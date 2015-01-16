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

	
#ifdef _DEBUG
	m_Info = new CInfo();
#endif
}

void CResourceManager::CleanUp()
{
	for(UINT i = 0; i < m_MeshArray->size(); ++i)
		SAFE_DELETE( (*m_MeshArray)[i] );
	m_MeshArray->clear();
	SAFE_DELETE( m_MeshArray );

	for(UINT i = 0; i < m_TextureArray->size(); ++i)
		SAFE_DELETE( (*m_TextureArray)[i] );
	m_TextureArray->clear();
	SAFE_DELETE( m_TextureArray );

#ifdef _DEBUG
	SAFE_DELETE(m_Info );
#endif
}