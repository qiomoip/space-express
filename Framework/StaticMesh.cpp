#include "StaticMesh.h"
#include "Device.h"
#include "ResourceManager.h"
#include "TString.h"
#include "Texture.h"

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
	//_TD3DXMATERIAL mMaterial;
	//memset(&mMaterial, 0, sizeof(_TD3DXMATERIAL));
	//mMaterial.MatD3D = d3dxMaterials->MatD3D;

	//mMaterial.pTextureFilename = _SINGLE(CTString)->CharToTCHAR(d3dxMaterials->pTextureFilename);

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
			LPSTR szRet = new char[100];
			strcpy(szRet, d3dxMaterials[i].pTextureFilename);
			LPTSTR szFileName = _SINGLE(CTString)->CharToTCHAR(d3dxMaterials[i].pTextureFilename);

			CTexture* pTexture = _SINGLE(CResourceManager)->LoadTexture(szRet, szFileName);
			if(!pTexture)
			{
				Safe_Delete_Array(szRet);
				Safe_Delete_Array(szFileName);
				Safe_Delete(pTexture);
				return E_FAIL;
			}
			Safe_Delete_Array(szRet);
			Safe_Delete_Array(szFileName);
			m_vecTexture.push_back(pTexture);
		}
	}

	// Done with the material buffer

	Safe_Release(m_pD3DXMtrlBuffer);

	return S_OK;
}

void CStaticMesh::Render()
{
	
	
	for( DWORD i = 0; i < m_pMeshInfo->dwNumMaterials; i++ )
	{
		// Set the material and texture for this subset
		_SINGLE(CDevice)->GetDevice()->SetMaterial( &m_pMeshInfo->pMaterials[i] );
		// _SINGLE(CDevice)->GetDevice()->SetTexture( 0, m_pMeshInfo->pTextures[i] );
		m_vecTexture[i]->SetTexture();

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