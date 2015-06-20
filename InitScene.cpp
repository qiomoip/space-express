#include "InitScene.h"
#include "Entity.h"
#include "ObjectManager.h"
#include "CameraManager.h"
#include "Camera.h"
#include "ThirdCam.h"
#include "Light.h"
#include "SceneButton.h"


CInitScene::CInitScene(void)
{
}


CInitScene::~CInitScene(void)
{
	Destroy();
}

HRESULT CInitScene::Init()
{
	if(FAILED(CScene::Init()))
	{
		return E_FAIL;
	}

	if(FAILED(CreateEntity()))
	{
		return E_FAIL;
	}

	if(FAILED(CreateCamera()))
	{
		return E_FAIL;
	}

	if(FAILED(CreateLight()))
	{
		return E_FAIL;
	}

	return S_OK;
}

void CInitScene::Update()
{
}


void CInitScene::Destroy()
{
	CScene::Destroy();
}

HRESULT CInitScene::CreateEntity()
{
	//_SINGLE(CResourceManager)->Load(MT_STATIC, "Tiger", _T("tiger.x"));

	CEntity* pSylva = _SINGLE(CObjectManager)->CreateEntity(
		MT_STATIC, RTYPE_ENTITY, "Tiger", MN_TIGER, _T("tiger.x"));
	pSylva->SetPos(D3DXVECTOR3(-5.f, 0.f, 0.f));
	pSylva->SetShader(SHADER_DEFAULT);
	pSylva->SetTechKey("DefaultTech");
	pSylva->SetPass(PASS_DEFAULT);
	pSylva->SetRotation(AT_Y, D3DX_PI);
	
	//CEntity* pSylvas[2];
	//테스트용 NPC생성
	for ( int i = 1; i <= 10; ++i)
	{
		string str = "Npc"; 
		str += i;
		pSylva = _SINGLE(CObjectManager)->CreateEntity(
			MT_STATIC, RTYPE_ENTITY, str, MN_ZOMBIE, _T("tiger.x"));
		pSylva->SetPos(D3DXVECTOR3(-3.f + (i * 5.f), 0.0f, sin(i) * 5.f) );
		pSylva->SetShader(SHADER_DEFAULT);
		pSylva->SetTechKey("DefaultTech");
		pSylva->SetPass(PASS_DEFAULT);
	}
	
	//*
	CEntity* pTerrain = _SINGLE(CObjectManager)->CreateEntity(
		MT_TERRAIN, RTYPE_TERRAIN, "MainTerrain", MN_TERRAIN, _T("MainTerrain"));
	pTerrain->SetShader(SHADER_DEFAULT);
	pTerrain->SetTechKey("DefaultTech");
	pTerrain->SetPass(PASS_DEFAULT);
	//*/

	CEntity* pEnvi = _SINGLE(CObjectManager)->CreateEntity(
		MT_STATIC, RTYPE_ENVIRONMENT, "Envi", MN_ENVIRONMENT, _T("Environment.X"));
	pEnvi->SetPos(D3DXVECTOR3(0.f, 10.f, 0.f));
	pEnvi->SetScale(5.f, 5.f, 5.f);
	pEnvi->SetShader(SHADER_DEFAULT);
	pEnvi->SetTechKey("DefaultTech");
	pEnvi->SetPass(PASS_DEFAULT/*PASS_NOTEXTURE*/);

#ifdef _DEBUG
	CEntity* pGrid = _SINGLE(CObjectManager)->CreateEntity(
		MT_GRID, RTYPE_GRID, "DebugGrid", MN_GRID, _T("Grid"));
	pGrid->SetShader(SHADER_DEFAULT);
	pGrid->SetTechKey("DefaultTech");
	pGrid->SetPass(PASS_NOTEXTURE);
#endif

	//박스로 빌딩 역할 (임시)
	CEntity* pBox;

	srand(0);

	for(int i = 0; i < 1; ++i)
	{
		int iScale = 1;
		int iPosX = -5;
		int iPosZ = -5;

		string strName = "Box"; 
		strName += i;

		pBox = _SINGLE(CObjectManager)->CreateEntity(
			MT_BOX, RTYPE_ENTITY, strName, MN_BOX);
		pBox->SetPos(D3DXVECTOR3(iPosX, 0.f, iPosZ));
		pBox->SetScale(iScale, iScale, iScale);
		pBox->SetShader(SHADER_DEFAULT);
		pBox->SetTechKey("DefaultTech");
		pBox->SetPass(PASS_NOTEXTURE);
	}

	/*
	UI
	*/
	CEntity* pEditButton= _SINGLE(CObjectManager)->CreateEntity(MT_UI, RTYPE_UI, "ChangeEditSceneBtn1", MN_SCENEBUTTON, L"ChangeEditButton");
	pEditButton->SetPos(D3DXVECTOR3(930.f, 650.f, 0.f));
	pEditButton->SetViewType(VIEW_ORTHOGONAL);
	pEditButton->SetShader(SHADER_DEFAULT);
	pEditButton->SetTechKey("DefaultTech");
	pEditButton->SetPass(PASS_DEFAULT);
	pEditButton->SetScale(100.f, 100.f, 0.f);
	pEditButton->SetDrawSphere(false);
	
	((CSceneButton*)pEditButton)->SetScene(this);

	RECT rc;
	rc.left = 930.f;
	rc.right = 1030.f;
	rc.top = 650.f;
	rc.bottom = 750.f;

	((CSceneButton*)pEditButton)->SetRectData(rc);
	((CSceneButton*)pEditButton)->SetSceneType(STYPE_EDIT);
	((CSceneButton*)pEditButton)->SetScene(this);

	CEntity* pMainButton= _SINGLE(CObjectManager)->CreateEntity(MT_UI, RTYPE_UI, "ChangeMainSceneBtn", MN_SCENEBUTTON, L"ChangeMainButton");
	
	pMainButton->SetPos(D3DXVECTOR3(820.f, 650.f, 0.f));
	pMainButton->SetViewType(VIEW_ORTHOGONAL);
	pMainButton->SetShader(SHADER_DEFAULT);
	pMainButton->SetTechKey("DefaultTech");
	pMainButton->SetPass(PASS_DEFAULT);
	pMainButton->SetScale(100.f, 100.f, 0.f);
	pMainButton->SetDrawSphere(false);

	rc.left = 820.f;
	rc.right = 920.f;
	rc.top = 650.f;
	rc.bottom = 750.f;

	((CSceneButton*)pMainButton)->SetRectData(rc);

	((CSceneButton*)pMainButton)->SetSceneType(STYPE_MAIN1);
	((CSceneButton*)pMainButton)->SetScene(this);

	return S_OK;
}

HRESULT CInitScene::CreateCamera()
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

HRESULT CInitScene::CreateLight()
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
