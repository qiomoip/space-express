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
	m_Objects = new map<eTYPE, map<LPTSTR, CEntity*>*>;
	m_Objects->insert(pair<eTYPE,map<LPTSTR, CEntity*>*>(TYPE_OBJECT, new map<LPTSTR, CEntity*>) );
	m_Objects->insert(pair<eTYPE,map<LPTSTR, CEntity*>*>(TYPE_WALL, new map<LPTSTR, CEntity*>) );
	m_Objects->insert(pair<eTYPE,map<LPTSTR, CEntity*>*>(TYPE_CHARACTER, new map<LPTSTR, CEntity*>) );
}

void CObjectManager::CleanUp()
{
	map<eTYPE, map<LPTSTR, CEntity*>*>::iterator it = m_Objects->begin();
	for(; it != m_Objects->end(); ++it)
	{
		map<LPTSTR, CEntity*>::iterator it_child = it->second->begin();
		for(; it_child != it->second->end(); ++it_child)
			Safe_Delete( (it_child->second) );
		
		Safe_Delete( it->second );

		//Safe_Delete_Array_Map( *(it->second) );

	}

	m_Objects->clear();
	
	Safe_Delete(m_Objects);
}

HRESULT CObjectManager::Render()
{
	const map<string, CMesh*>* mapMesh = _SINGLE(CResourceManager)->GetMeshList();

	for(map<string, CMesh*>::const_iterator iter = mapMesh->begin(); iter != mapMesh->end(); ++iter)
	{
		iter->second->Render();
	}
	return S_OK;
}