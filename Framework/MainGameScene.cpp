#include "MainGameScene.h"
#include "Entity.h"
#include "ThirdCam.h"
#include "Mouse.h"
#include "Light.h"
#include "Shader.h"
#include "ShaderManager.h"
#include "Frustum.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "ObjectManager.h"
#include "Debug.h"
#include "Camera.h"
#include "CameraManager.h"
#include "SceneButton.h"

CMainGameScene::CMainGameScene(void)
{
}


CMainGameScene::~CMainGameScene(void)
{
	Destroy();
}

HRESULT CMainGameScene::Init()
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

void CMainGameScene::Update()
{
}

void CMainGameScene::Destroy()
{
	CScene::Destroy();
}

HRESULT CMainGameScene::CreateEntity()
{
	//_SINGLE(CResourceManager)->Load(MT_STATIC, "Tiger", _T("tiger.x"));

	CEntity* pSylva = _SINGLE(CObjectManager)->CreateEntity(
		MT_STATIC, RTYPE_ENTITY, "Tiger", MN_TIGER, _T("tiger.x"));
	pSylva->SetPos(D3DXVECTOR3(-5.f, 0.f, 0.f));
	pSylva->SetShader(SHADER_DEFAULT);
	pSylva->SetTechKey("DefaultTech");
	pSylva->SetPass(PASS_DEFAULT);
	pSylva->SetRotation(AT_Y, D3DX_PI);
	
	
	srand((unsigned)time(NULL));
	//CEntity* pSylvas[2];
	//테스트용 NPC생성
	for ( int i = 1; i <= 10; ++i)
	{
		float x = (float)(rand()%10);
		float y = (float)(rand()%10);
		string str = "Npc"; 
		str += i;
		pSylva = _SINGLE(CObjectManager)->CreateEntity(
			MT_STATIC, RTYPE_ENTITY, str, MN_ZOMBIE, _T("tiger.x"));
		/*pSylva->SetPos(D3DXVECTOR3(-3.f + ((float)i * 5.f), 0.0f, sin((float)i) * 5.f) );*/
		pSylva->SetPos(D3DXVECTOR3(x, 0, y) );
		pSylva->SetRotation(eAxis_TYPE::AT_X, D3DX_PI * 0.5f);
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
	
	//*
	CEntity* pEnvi = _SINGLE(CObjectManager)->CreateEntity(
		MT_STATIC, RTYPE_ENVIRONMENT, "Envi", MN_ENVIRONMENT, _T("Environment.X"));
	pEnvi->SetPos(D3DXVECTOR3(0.f, 10.f, 0.f));
	pEnvi->SetScale(5.f, 5.f, 5.f);
	pEnvi->SetShader(SHADER_DEFAULT);
	pEnvi->SetTechKey("DefaultTech");
	pEnvi->SetPass(PASS_DEFAULT);//PASS_NOTEXTURE
	//*/
	
	//*
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

	CEntity* pEditButton= _SINGLE(CObjectManager)->CreateEntity(MT_UI, RTYPE_UI, "ChangeEditSceneBtn2", MN_SCENEBUTTON, L"ChangeEditButton");
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

	if(FAILED(CreateBox(L"Data\\BoxPos.txt")))
	{
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CMainGameScene::CreateBox(LPCWSTR pFileName)
{
	HANDLE hFile = CreateFile(pFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	
	if(INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;

	int* pData = new int;

	DWORD dwBytes;

	ReadFile(hFile, pData, sizeof(int), &dwBytes, NULL);
	
	int iBoxCount = *pData;

	for(int i = 0; i < iBoxCount; ++i)
	{
		string* pName = new string;
		D3DXVECTOR3* pPos = new D3DXVECTOR3;

		//*pName = string("PickingBox" + i);
		//*pPos = D3DXVECTOR3(10.f, 0.f, 10.f);

		//string strName = "PickBox";
		//D3DXVECTOR3 vPos = D3DXVECTOR3(10.f, 0.f, 10.f);
		
		ReadFile(hFile, pName, sizeof(string), &dwBytes, NULL);
		ReadFile(hFile, pPos, sizeof(D3DXVECTOR3), &dwBytes, NULL);

		CEntity* pBox = _SINGLE(CObjectManager)->CreateEntity(
			MT_BOX, RTYPE_ENTITY, *pName, MN_BOX);
		pBox->SetPos(D3DXVECTOR3(pPos->x, 0.f, pPos->z));

		//CEntity* pBox = _SINGLE(CObjectManager)->CreateEntity(
		//	MT_BOX, RTYPE_ENTITY, strName, MN_BOX);
		//pBox->SetPos(D3DXVECTOR3(vPos.x, 0.f, vPos.z));


		pBox->SetScale(1, 1, 1);
		pBox->SetShader(SHADER_DEFAULT);
		pBox->SetTechKey("DefaultTech");
		pBox->SetPass(PASS_NOTEXTURE);

//		Safe_Delete(pName);
		Safe_Delete(pPos);
		Safe_Delete(pData);

	}

	CloseHandle(hFile);


	return S_OK;
}

HRESULT CMainGameScene::CreateCamera()
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

HRESULT CMainGameScene::CreateLight()
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
