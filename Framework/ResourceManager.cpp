#include "ResourceManager.h"


CResourceManager::CResourceManager(void)
{
	Init();
}


CResourceManager::~CResourceManager(void)
{
	CleanUp();
}


void CResourceManager::Init()
{
	m_MeshArray = new vector<MESH_INFO*>;
	m_TextureArray = new vector<TEXTURE_INFO*>;
}

void CResourceManager::CleanUp()
{
	for(UINT i = 0; i < m_MeshArray->size(); ++i)
		delete (*m_MeshArray)[i];
	m_MeshArray->clear();
	SAFE_DELETE( m_MeshArray );

	for(UINT i = 0; i < m_TextureArray->size(); ++i)
		delete (*m_TextureArray)[i];
	m_TextureArray->clear();
	SAFE_DELETE( m_TextureArray );
}