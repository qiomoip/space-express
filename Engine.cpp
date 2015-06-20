#include "Engine.h"
#include "Device.h"
#include "Debug.h"
#include "Camera.h"
#include "CameraManager.h"
#include "KeyManager.h"
#include "ResourceManager.h"
#include "ObjectManager.h"
#include "Entity.h"
#include "ThirdCam.h"
#include "Mouse.h"
#include "Light.h"
#include "Shader.h"
#include "ShaderManager.h"
#include "Frustum.h"
#include "SceneManager.h"
#include "TimeManager.h"
#include "ZombieAttackState.h"
#include "ZombieIdleState.h"
#include "ZombieTrackingState.h"
#include "ZombieFleeState.h"
#include "SceneManager.h"
#include "MainGameScene.h"


CEngine::CEngine(void)
	: m_pDevice(NULL)
	, m_Name(NULL)
{
}

CEngine::~CEngine(void)
{
	Destroy();
}



HRESULT CEngine::Initialize(HWND hWnd)
{
	m_pDevice = _SINGLE(CDevice);

	if(FAILED(m_pDevice->Initialize(hWnd)))
	{
		return E_FAIL;
	}

	//Key
	_SINGLE(CKeyManager)->Initialize();
	_SINGLE(CMouse)->SetHwnd(hWnd);

#ifdef _DEBUG
	_SINGLE(CDebug)->Initialize();
#endif

	if(FAILED(CreateShader()))
		return E_FAIL;

	//씬 생성
	_SINGLE(CSceneManager)->CreateScene(STYPE_MAIN1);

	return S_OK;
}

HRESULT CEngine::CreateEntity()
{
	CEntity* pSylva = _SINGLE(CObjectManager)->CreateEntity(
		MT_STATIC, RTYPE_ENTITY, "Tiger", MN_TIGER, _T("tiger.x"));
	pSylva->SetPos(D3DXVECTOR3(-5.f, 0.f, 0.f));
	pSylva->SetShader(SHADER_DEFAULT);
	pSylva->SetTechKey("DefaultTech");
	pSylva->SetPass(PASS_DEFAULT);
	pSylva->SetRotation(AT_Y, D3DX_PI);
	
	
	srand((unsigned)time(NULL));
	//테스트용 NPC생성
	for ( int i = 1; i <= 10; ++i)
	{
		float x = (float)(rand()%10);
		float y = (float)(rand()%10);
		string str = "Npc"; 
		str += i;
		pSylva = _SINGLE(CObjectManager)->CreateEntity(
			MT_STATIC, RTYPE_ENTITY, str, MN_ZOMBIE, _T("sylva.x"));
		/*pSylva->SetPos(D3DXVECTOR3(-3.f + ((float)i * 5.f), 0.0f, sin((float)i) * 5.f) );*/
		pSylva->SetPos(D3DXVECTOR3(x, 0, y) );
		pSylva->SetRotation(eAxis_TYPE::AT_X, D3DX_PI * 0.5f);
		pSylva->SetShader(SHADER_DEFAULT);
		pSylva->SetTechKey("DefaultTech");
		pSylva->SetPass(PASS_DEFAULT);
	}
	
	return S_OK;
}

HRESULT CEngine::CreateCamera()
{
	//Camera 메인 자유시점
	CCamera* pCam = _SINGLE(CCameraManager)->CreateCamera(CN_THIRD);
	/*pCam->SetPos(D3DXVECTOR3(50.f,148.f, 10.f));
	pCam->SetData(D3DXVECTOR3(0.f, 0.f, 1.f), D3DXVECTOR3(0.f, -1.f, 0.f), D3DXVECTOR3(1.f, 0.f, 0.f));*/ 
	_SINGLE(CCameraManager)->AddCamera("MainCamera", pCam);
	_SINGLE(CCameraManager)->SetMainCamera("MainCamera");

	((CThirdCam*)pCam)->SetLookObject(_SINGLE(CObjectManager)->FindObject("Tiger"));
	//Camera 3인칭
	CCamera* pCam1 = _SINGLE(CCameraManager)->CreateCamera(CN_THIRD);
	pCam1->SetPos(D3DXVECTOR3(10.f, 0.f, -10.f));
	_SINGLE(CCameraManager)->AddCamera("ThirdTestCam", pCam1);

	return S_OK;
}

HRESULT CEngine::CreateLight()
{
	m_vecLight.reserve(10);

	CLight* pLight = new CLight;
	
	D3DLIGHT9 tLight;
	memset(&tLight, 0, sizeof(D3DLIGHT9));

	D3DCOLORVALUE tValue;
	tValue.b = tValue.g = tValue.r = tValue.a = 1.f;

	tLight.Ambient = tValue;
	tLight.Diffuse = tValue;
	tLight.Specular = tValue;
	
	tLight.Direction = D3DXVECTOR3(1.f, 0.f, 1.f);
	tLight.Type = D3DLIGHT_DIRECTIONAL;

	pLight->SetLightInfo(tLight);

	m_vecLight.push_back(pLight);

	return S_OK;
}

HRESULT CEngine::CreateShader()
{
	if(FAILED(_SINGLE(CShaderManager)->CreateShader(SHADER_DEFAULT, _T("shader.hpp"))))
	{
		return E_FAIL;
	}

	return S_OK;
}

void CEngine::Update()
{
	_SINGLE(CObjectManager)->Update();
	_SINGLE(CCameraManager)->Update();
	_SINGLE(CSceneManager)->Update();
	#ifdef _DEBUG
	_SINGLE(CDebug)->Update();
#endif
}

VOID CEngine::Render()
{
	_SINGLE(CSceneManager)->Render();
}

VOID CEngine::Destroy()
{
	for(unsigned int i = 0; i < m_vecLight.size(); ++i)
		Safe_Delete(m_vecLight[i]);
	m_vecLight.clear();
	_SINGLE(CFrustum)->KillInstance();
	_SINGLE(CShaderManager)->KillInstance();
	_SINGLE(CMouse)->KillInstance();
	_SINGLE(CSceneManager)->KillInstance();
	_SINGLE(CObjectManager)->KillInstance();
	_SINGLE(CResourceManager)->KillInstance();
	_SINGLE(CCameraManager)->KillInstance();
	_SINGLE(CKeyManager)->KillInstance();
#ifdef _DEBUG
	_SINGLE(CDebug)->KillInstance();
#endif
	_SINGLE(CTimeManager)->KillInstance();
	_SINGLE(CZombieAttackState)->KillInstance();
	_SINGLE(CZombieIdleState)->KillInstance();
	_SINGLE(CZombieTrackingState)->KillInstance();
	_SINGLE(CZombieFleeState)->KillInstance();

	if(m_pDevice)
		m_pDevice->KillInstance();
}

VOID CEngine::Collision()
{
}

VOID CEngine::Run()
{
	Input();
	Update();
	Collision();
	Render();
}

void CEngine::Input()
{
	_SINGLE(CTimeManager)->CheckFps();
	_SINGLE(CKeyManager)->SetKeyState();
	_SINGLE(CCameraManager)->Input();
	_SINGLE(CObjectManager)->Input();
	_SINGLE(CSceneManager)->Input();
#ifdef _DEBUG
	_SINGLE(CDebug)->Input();
#endif
}