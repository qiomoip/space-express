#include "ResourceManager.h"
#include "Device.h"

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
}

void CResourceManager::CleanUp()
{
	for(UINT i = 0; i < m_MeshArray->size(); ++i)
	{
		if( (*m_MeshArray)[i]->pMaterials )
			Safe_Delete_Array( (*m_MeshArray)[i]->pMaterials );
		if( (*m_MeshArray)[i]->pTextures )
		{
			for( DWORD j = 0; j < (*m_MeshArray)[i]->dwNumMaterials; ++j)
			{
				if( (*m_MeshArray)[i]->pTextures[j] )
					Safe_Release( (*m_MeshArray)[i]->pTextures[j] );
			}
			Safe_Delete_Array( (*m_MeshArray)[i]->pTextures );
		}
		if( (*m_MeshArray)[i]->pMesh )
			Safe_Release( (*m_MeshArray)[i]->pMesh );

		Safe_Delete( (*m_MeshArray)[i] );
	}
	m_MeshArray->clear();
	Safe_Delete( m_MeshArray );

}

void CResourceManager::Load()
{
	if ( LoadMesh( _T( "tiger.x" ) ) == S_OK  )
	{
		if( LoadTexture( _T("tiger.x") ) == MN_TIGER )
			MessageBox(NULL, _T("Mesh/Texture Load Ok!"), _T("tiger.x"), MB_OK);
		else
			assert(false);
	}
	else
		assert(false);
}

/*
메시 로드
성공 : 해당 메시의 인덱스값 반환
실패 : -1 반환
*/
HRESULT CResourceManager::LoadMesh(LPTSTR _meshName)
{
	 m_pMesh = new MESH_INFO;

	m_pD3DXMtrlBuffer = NULL;

	const LPTSTR str = GetResourcePathT(_meshName);
	LPTSTR str2 = _T("Resources\\Mesh_Texture\\tiger.x");
	//메시 로드
	if(	D3DXLoadMeshFromX( str, D3DXMESH_SYSTEMMEM, _SINGLE(CDevice)->GetDevice(), 
		NULL, &m_pD3DXMtrlBuffer, NULL, &m_pMesh->dwNumMaterials, &m_pMesh->pMesh)		)
	{
		Safe_Delete(m_pMesh);
		MessageBox(NULL, _T("No mesh!"), _meshName, MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

int	CResourceManager::LoadTexture(LPTSTR _meshName)
{
	
	// We need to extract the material properties and texture names from the 
    // pD3DXMtrlBuffer
    D3DXMATERIAL* d3dxMaterials = ( D3DXMATERIAL* )m_pD3DXMtrlBuffer->GetBufferPointer();
	m_pMesh->pMaterials = new D3DMATERIAL9[m_pMesh->dwNumMaterials];
    m_pMesh->pTextures = new LPDIRECT3DTEXTURE9[m_pMesh->dwNumMaterials];

    if( !m_pMesh->pMaterials || !m_pMesh->pMaterials )
	{
		Safe_Delete(m_pMesh);
        return E_OUTOFMEMORY;
	}

    for( DWORD i = 0; i < m_pMesh->dwNumMaterials; i++ )
    {
        // Copy the material
        m_pMesh->pMaterials[i] = d3dxMaterials[i].MatD3D;

        // Set the ambient color for the material (D3DX does not do this)
        m_pMesh->pMaterials[i].Ambient = m_pMesh->pMaterials[i].Diffuse;

		m_pMesh->pTextures[i] = NULL;

        if( d3dxMaterials[i].pTextureFilename &&
            lstrlenA( d3dxMaterials[i].pTextureFilename ) > 0 )
        {
			//텍스쳐 이름 앞에도 경로 추가
			/*CHAR* preFix = "Resources\\Mesh_Texture\\";
			CHAR filename[255];	
			strcpy_s(filename, 255, preFix);
			strcat_s(filename, 255, d3dxMaterials[i].pTextureFilename);*/
			
			
            // Create the texture
            if( FAILED( D3DXCreateTextureFromFileA( _SINGLE(CDevice)->GetDevice(),
							GetResourcePath( d3dxMaterials[i].pTextureFilename ),
							&m_pMesh->pTextures[i] ) ) )
            {
				MessageBox( NULL, _T("Could not find texture map"), _meshName, MB_OK );
				Safe_Delete(m_pMesh);
				return -1;
            }
        }
    }

	m_MeshArray->push_back(m_pMesh);
	m_pMesh = NULL;
    // Done with the material buffer
	
	Safe_Release(m_pD3DXMtrlBuffer);
	
	return m_MeshArray->size();
	
}

LPSTR CResourceManager::GetResourcePath( LPSTR _str)
{
	const CHAR* preFix = "Resources\\Mesh_Texture\\";
	CHAR filename[255];	
	strcpy_s(filename, 255, preFix);
	strcat_s(filename, 255, _str);

	return filename;
}

TCHAR* CResourceManager::GetResourcePathT( LPTSTR _str)
{
	const TCHAR preFix[] = _T("Resources\\Mesh_Texture\\");
	TCHAR filename[255];	
	_tcscpy_s(filename, 255, preFix);
	_tcscat_s(filename, 255, _str);
	
	return filename;
}

vector<MESH_INFO*>*		CResourceManager::GetMeshArray()
{
	return m_MeshArray;
}