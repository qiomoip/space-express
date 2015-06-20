#include "EditorScene.h"
#include "ObjectManager.h"
#include "Entity.h"
#include "CameraManager.h"
#include "Camera.h"
#include "ThirdCam.h"
#include "Light.h"
#include "KeyManager.h"
#include "TerrainMesh.h"
#include "Mouse.h"
#include "SceneButton.h"
#include "SaveButton.h"

CEditorScene::CEditorScene(void)
	: m_iBoxCnt(0)
{
}


CEditorScene::~CEditorScene(void)
{
	Destroy();
}

HRESULT CEditorScene::Init()
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

void CEditorScene::Update()
{
}


void CEditorScene::Destroy()
{
	CScene::Destroy();
}

void CEditorScene::Input()
{
	//클릭 들어오면
	//터레인과 충돌 체크 검사
	const KEYINFO* pInfo = _SINGLE(CKeyManager)->GetKey(KEY_NAME_L_BUTTON);
	if(!pInfo)
		return;

	if(pInfo->bPush)
	{
		CEntity* pTerrain = _SINGLE(CObjectManager)->FindObject("MainTerrain");

		CTerrainMesh* pTerrainMesh = (CTerrainMesh*)pTerrain->GetMesh();

		//뷰 스페이스의 레이...
		const D3DXMATRIX* pMatView = _SINGLE(CCameraManager)->GetCurCam()->GetMatView();
		
		//월드로 바꾼다.
		RAY tRay = _SINGLE(CMouse)->TransformRay(pMatView);

		//월드 역좌표로 해서 로컬로 변환하고 싶지만
		//어차피 ㅌㅓ레인의 월드는 Identity겠지...
		//D3DXMATRIX matWorld = pTerrain->GetMatWorld();

		//D3DXMATRIX matInverseWorld;

		//D3DXMatrixInverse(&matInverseWorld, 0, &matWorld);

		//D3DXVec3TransformNormal(&tRay.vDir, &tRay.vDir, &matInverseWorld);

		//여기서 나온 레이 구조체가 터레인 월드의 구조체...

		CEntity* pBox = NULL;

		if(pTerrainMesh->GetCollisionPos(tRay))
		{
			string strName = "PickingBox"; 
			strName += m_iBoxCnt;

			pBox = _SINGLE(CObjectManager)->CreateEntity(
				MT_BOX, RTYPE_ENTITY, strName, MN_BOX);
			pBox->SetPos(D3DXVECTOR3(tRay.vIntersectPos.x, 0.f, tRay.vIntersectPos.z));
			//pBox->SetScale(1, 1, 1);
			pBox->SetShader(SHADER_DEFAULT);
			pBox->SetTechKey("DefaultTech");
			pBox->SetPass(PASS_NOTEXTURE);
			++m_iBoxCnt;

			m_listBox.push_back(pBox);
		}

	}

	pInfo = _SINGLE(CKeyManager)->GetKey(KEY_NAME_R_BUTTON);
	if(!pInfo)
		return;

	if(pInfo->bPush)
	{
		RAY tRay = _SINGLE(CMouse)->TransformRay(_SINGLE(CCameraManager)->GetCurCam()->GetMatView());
		list<CEntity*>::iterator iter = m_listBox.begin();

		for(; iter != m_listBox.end(); ++iter)
		{
			if(_SINGLE(CMouse)->IntersectRayToSphere(&tRay, (*iter)->GetPos(), (*iter)->GetSize()))
			{
				_SINGLE(CObjectManager)->Remove_Object((*iter));
				
				//erase로 지우면 객체가 list에서 안 빠짐...
				//iter = m_listBox.erase(iter);

				m_listBox.remove(*iter);

				--m_iBoxCnt;

				break;
			}
		}
	}

	
	
}

HRESULT CEditorScene::CreateEntity()
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


	CEntity* pMainButton= _SINGLE(CObjectManager)->CreateEntity(MT_UI, RTYPE_UI, "ChangeMainSceneBtn", MN_SCENEBUTTON, L"ChangeMainButton");
	
	pMainButton->SetPos(D3DXVECTOR3(820.f, 650.f, 0.f));
	pMainButton->SetViewType(VIEW_ORTHOGONAL);
	pMainButton->SetShader(SHADER_DEFAULT);
	pMainButton->SetTechKey("DefaultTech");
	pMainButton->SetPass(PASS_DEFAULT);
	pMainButton->SetScale(100.f, 100.f, 0.f);
	pMainButton->SetDrawSphere(false);

	RECT rc;

	rc.left = 820.f;
	rc.right = 920.f;
	rc.top = 650.f;
	rc.bottom = 750.f;

	((CBaseButton*)pMainButton)->SetRectData(rc);

	((CSceneButton*)pMainButton)->SetSceneType(STYPE_MAIN1);
	((CSceneButton*)pMainButton)->SetScene(this);


	CEntity* pSaveButton = _SINGLE(CObjectManager)->CreateEntity(MT_UI, RTYPE_UI, "SaveDataButton", MN_SAVEBUTTON, L"SaveDataButton");
	
	pSaveButton->SetPos(D3DXVECTOR3(820.f, 540.f, 0.f));
	pSaveButton->SetViewType(VIEW_ORTHOGONAL);
	pSaveButton->SetShader(SHADER_DEFAULT);
	pSaveButton->SetTechKey("DefaultTech");
	pSaveButton->SetPass(PASS_DEFAULT);
	pSaveButton->SetScale(100.f, 100.f, 0.f);
	pSaveButton->SetDrawSphere(false);

	rc.left = 820.f;
	rc.right = 920.f;
	rc.top = 540.f;
	rc.bottom = 640.f;

	((CBaseButton*)pSaveButton)->SetRectData(rc);
	((CSaveButton*)pSaveButton)->SetScene(this);

	if(FAILED(CreateBox(L"Data\\BoxPos.txt")))
	{
		return E_FAIL;
	}

	return S_OK;
}

HRESULT CEditorScene::CreateCamera()
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

HRESULT CEditorScene::CreateLight()
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

HRESULT CEditorScene::CreateBox(LPCWSTR pFileName)
{
	HANDLE hFile = CreateFile(pFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	
	if(INVALID_HANDLE_VALUE == hFile)
		return E_FAIL;

	int* pData = new int;

	DWORD dwBytes;

	ReadFile(hFile, pData, sizeof(int), &dwBytes, NULL);
	
	int iBoxCount = *pData;

	Safe_Delete(pData);

	string* pName = new string;

	for(int i = 0; i < iBoxCount; ++i)
	{
		
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

		Safe_Delete(pPos);

		m_listBox.push_back(pBox);

	}

	m_iBoxCnt = iBoxCount;

	CloseHandle(hFile);


	return S_OK;
}
