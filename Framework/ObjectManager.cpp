#include "ObjectManager.h"
#include "ResourceManager.h"
#include "Entity.h"
#include "ShaderManager.h"
#include "Shader.h"
#include "Tiger.h"
#include "Frustum.h"
#include "Zombie.h"

#include "Debug.h"

//임시
#include "Mesh.h"

#include "Device.h"

#include "SceneButton.h"
#include "SaveButton.h"


CObjectManager::CObjectManager(void)
{
	Init();
}

CObjectManager::~CObjectManager(void)
{
	CleanUp();
}

void CObjectManager::Init()
{
}

void CObjectManager::CleanUp()
{
	for(int i = 0; i < RTYPE_MAX; ++i)
		m_listRenderList[i].clear();

	Safe_Delete_Map(m_mapObject);
	
}


CEntity* CObjectManager::CreateEntity(
	const eMESH_TYPE& eMeshType, 
	const eRENDER_TYPE& eRender, 
	const string& strEntityKey,  
	const eMESH_NUM& eMeshNum, 
	const LPTSTR szMeshName)
{
	map<string, CEntity*>::iterator iter = m_mapObject.find(strEntityKey);

	if(iter != m_mapObject.end())
		return iter->second;

	CEntity* pEntity = NULL;

	switch(eMeshNum)
	{
	case MN_TIGER:
		pEntity = new CTiger;
		break;
		
	case MN_TERRAIN:
	case MN_ENVIRONMENT:
	case MN_GRID:
	case MN_BOX:
		pEntity = new CEntity;
		break;
		/*case MN_ENVIRONMENT:
		pEntity = new CEntity;
		break;
	
		pEntity = new CEntity;
		break;
	
		pEntity = new CEntity;
		break;*/
	case MN_ZOMBIE:
		pEntity = new CZombie;
		iter = m_mapObject.find("Tiger");
		 ((CZombie*)pEntity)->SetHero(iter->second );
		break;
	case MN_SCENEBUTTON:
		pEntity = new CSceneButton;
		break;
	case MN_SAVEBUTTON:
		pEntity = new CSaveButton;
		break;
	default:
		pEntity = new CEntity;
		break;
	}
	//CEntity* pEntity = new CEntity;
	pEntity->Initialize();
	pEntity->SetRenderType(eRender);
	pEntity->SetName(strEntityKey);
	CMesh* pMesh = NULL;
	
	if(eRender != RTYPE_NONE)
		pMesh = _SINGLE(CResourceManager)->Load(eMeshType, eMeshNum, szMeshName);

	if(pMesh)
		pEntity->PushMesh(pMesh);

	m_mapObject.insert(map<string, CEntity*>::value_type(strEntityKey, pEntity));
	
	//메시크기로 경계구 생성
	pEntity->InitSphereMesh();

	pEntity->m_eMeshNum = eMeshNum;
	
	return pEntity;
}

CEntity* CObjectManager::CreateEntity(const string& strEntityKey)
{
	map<string, CEntity*>::iterator iter = m_mapObject.find(strEntityKey);

	if(iter != m_mapObject.end())
		return iter->second;

	CEntity* pEntity = new CEntity;
	pEntity->Initialize();
	pEntity->SetName(strEntityKey);

	return pEntity;
}


void CObjectManager::Input()
{
	for(map<string, CEntity*>::iterator iter = m_mapObject.begin();
		iter != m_mapObject.end(); ++iter)
	{
		iter->second->Input();
	}
}

HRESULT CObjectManager::Render()
{
	//const map<string, CMesh*>* mapMesh = _SINGLE(CResourceManager)->GetMeshList();

	//for(map<string, CMesh*>::const_iterator iter = mapMesh->begin(); iter != mapMesh->end(); ++iter)
	//{
	//	iter->second->Render();
	//}
	
	//LPDIRECT3DDEVICE9 pd3dDevice = _SINGLE(CDevice)->GetDevice();
	//pd3dDevice->SetStreamSourceFreq( 0, D3DSTREAMSOURCE_INDEXEDDATA | g_NumBoxes );
	//pd3dDevice->SetStreamSource( 0, g_pVBBox, 0, sizeof( BOX_VERTEX ) );

	////스트림 1로 세팅 되어있는 세컨드 버텍스 버퍼 바인드
	////버텍스당 하나의 인스턴싱 데이터를 가지므로 1과 바인드한다
	//pd3dDevice->SetStreamSourceFreq( 1, D3DSTREAMSOURCE_INSTANCEDATA | 1ul );
	//pd3dDevice->SetStreamSource( 1, g_pVBInstanceData, 0, sizeof( BOX_INSTANCEDATA_POS ) );
	
	static UINT dpcall ;
	dpcall = 0;
	for(int i = RTYPE_NONE + 1; i < RTYPE_MAX; ++i)
	{
		if(i == RTYPE_UI)
			continue;

		for(list<CEntity*>::iterator iter = m_listRenderList[i].begin(); iter != m_listRenderList[i].end();
			++iter)
		{
			_SINGLE(CShaderManager)->BeginShader((*iter)->GetShader(), (*iter)->GetTechKey());

			(*iter)->Render();

			_SINGLE(CShaderManager)->EndShader((*iter)->GetShader());
		}
	}
	_SINGLE(CResourceManager)->RenderInstancingData();

	//ui는 따로~~
	list<CEntity*>::iterator iter = m_listRenderList[RTYPE_UI].begin();

	for(; iter != m_listRenderList[RTYPE_UI].end(); ++iter)
	{
		_SINGLE(CShaderManager)->BeginShader((*iter)->GetShader(), (*iter)->GetTechKey());

			(*iter)->Render();

			_SINGLE(CShaderManager)->EndShader((*iter)->GetShader());
	}

#ifdef _DEBUG
	_SINGLE(CDebug)->AddStaticLog(LOG_DPCALL, _T("DP call : %d"), dpcall) ;
#endif _DEBUG


	//렌더리스트 초기화
	Reset_RenderList();

	return S_OK;
}

void CObjectManager::Update()
{
	for(map<string, CEntity*>::iterator iter = m_mapObject.begin();
		iter != m_mapObject.end(); ++iter)
	{
		iter->second->Update();
	}

}

void CObjectManager::Collision()
{

}


void CObjectManager::Push_RenderList(CEntity* pEntity)
{
	m_listRenderList[pEntity->GetRenderType()].push_back(pEntity);
}

void CObjectManager::Reset_RenderList()
{
	for (int i = RTYPE_NONE + 1; i < RTYPE_MAX; ++i)
		m_listRenderList[i].clear();
}

void CObjectManager::Remove_Object(CEntity*	pEntity)
{
	m_mapObject.erase(pEntity->GetName());
	for(list<CEntity*>::iterator iter = m_listRenderList[pEntity->GetRenderType()].begin();
		iter != m_listRenderList[pEntity->GetRenderType()].end();
		++iter)
	{
		if((*iter)->GetName() == pEntity->GetName())
		{
			iter = m_listRenderList[pEntity->GetRenderType()].erase(iter);
			break;
		}
	}

	Safe_Delete(pEntity);
}

CEntity*	CObjectManager::FindObject(const string& strObjKey)
{
	map<string, CEntity*>::iterator iter = m_mapObject.find(strObjKey);

	if(iter == m_mapObject.end())
		return NULL;

	return iter->second;
}

list<CEntity*>* CObjectManager::GetRenderList()
{
	return m_listRenderList;
}
