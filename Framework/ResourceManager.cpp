#include "ResourceManager.h"
#include "Device.h"
#include "TString.h"
#include "TerrainMesh.h"
#include "StaticMesh.h"

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
	m_mapMesh = new map<string, CMesh*>;
}

void CResourceManager::CleanUp()
{
	/*for(UINT i = 0; i < m_MeshArray->size(); ++i)
	{
		if( (*m_MeshArray)[i]->pMaterials )
			Safe_Delete_Array( (*m_MeshArray)[i]->pMaterials );
		if( (*m_MeshArray)[i]->pName)
			Safe_Delete_Array((*m_MeshArray)[i]->pName);
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
		{
			
			Safe_Release( (*m_MeshArray)[i]->pMesh );
		}

		Safe_Delete( (*m_MeshArray)[i] );
	}
	m_MeshArray->clear();
	Safe_Delete( m_MeshArray );*/

	Safe_Delete_Map(*m_mapMesh);
	Safe_Delete(m_mapMesh);
}

void CResourceManager::Load(const eMESH_TYPE& eMeshType, const string& strMeshKey, const LPTSTR szMeshName)
{
	CMesh* pMesh = LoadMesh(eMeshType, strMeshKey, szMeshName);
	if(!pMesh)
		return;

	if( SUCCEEDED(LoadTexture(LoadMesh(MT_STATIC, strMeshKey, szMeshName )) ) )
			MessageBox(NULL, _T("Mesh/Texture Load Ok!"), _T("tiger.x"), MB_OK);
		else
			assert(false);
}

/*
메시 로드
성공 : 해당 메쉬의 포인터 리턴
실패 : NULL 반환
*/
CMesh* CResourceManager::LoadMesh(const eMESH_TYPE& eMeshType, const string& strMeshKey, const LPTSTR _meshName)
{
	
	
	map<string, CMesh*>::iterator iter = m_mapMesh->find(strMeshKey);
	if(iter != m_mapMesh->end())
		return iter->second;

	CMesh* pMesh = NULL;

	switch (eMeshType)
	{
	case MT_NULL:
		break;
	case MT_ANI:
		break;
	case MT_STATIC:
		{
			pMesh = new CStaticMesh;
		}
		break;
	case MT_TEXTURE:
		{
		}
		break;
	case MT_TERRAIN:
		{
			pMesh = new CTerrainMesh;
		}
		break;
	default:
		break;
	}
	if(FAILED(pMesh->LoadResource(_meshName)))
	{
		Safe_Delete(pMesh);
		return NULL;
	}
	// MESH_INFO* pMesh = new MESH_INFO;
	// memset(pMesh, 0, sizeof(MESH_INFO));

	//m_pD3DXMtrlBuffer = NULL;

	//LPTSTR str = GetResourcePathT(_meshName);

	////메시 로드
	//if(	D3DXLoadMeshFromX( str, D3DXMESH_SYSTEMMEM, _SINGLE(CDevice)->GetDevice(), 
	//	NULL, &m_pD3DXMtrlBuffer, NULL, &pMesh->dwNumMaterials, &pMesh->pMesh)		)
	//{
	//	Safe_Delete_Array(str);
	//	Safe_Delete(pMesh);
	//	MessageBox(NULL, _T("No mesh!"), _meshName, MB_OK);
	//	return NULL;
	//}
	//pMesh->pName = new TCHAR[256];
	//_tcscpy(pMesh->pName, _meshName);
	//Safe_Delete_Array(str);

	m_mapMesh->insert(map<string, CMesh*>::value_type(strMeshKey, pMesh));

	return pMesh;
}

