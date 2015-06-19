#include "StaticMesh.h"
#include "Device.h"
#include "ResourceManager.h"
//#include "TString.h"
#include "Texture.h"
#include "Shader.h"
#include "Debug.h"

CStaticMesh::CStaticMesh(void)
	: CMesh()
	, m_pMeshInfo(NULL)
	, m_pD3DXMtrlBuffer(NULL)
	, m_pDeclGeometry(NULL)
	, m_pCloneMesh(NULL)
	, m_pVB(NULL)
	, m_pIB(NULL)
	, m_pInstancingVB(NULL)
	, m_iAddInstanceData(0)
	
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

	LPD3DXBUFFER	pAdj = NULL;

	//메시 로드
	if(	D3DXLoadMeshFromX( str, D3DXMESH_SYSTEMMEM, _SINGLE(CDevice)->GetDevice(), 
		&pAdj, &m_pD3DXMtrlBuffer, NULL, &m_pMeshInfo->dwNumMaterials, &m_pMeshInfo->pMesh)		)
	{
		Safe_Delete_Array(str);
		Safe_Delete(m_pMeshInfo);
		MessageBox(NULL, _T("No mesh!"), szMeshName, MB_OK);
		return E_FAIL;
	}
	//로드한 x파일의 사이즈 구하기
	GetSize();

	Safe_Delete_Array(str);


	D3DVERTEXELEMENT9 pDecl[] =
	{
		{0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
		{0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
		{0, 24, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0},
		{0, 36, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},	
		D3DDECL_END()
	};

	LPD3DXMESH pMesh = NULL;


	m_pMeshInfo->pMesh->CloneMesh( m_pMeshInfo->pMesh->GetOptions(), pDecl,
		_SINGLE(CDevice)->GetDevice(), &pMesh );

	//포맷이 변경된 메시 데이터
	m_pCloneMesh = pMesh;

	D3DXComputeTangent(m_pCloneMesh, 0 ,0, 0, TRUE, NULL);

	//메시 최적화
		m_pCloneMesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | 
		D3DXMESHOPT_VERTEXCACHE,
		(DWORD*)pAdj->GetBufferPointer(),
		NULL, NULL, NULL);

	//이 버텍스 버퍼가 메인 버텍스 버퍼인 듯...
	m_pCloneMesh->GetVertexBuffer(&m_pVB);
	m_pCloneMesh->GetIndexBuffer(&m_pIB);

	D3DVERTEXELEMENT9	decl[MAX_FVF_DECL_SIZE]	= {0};

	//메인 메시의 선언 정보를 가져온다
	m_pCloneMesh->GetDeclaration(decl);

	//Geometry 선언 정보를 인스턴싱 데이터로 수정한다
	_SINGLE(CDevice)->GetDevice()->CreateVertexDeclaration(g_tTotalFmt,
		&m_pDeclGeometry);

	//attribute range 정보를 가져온다 (특성 테이블?)
	/*AttribId
		속성 테이블의 식별자.
	FaceStart
		시작면.
	FaceCount
		면의 수.
	VertexStart
		시작 정점.
	VertexCount
		정점의 수.*/

	m_pAttr	= new D3DXATTRIBUTERANGE[m_pMeshInfo->dwNumMaterials];

	/*속성 테이블은, 다른 텍스처, 렌더링 스테이트, 머트리얼등에 의해
	드로잉(Drawing) 할 필요가 있는 메쉬의 영역을 식별하기 위해서 사용된다. 
		한층 더 애플리케이션은, 속성 테이블을 사용해, 
		프레임의 드로잉(Drawing)시에 소정의 속성 식별자 (AttribId)를 드로잉(Drawing) 하지 않는 것에 따라, 
		메쉬의 일부를 숨길 수가 있다.*/
	m_pCloneMesh->GetAttributeTable(m_pAttr, &m_pMeshInfo->dwNumMaterials);

	//인스턴싱 버퍼 생성
	if(!m_pInstancingVB)
		_SINGLE(CDevice)->GetDevice()->CreateVertexBuffer(INSTANCING_NUM * sizeof(InstancingData),
		0, 0, D3DPOOL_MANAGED, &m_pInstancingVB,
		NULL);


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
	
	//스트림 0으로 세팅 되어있는 메인 버텍스 버퍼 바인드
	//g_NumBoxes 는 출력할 인스턴싱 데이터 개수
	

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
	//pShader->EndPass();

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

	Safe_Release(m_pCloneMesh);
	Safe_Release(m_pDeclGeometry);
	Safe_Release(m_pVB);
	Safe_Release(m_pInstancingVB);
	Safe_Release(m_pIB);
	Safe_Delete(m_pAttr);

	Safe_Delete( m_pMeshInfo );
}

 const eMESH_TYPE CStaticMesh::GetType() const 
{
	return m_ColType;
}


 
void CStaticMesh::PushInstancingData( const D3DXMATRIX& matWorld )
{
	/*if(m_iAddInstanceData >= INSTANCING_NUM)
		return;*/

	PInstancingData	pData	= NULL;

	m_pInstancingVB->Lock(m_iAddInstanceData * sizeof(InstancingData),
		sizeof(InstancingData), (void**)&pData, 0);

	memcpy(&pData->vRow1, &matWorld, sizeof(D3DXMATRIX));

	pData->vRow1;
	pData->vRow2;
	pData->vRow3;
	pData->vRow4;

	m_pInstancingVB->Unlock();

	++m_iAddInstanceData;
}

void CStaticMesh::ResetInstancingCount()
{
	m_iAddInstanceData = 0;
}

void CStaticMesh::RenderInstance(CShader* pShader, const UINT& uPass)
{
	LPDIRECT3DDEVICE9 pDevice = _SINGLE(CDevice)->GetDevice();
	pDevice->SetVertexDeclaration(m_pDeclGeometry);

	pDevice->SetStreamSourceFreq(0, 
		D3DSTREAMSOURCE_INDEXEDDATA | m_iAddInstanceData);
	pDevice->SetStreamSource(0, m_pVB, 0,
		m_pCloneMesh->GetNumBytesPerVertex());

	pDevice->SetStreamSourceFreq(1,
		D3DSTREAMSOURCE_INSTANCEDATA | 1ul);
	pDevice->SetStreamSource(1, m_pInstancingVB,
		0, sizeof(InstancingData));

	pDevice->SetIndices(m_pIB);

	int iSize = sizeof(m_arrayTexture) / sizeof(m_arrayTexture[0]);
	
	for( DWORD i = 0; i < iSize; i++ )
	{
		// Set the material and texture for this subset
		//_SINGLE(CDevice)->GetDevice()->SetMaterial( &m_pMeshInfo->pMaterials[i] );
		pShader->SetValue("g_mtrlMesh", &m_pMeshInfo->pMaterials[i], sizeof(D3DMATERIAL9) );
		// _SINGLE(CDevice)->GetDevice()->SetTexture( 0, m_pMeshInfo->pTextures[i] );
//		m_vecTexture[i]->SetTexture();
		//m_arrayTexture[i]->SetTexture();
		pShader->SetTexture("g_BaseTex", m_arrayTexture[i]->GetTextureInfo());
		
		// Draw the mesh subset
		pShader->BeginPass(uPass);
		pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
			0, 0, 
			m_pAttr[i].VertexCount,
			m_pAttr[i].FaceStart * 3,
			m_pAttr[i].FaceCount);
		pShader->EndPass();
	}

	pDevice->SetStreamSourceFreq(0, 1);
	pDevice->SetStreamSourceFreq(1, 1);
}