#include "ObjectManager.h"
#include "ResourceManager.h"
#include "Entity.h"

//юс╫ц
#include "Mesh.h"


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


CEntity* CObjectManager::CreateEntity(const eMESH_TYPE& eMeshType, const eRENDER_TYPE& eRender, const string& strMeshKey, const LPTSTR szMeshName)
{
	map<string, CEntity*>::iterator iter = m_mapObject.find(strMeshKey);

	if(iter != m_mapObject.end())
		return iter->second;

	CEntity* pEntity = new CEntity;
	pEntity->Initialize();
	pEntity->SetRenderType(eRender);
	pEntity->SetName(strMeshKey);
	CMesh* pMesh = NULL;
	
	if(eRender != RTYPE_NONE)
		pMesh = _SINGLE(CResourceManager)->Load(eMeshType, strMeshKey, szMeshName);

	if(pMesh)
		pEntity->PushMesh(pMesh);

	m_mapObject.insert(map<string, CEntity*>::value_type(strMeshKey, pEntity));

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
	for(int i = RTYPE_ENVIRONMENT; i < RTYPE_MAX; ++i)
	{
		for(list<CEntity*>::iterator iter = m_listRenderList[i].begin(); iter != m_listRenderList[i].end();
			++iter)
		{
			(*iter)->Render();
		}
	}

	for(int i = RTYPE_ENVIRONMENT; i < RTYPE_MAX; ++i)
	{
		m_listRenderList[i].clear();
	}

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

void CObjectManager::Push_RenderList(CEntity* pEntity)
{
	m_listRenderList[pEntity->GetRenderType()].push_back(pEntity);
}

CEntity*	CObjectManager::FindObject(const string& strObjKey)
{
	map<string, CEntity*>::iterator iter = m_mapObject.find(strObjKey);

	if(iter == m_mapObject.end())
		return NULL;

	return iter->second;
}