HRESULT	CResourceManager::LoadTexture(CMesh* pMesh)
{
	return S_OK;
	//if(!pMesh)
	//	return E_FAIL;

	//if(!pMeshInfo)
	//	return E_FAIL;
	//// We need to extract the material properties and texture names from the 
 //   // pD3DXMtrlBuffer
 //   D3DXMATERIAL* d3dxMaterials = ( D3DXMATERIAL* )m_pD3DXMtrlBuffer->GetBufferPointer();
	//_TD3DXMATERIAL mMaterial;
	//memset(&mMaterial, 0, sizeof(_TD3DXMATERIAL));
	//mMaterial.MatD3D = d3dxMaterials->MatD3D;
	///*MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, d3dxMaterials->pTextureFilename, strlen(d3dxMaterials->pTextureFilename) + 1,
	//	mMaterial.pTextureFilename, _tcslen(mMaterial.pTextureFilename) + 1);*/
	//mMaterial.pTextureFilename = _SINGLE(CTString)->CharToTCHAR(d3dxMaterials->pTextureFilename);

	//pMeshInfo->pMaterials = new D3DMATERIAL9[pMeshInfo->dwNumMaterials];
 //   pMeshInfo->pTextures = new LPDIRECT3DTEXTURE9[pMeshInfo->dwNumMaterials];

 //   if( !pMeshInfo->pMaterials || !pMeshInfo->pMaterials )
	//{
	//	Safe_Delete(pMeshInfo);
 //       return E_OUTOFMEMORY;
	//}

 //   for( DWORD i = 0; i < pMeshInfo->dwNumMaterials; i++ )
 //   {
 //       // Copy the material
 //       pMeshInfo->pMaterials[i] = d3dxMaterials[i].MatD3D;

 //       // Set the ambient color for the material (D3DX does not do this)
 //       pMeshInfo->pMaterials[i].Ambient = pMeshInfo->pMaterials[i].Diffuse;

	//	pMeshInfo->pTextures[i] = NULL;

 //       if( d3dxMaterials[i].pTextureFilename &&
 //           lstrlenA( d3dxMaterials[i].pTextureFilename ) > 0 )
 //       {
	//		//텍스쳐 이름 앞에도 경로 추가
	//		/*CHAR* preFix = "Resources\\Mesh_Texture\\";
	//		CHAR filename[255];	
	//		strcpy_s(filename, 255, preFix);
	//		strcat_s(filename, 255, d3dxMaterials[i].pTextureFilename);*/
	//		
	//		
 //           // Create the texture
	//		LPTSTR szPath = GetResourcePathT( mMaterial.pTextureFilename);
 //           if( FAILED( D3DXCreateTextureFromFile( _SINGLE(CDevice)->GetDevice(),
	//			szPath,
	//						&pMeshInfo->pTextures[i] ) ) )
 //           {
	//			MessageBox( NULL, _T("Could not find texture map"), pMeshInfo->pName, MB_OK );
	//			Safe_Delete(pMeshInfo);
	//			Safe_Delete(szPath);
	//			return E_FAIL;
 //           }
	//		Safe_Delete_Array(szPath);
 //       }
 //   }

	//m_MeshArray->push_back(pMeshInfo);
 //   // Done with the material buffer
	//
	//Safe_Release(m_pD3DXMtrlBuffer);

	//Safe_Delete_Array(mMaterial.pTextureFilename);
	//
	//return S_OK;
	
}

LPSTR CResourceManager::GetResourcePath(const LPSTR _str)
{
	const CHAR* preFix = "Resources\\Mesh_Texture\\";
	//CHAR filename[255];	
	CHAR* pFileName = new CHAR[256];
	strcpy_s(pFileName, 255, preFix);
	strcat_s(pFileName, 255, _str);

	return pFileName;
}

TCHAR* CResourceManager::GetResourcePathT(const LPTSTR _str)
{
	const TCHAR preFix[] = _T("Resources\\Mesh_Texture\\");
	//TCHAR filename[255];	
	TCHAR* pFileName = new TCHAR[256];
	_tcscpy_s(pFileName, 256, preFix);
	_tcscat_s(pFileName, 256, _str);
	
	return pFileName;
}

const map<string, CMesh*>*		CResourceManager::GetMeshList() const
{
	return m_mapMesh;
}