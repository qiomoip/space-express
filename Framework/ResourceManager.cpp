#include "ResourceManager.h"
#include "Device.h"
#include "TString.h"
#include "TerrainMesh.h"
#include "StaticMesh.h"
#include "Texture.h"
#include "GridMesh.h"
#include "BoxMesh.h"

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
	m_mapMesh = new map<eMESH_NUM, CMesh*>;
}

void CResourceManager::CleanUp()
{
	Safe_Delete_Map(m_mapTexture);
	Safe_Delete_Map(*m_mapMesh);
	Safe_Delete(m_mapMesh);
}

CMesh* CResourceManager::Load(const eMESH_TYPE& eMeshType, const eMESH_NUM& eMeshNum, const LPTSTR szMeshName)
{
	CMesh* pMesh = LoadMesh(eMeshType, eMeshNum, szMeshName);
	if(!pMesh)
	{
		return NULL;
	}

	//if( SUCCEEDED(LoadTexture(pMesh) ))
	//{
	//	MessageBox(NULL, _T("Mesh/Texture Load Ok!"), szMeshName, MB_OK);
	//	return pMesh;
	//}
	//else
	//{
	//	Safe_Delete(pMesh);
	//	assert(false);
	//	return NULL;
	//}
	return pMesh;
}

/*
메시 로드
성공 : 해당 메쉬의 포인터 리턴
실패 : NULL 반환
*/
CMesh* CResourceManager::LoadMesh(const eMESH_TYPE& eMeshType, const eMESH_NUM& eMeshNum, const LPTSTR _meshName)
{
	map<eMESH_NUM, CMesh*>::iterator iter = m_mapMesh->find(eMeshNum);
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
	case MT_BOX:
		{
			pMesh = new CBoxMesh;
		}
		break;
#ifdef _DEBUG
	case MT_GRID:
		{
			pMesh = new CGridMesh;
		}
		break;
#endif
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

	m_mapMesh->insert(map<eMESH_NUM, CMesh*>::value_type(eMeshNum, pMesh));

	return pMesh;
}

CTexture*	CResourceManager::LoadTexture(const string& strTextureKey, const LPTSTR _texname)
{
	map<string, CTexture*>::iterator iter = m_mapTexture.find(strTextureKey);
	if(iter != m_mapTexture.end())
		return iter->second;
	CTexture* pTexture = new CTexture;
	LPDIRECT3DTEXTURE9 pTex = NULL;
	// Create the texture
	LPTSTR szPath = GetResourcePathT(_texname);
	if( FAILED( D3DXCreateTextureFromFile( _SINGLE(CDevice)->GetDevice(),
		szPath,
		&pTex ) ) )
	{
		MessageBox( NULL, _T("Could not find texture map"), _texname, MB_OK );
		Safe_Delete(pTexture);
		Safe_Delete_Array(szPath);
		return NULL;
	}
	Safe_Delete_Array(szPath);
	pTexture->SetTextureInfo(pTex);

	CHAR szRet[256];
			memset(szRet, 0, sizeof(char) * 256);
			int len = WideCharToMultiByte( CP_ACP, 0, _texname, -1, NULL, 0, NULL, NULL );	
			WideCharToMultiByte( CP_ACP, 0, _texname, -1, szRet, len, NULL, NULL );

	pTexture->SetTextureName(szRet);
	m_mapTexture.insert(map<string, CTexture*>::value_type(strTextureKey, pTexture));
	return pTexture;

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

const map<eMESH_NUM, CMesh*>*		CResourceManager::GetMeshList() const
{
	return m_mapMesh;
}