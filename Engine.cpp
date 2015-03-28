#include "Engine.h"
#include "Device.h"
#include "Debug.h"
#include "Camera.h"
#include "CameraManager.h"
#include "KeyManager.h"
#include "ResourceManager.h"
#include "ObjectManager.h"
#include "TString.h"
#include "Entity.h"
#include "ThirdCam.h"
#include "Mouse.h"
#include "Light.h"
#include "Shader.h"
#include "ShaderManager.h"

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

	if(FAILED(CreateEntity()))
		return E_FAIL;

	if(FAILED(CreateCamera()))
		return E_FAIL;

	if(FAILED(CreateLight()))
		return E_FAIL;

	const CCamera* pMainCam = _SINGLE(CCameraManager)->GetCurCam();

	((CThirdCam*)pMainCam)->SetLookObject(_SINGLE(CObjectManager)->FindObject("Tiger"));


	return S_OK;
}

HRESULT CEngine::CreateEntity()
{
	//_SINGLE(CResourceManager)->Load(MT_STATIC, "Tiger", _T("tiger.x"));

	CEntity* pSylva = _SINGLE(CObjectManager)->CreateEntity(MT_STATIC, RTYPE_ENTITY, "Tiger", _T("tiger.x"));
	pSylva->SetPos(D3DXVECTOR3(0.f, 0.f, 0.f));
	pSylva->SetShader(SHADER_DEFAULT);
	pSylva->SetTechKey("DefaultTech");
	pSylva->SetPass(PASS_DEFAULT);

	CEntity* pTerrain = _SINGLE(CObjectManager)->CreateEntity(MT_TERRAIN, RTYPE_TERRAIN, "MainTerrain");
	pTerrain->SetShader(SHADER_DEFAULT);
	pTerrain->SetTechKey("DefaultTech");
	pTerrain->SetPass(PASS_DEFAULT);


	CEntity* pEnvi = _SINGLE(CObjectManager)->CreateEntity(MT_STATIC, RTYPE_ENVIRONMENT, "Envi", _T("Environment.X"));
	pEnvi->SetPos(D3DXVECTOR3(0.f, 10.f, 0.f));
	pEnvi->SetScale(5.f, 5.f, 5.f);
	pEnvi->SetShader(SHADER_DEFAULT);
	pEnvi->SetTechKey("DefaultTech");
	pEnvi->SetPass(PASS_DEFAULT/*PASS_NOTEXTURE*/);

	return S_OK;
}

HRESULT CEngine::CreateCamera()
{
	//Camera
	CCamera* pCam = _SINGLE(CCameraManager)->CreateCamera(CN_THIRD);
	_SINGLE(CCameraManager)->AddCamera("MainCamera", pCam);
	_SINGLE(CCameraManager)->SetMainCamera("MainCamera");

	//Camera
	CCamera* pCam1 = _SINGLE(CCameraManager)->CreateCamera(CN_THIRD);
	pCam1->SetPos(D3DXVECTOR3(10.f, 0.f, -10.f));
	_SINGLE(CCameraManager)->AddCamera("ThirdTestCam", pCam1);

	return S_OK;
}

HRESULT CEngine::CreateLight()
{
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
	_SINGLE(CCameraManager)->Update();
	_SINGLE(CObjectManager)->Update();
	_SINGLE(CDebug)->Update();
}

VOID CEngine::Render()
{
	if( NULL == m_pDevice->GetDevice() )
		return;

	// Clear the backbuffer to a blue color
	m_pDevice->GetDevice()->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | 
		D3DCLEAR_STENCIL, D3DCOLOR_XRGB( 200, 200, 200 ), 1.0f, 0 );

	// Begin the scene
	if( SUCCEEDED( m_pDevice->GetDevice()->BeginScene() ) )
	{
		// Rendering of scene objects can happen here

		//Camera Transform
		_SINGLE(CCameraManager)->SetTransform(); 

		//Set Light
		_SINGLE(CDevice)->GetDevice()->SetRenderState(D3DRS_LIGHTING, true);
		for(unsigned int i = 0; i < m_vecLight.size(); ++i)
		{
			m_pDevice->GetDevice()->SetLight(i, m_vecLight[i]->GetLightInfo());
			m_pDevice->GetDevice()->LightEnable(i, true);
		}

		//Debug Render
		_SINGLE(CDebug)->Render();

		//ObjectRender
		_SINGLE(CObjectManager)->Render();

		// End the scene
		m_pDevice->GetDevice()->EndScene();
	}

	// Present the backbuffer contents to the display
	m_pDevice->GetDevice()->Present( NULL, NULL, NULL, NULL );
}

VOID CEngine::Destroy()
{
	for(unsigned int i = 0; i < m_vecLight.size(); ++i)
		Safe_Delete(m_vecLight[i]);
	m_vecLight.clear();
	_SINGLE(CShaderManager)->KillInstance();
	_SINGLE(CMouse)->KillInstance();
	_SINGLE(CObjectManager)->KillInstance();
	_SINGLE(CResourceManager)->KillInstance();
	_SINGLE(CCameraManager)->KillInstance();
	_SINGLE(CKeyManager)->KillInstance();


#ifdef _DEBUG
	_SINGLE(CDebug)->KillInstance();
#endif

	if(m_pDevice)
		m_pDevice->KillInstance();
}

VOID CEngine::Collision()
{
}

VOID CEngine::Run()
{
	Collision();
	Input();
	Update();
	Render();
}

void CEngine::Input()
{
	_SINGLE(CKeyManager)->SetKeyState();
	_SINGLE(CCameraManager)->Input();
	_SINGLE(CObjectManager)->Input();

#ifdef _DEBUG
	_SINGLE(CDebug)->Input();
#endif
}