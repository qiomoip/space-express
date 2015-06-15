#include "StaticMesh.h"
#include "Device.h"
#include "ResourceManager.h"
//#include "TString.h"
#include "Texture.h"
#include "Shader.h"
#include "Debug.h"

CStaticMesh::CStaticMesh(void)
	: m_pMeshInfo(NULL)
	, m_pD3DXMtrlBuffer(NULL)
	
{
	m_ColType = MT_STATIC;
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
		MessageBox(NULL, _T("No mesh!"), szMeshName, MB_OK);
		return E_FAIL;
	}
	//로드한 x파일의 사이즈 구하기
	GetSize();

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
	mMaterial.pTextureFilename = new TCHAR[255];

	mMaterial.MatD3D = d3dxMaterials->MatD3D;
	MultiByteToWideChar(
		CP_ACP, MB_PRECOMPOSED, 
		d3dxMaterials->pTextureFilename, 
		strlen(d3dxMaterials->pTextureFilename) + 1,
		mMaterial.pTextureFilename , 
		_tcslen(mMaterial.pTextureFilename ) + 1);

	m_pMeshInfo->pMaterials = new D3DMATERIAL9[m_pMeshInfo->dwNumMaterials];
	m_arrayTexture = new CTexture*[m_pMeshInfo->dwNumMaterials];
	//m_pMeshInfo->pTextures = new LPDIRECT3DTEXTURE9[m_pMeshInfo->dwNumMaterials];

	if( !m_pMeshInfo->pMaterials  )
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

		//m_pMeshInfo->pTextures[i] = NULL;

		if( d3dxMaterials[i].pTextureFilename &&
			lstrlenA( d3dxMaterials[i].pTextureFilename ) > 0 )
		{
			LPSTR szRet = new CHAR[255];
			
			int len = WideCharToMultiByte( CP_ACP, 0, mMaterial.pTextureFilename, -1, NULL, 0, NULL, NULL );	
			WideCharToMultiByte( CP_ACP, 0, mMaterial.pTextureFilename, -1, szRet, len, NULL, NULL );
			/*LPSTR szRet= new CHAR[256];
			memset(szRet, 0, sizeof(char) * 256);
			/*int len = WideCharToMultiByte( CP_ACP, 0, mMaterial.pTextureFilename, -1, NULL, 0, NULL, NULL );	
			WideCharToMultiByte( CP_ACP, 0, mMaterial.pTextureFilename, -1, szRet, len, NULL, NULL );
*/
			//WideCharToMultiByte(CP_ACP, MB_PRECOMPOSED, mMaterial.pTextureFilename, _tcslen(mMaterial.pTextureFilename) + 1,
			//	szRet, 256 , NULL, NULL);

			CTexture* pTexture = _SINGLE(CResourceManager)->LoadTexture(szRet, mMaterial.pTextureFilename);
			if(!pTexture)
			{
				Safe_Delete_Array(szRet);
				Safe_Delete(pTexture);
				return E_FAIL;
			}
			Safe_Delete_Array(szRet);
//			m_vecTexture.push_back(pTexture);
			m_arrayTexture[i] = pTexture;
		}
	}

	// Done with the material buffer

	Safe_Release(m_pD3DXMtrlBuffer);

	Safe_Delete_Array(mMaterial.pTextureFilename);

	return S_OK;
}
void CStaticMesh::SetSize()
{
	if(m_pMeshInfo->pMesh )	
	{
		D3DXVECTOR3 vCenter = D3DXVECTOR3(0,0,0);
		float		fRadius = 0.f;
		DWORD dwVertexNum = m_pMeshInfo->pMesh->GetNumVertices();
		DWORD dwBytes = m_pMeshInfo->pMesh->GetNumBytesPerVertex();
		BYTE* ppVB = NULL;

		m_pMeshInfo->pMesh->LockVertexBuffer( 0, (VOID**) &ppVB);

		HRESULT hr = D3DXComputeBoundingSphere( 
			(D3DXVECTOR3*)ppVB, 
			dwVertexNum,
			dwBytes,
			&vCenter,
			&fRadius);

		if (hr == S_OK)
			m_pMeshInfo->fSize = fRadius;

		m_pMeshInfo->pMesh->UnlockVertexBuffer();
	}
}


float CStaticMesh::GetSize() 
{
	return m_pMeshInfo->fSize/2.0f;
}


void CStaticMesh::Render(CShader* pShader, const UINT& uPass)
{
	//_SINGLE(CDevice)->GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
	
	for( DWORD i = 0; i < m_pMeshInfo->dwNumMaterials; i++ )
	{
		// Set the material and texture for this subset
		//_SINGLE(CDevice)->GetDevice()->SetMaterial( &m_pMeshInfo->pMaterials[i] );
		pShader->SetValue("g_mtrlMesh", &m_pMeshInfo->pMaterials[i], sizeof(D3DMATERIAL9) );
		// _SINGLE(CDevice)->GetDevice()->SetTexture( 0, m_pMeshInfo->pTextures[i] );
//		m_vecTexture[i]->SetTexture();
		m_arrayTexture[i]->SetTexture();

		// Draw the mesh subset
		pShader->BeginPass(uPass);
		m_pMeshInfo->pMesh->DrawSubset( i );
		pShader->EndPass();
		

	}
#ifdef _DEBUG
	_SINGLE(CDebug)->AddFaceCount( (UINT)m_pMeshInfo->pMesh->GetNumFaces() );
	pShader->BeginPass(PASS_NOTEXTURE);

	//_SINGLE(CDebug)->DrawSphere(m_pMeshInfo->fSize * 0.5f);	
	//경계구 그리기
	/*LPD3DXMESH _mesh = NULL;
	HRESULT r = D3DXCreateSphere( _SINGLE(CDevice)->GetDevice(),
		 m_pMeshInfo->fSize * 5.f , (UINT)8, (UINT)8, &_mesh, NULL);
	
	r = _mesh->DrawSubset(0);	
	Safe_Release( _mesh);*/

	
	#endif
	pShader->EndPass();
	
	//_SINGLE(CDevice)->GetDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);
}

const LPD3DXMESH CStaticMesh::GetMesh() const 
{
	return m_pMeshInfo->pMesh;
}


void CStaticMesh::Destroy()
{

	if( m_pMeshInfo->pMaterials )
		Safe_Delete_Array(m_pMeshInfo->pMaterials);
	if( m_pMeshInfo->pName)
		Safe_Delete_Array(m_pMeshInfo->pName);
	//if( m_pMeshInfo->pTextures )
	//{
	//	for( DWORD j = 0; j < m_pMeshInfo->dwNumMaterials; ++j)
	//	{
	//		if( m_pMeshInfo->pTextures[j] )
	//			Safe_Release( m_pMeshInfo->pTextures[j] );
	//	}
	//	Safe_Delete_Array( m_pMeshInfo->pTextures );
	//}
	if( m_pMeshInfo->pMesh )
	{

		Safe_Release( m_pMeshInfo->pMesh );
	}

	Safe_Delete( m_pMeshInfo );
}

 const eMESH_TYPE CStaticMesh::GetType() const 
{
	return m_ColType;
}
