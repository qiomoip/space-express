#include "StaticMesh.h"
#include "Device.h"
#include "ResourceManager.h"
#include "TString.h"

CStaticMesh::CStaticMesh(void)
	: m_pMeshInfo(NULL)
	, m_pD3DXMtrlBuffer(NULL)
{

}


CStaticMesh::~CStaticMesh(void)
{
	Destroy();
}


HRESULT CStaticMesh::LoadResource(const LPTSTR szMeshName)
{
	if(FAILED(LoadMesh(szMeshName)))
		return E_FAIL;

	if(FAILED(LoadTexture()))
		return E_FAIL;

	return S_OK;
}

HRESULT CStaticMesh::LoadMesh(const LPTSTR szMeshName)
{
	m_pMeshInfo = new MESH_INFO;
	memset(m_pMeshInfo, 0, sizeof(MESH_INFO));

	m_pMeshInfo->pName = new TCHAR[256];
	_tcscpy(m_pMeshInfo->pName, szMeshName);

	m_pD3DXMtrlBuffer = NULL;

	LPTSTR str = _SINGLE(CResourceManager)->GetResourcePathT(m_pMeshInfo->pName);

	//메시 로드
	if(	D3DXLoadMeshFromX( str, D3DXMESH_SYSTEMMEM, _SINGLE(CDevice)->GetDevice(), 
		NULL, &m_pD3DXMtrlBuffer, NULL, &m_pMeshInfo->dwNumMaterials, &m_pMeshInfo->pMesh)		)
	{
		Safe_Delete_Array(str);
		Safe_Delete(m_pMeshInfo);
		MessageBox(NULL, _T("No mesh!"), m_pMeshInfo->pName, MB_OK);
		return E_FAIL;
	}
	Safe_Delete_Array(str);
	return S_OK;
}

HRESULT CStaticMesh::LoadTexture()
{
	if(!m_pMeshInfo)
		return E_FAIL;
	// We need to extract the material properties and texture names from the 
	// pD3DXMtrlBuffer
	D3DXMATERIAL* d3dxMaterials = ( D3DXMATERIAL* )m_pD3DXMtrlBuffer->GetBufferPointer();
	_TD3DXMATERIAL mMaterial;
	memset(&mMaterial, 0, sizeof(_TD3DXMATERIAL));
	mMaterial.MatD3D = d3dxMaterials->MatD3D;
	/*MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, d3dxMaterials->pTextureFilename, strlen(d3dxMaterials->pTextureFilename) + 1,
	mMaterial.pTextureFilename, _tcslen(mMaterial.pTextureFilename) + 1);*/
	mMaterial.pTextureFilename = _SINGLE(CTString)->CharToTCHAR(d3dxMaterials->pTextureFilename);

	m_pMeshInfo->pMaterials = new D3DMATERIAL9[m_pMeshInfo->dwNumMaterials];
	m_pMeshInfo->pTextures = new LPDIRECT3DTEXTURE9[m_pMeshInfo->dwNumMaterials];

	if( !m_pMeshInfo->pMaterials || !m_pMeshInfo->pMaterials )
	{
		Safe_Delete(m_pMeshInfo);
		return E_OUTOFMEMORY;
	}

	for( DWORD i = 0; i < m_pMeshInfo->dwNumMaterials; i++ )
	{
		// Copy the material
		m_pMeshInfo->pMaterials[i] = d3dxMaterials[i].MatD3D;

		// Set the ambient color for the material (D3DX does not do this)
		m_pMeshInfo->pMaterials[i].Ambient = m_pMeshInfo->pMaterials[i].Diffuse;

		m_pMeshInfo->pTextures[i] = NULL;

		if( d3dxMaterials[i].pTextureFilename &&
			lstrlenA( d3dxMaterials[i].pTextureFilename ) > 0 )
		{
			//텍스쳐 이름 앞에도 경로 추가
			/*CHAR* preFix = "Resources\\Mesh_Texture\\";
			CHAR filename[255];	
			strcpy_s(filename, 255, preFix);
			strcat_s(filename, 255, d3dxMaterials[i].pTextureFilename);*/


			// Create the texture
			LPTSTR szPath = _SINGLE(CResourceManager)->GetResourcePathT( mMaterial.pTextureFilename);
			if( FAILED( D3DXCreateTextureFromFile( _SINGLE(CDevice)->GetDevice(),
				szPath,
				&m_pMeshInfo->pTextures[i] ) ) )
			{
				MessageBox( NULL, _T("Could not find texture map"), m_pMeshInfo->pName, MB_OK );
				Safe_Delete(m_pMeshInfo);
				Safe_Delete(szPath);
				return E_FAIL;
			}
			Safe_Delete_Array(szPath);
		}
	}

	// Done with the material buffer

	Safe_Release(m_pD3DXMtrlBuffer);

	Safe_Delete_Array(mMaterial.pTextureFilename);

	return S_OK;
}

void CStaticMesh::Render()
{
	_SINGLE(CDevice)->GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
	 for( DWORD i = 0; i < m_pMeshInfo->dwNumMaterials; i++ )
        {
            // Set the material and texture for this subset
			_SINGLE(CDevice)->GetDevice()->SetMaterial( &m_pMeshInfo->pMaterials[i] );
            _SINGLE(CDevice)->GetDevice()->SetTexture( 0, m_pMeshInfo->pTextures[i] );

            // Draw the mesh subset
			m_pMeshInfo->pMesh->DrawSubset( i );
        }
}

void CStaticMesh::Destroy()
{

	if( m_pMeshInfo->pMaterials )
		Safe_Delete_Array(m_pMeshInfo->pMaterials);
	if( m_pMeshInfo->pName)
		Safe_Delete_Array(m_pMeshInfo->pName);
	if( m_pMeshInfo->pTextures )
	{
		for( DWORD j = 0; j < m_pMeshInfo->dwNumMaterials; ++j)
		{
			if( m_pMeshInfo->pTextures[j] )
				Safe_Release( m_pMeshInfo->pTextures[j] );
		}
		Safe_Delete_Array( m_pMeshInfo->pTextures );
	}
	if( m_pMeshInfo->pMesh )
	{

		Safe_Release( m_pMeshInfo->pMesh );
	}

	Safe_Delete( m_pMeshInfo );
}