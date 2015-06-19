#include "TerrainMesh.h"
#include "Device.h"
#include "CameraManager.h"
#include "Camera.h"
#include "Texture.h"
#include "ResourceManager.h"
#include "Shader.h"
#include "Debug.h"
#include "QuadTree.h"
#include "KeyManager.h"
#include "Mouse.h"

CTerrainMesh::CTerrainMesh(void)
	: CMesh()
	, m_pVB(NULL)
	, m_pIB(NULL)
	, m_pTexture(NULL)
	, m_strFileName("")
	, m_iTriNum(0)
	, m_QuadTree(NULL)
{
	memset(&m_tInfo, 0, sizeof(m_tInfo));
	memset(&m_tMtrl, 0, sizeof(m_tMtrl));
}


CTerrainMesh::~CTerrainMesh(void)
{
	Destroy();
}

float CTerrainMesh::GetSize()
{
	return 129 * 1.4f;
}

float CTerrainMesh::GetHeight(float fPosX, float fPosZ)
{
	//지형의 시작점을 원점으로 이동하는 변환으로 xz평면 상에서 이동
	//pV[iIndex].vPos = D3DXVECTOR3( j * m_tInfo.fCellSpacing - m_tInfo.iRow * 0.5f, 0.f, i * m_tInfo.fCellSpacing- m_tInfo.iCol * 0.5f) * 0.2f;	
	
	//fPosX = m_tInfo.iRow * 10.f + fPosX;
	//fPosZ = m_tInfo.iCol * 10.f + fPosZ;

	//셀 간격을 1로 만들어 변환 배율을 낮춤
	fPosX /= m_tInfo.fCellSpacing;
	fPosZ /= m_tInfo.fCellSpacing;

	float fRow = floorf(fPosX);
	float fCol = floorf(fPosZ);

	if(fRow < 0 || fCol < 0)
		return 0.f;

	VERTEXTERRAIN* tempVB = NULL;

	D3DXVECTOR3 vPos[4];
	memset(vPos, 0, sizeof(D3DXVECTOR3) * 4);

	m_pVB->Lock(0, 0, (void**)&tempVB, 0);

	//INDEX* pI = NULL;

	//m_pIB->Lock(0, 0, (void**)&pI, 0);

	//정점 정보 가져오기
	int iIndex = (int)(fCol * m_tInfo.iRow + fRow);
	if(iIndex < 0)
		return 0.f;
	else if(iIndex >= m_tInfo.iCol * m_tInfo.iRow)
		return 0.f;
	vPos[0] = tempVB[iIndex].vPos;
	vPos[1] = tempVB[iIndex + 1].vPos;
	vPos[2] = tempVB[iIndex + m_tInfo.iRow].vPos;
	vPos[3] = tempVB[iIndex + m_tInfo.iRow + 1].vPos;

	m_pVB->Unlock();

	//y좌표 얻기
	//비율
	float fRatioX = (fPosX - vPos[0].x) / m_tInfo.fCellSpacing;
	float fRatioZ = (fPosZ - vPos[0].z) / m_tInfo.fCellSpacing;

	
	if(fRatioX > fRatioZ)
	{
		return vPos[0].y + (vPos[1].y - vPos[0].y) * fRatioX + (vPos[2].y - vPos[0].y) * fRatioZ;

	}

	else
	{
		return vPos[0].y + (vPos[3].y - vPos[2].y) * fRatioX + (vPos[3].y - vPos[1].y) * fRatioZ;
	}
	
}

bool CTerrainMesh::GetCollisionPos(RAY& tRay)
{
	D3DXVECTOR3 vPos;
	memset(&vPos, 0, sizeof(D3DXVECTOR3));

	//충돌을 검사합니다
	//레이랑 터레인 정보랑 박는지 아닌지 검사.....
	VERTEXTERRAIN* pV = NULL;
	INDEX* pI = NULL;

	m_pVB->Lock(0, 0, (void**)&pV, 0);

	m_pIB->Lock(0, 0, (void**)&pI, 0);

	WORD wIndex = 0;

	float u = 0.f;
		float v = 0.f;
		float fDist = 0.f;

	while(wIndex < m_iTriNum)
	{
		D3DXVECTOR3 v0 = pV[pI[wIndex]._0].vPos;
		D3DXVECTOR3 v1 = pV[pI[wIndex]._1].vPos;
		D3DXVECTOR3 v2 = pV[pI[wIndex]._2].vPos;
		if(D3DXIntersectTri(&v0,
				&v1,
				&v2,
				&tRay.vOrigin,
				&tRay.vDir,
				&u,
				&v,
				&fDist))
			{
				tRay.vIntersectPos = v0 + (v1 * u - v0 * u) + (v2 * v - v0 * v);

				m_pVB->Unlock();

				m_pIB->Unlock();

				return true;
			}

		++wIndex;
	}
	

	m_pVB->Unlock();

	m_pIB->Unlock();
	//충돌될 경우 true 리턴하고 해당 값을 tRay의 인터섹트포지션에 넣어줌...
	return false;
}

HRESULT CTerrainMesh::LoadResource(const LPTSTR _meshName)
{
	TERRAININFO tInfo;
	memset(&tInfo, 0, sizeof(tInfo));
	tInfo.fHeightScale = 1.f;
	tInfo.fCellSpacing = 1.f;
	tInfo.iCol = 129;
	tInfo.iRow = 129;
	tInfo.iVtxNum = tInfo.iCol * tInfo.iRow;

	m_iTriNum = (tInfo.iCol - 1 ) * (tInfo.iRow - 1) * 2;

	if(!CreateTerrainInfo(tInfo))
		return E_FAIL;

	return S_OK;
}

void CTerrainMesh::Render(CShader* pShader, const UINT& uPass)
{
	LPDWORD		pI = NULL;
	if( FAILED( m_pIB->Lock( 
		0, (m_tInfo.iCol-1)*(m_tInfo.iRow-1)*2 * sizeof(INDEX), (void**)&pI, 0 ) ) )
        return ;

	m_iTriNum = m_QuadTree->GenerateIndex( pI, m_pvHeightMap, _SINGLE(CFrustum) );
    m_pIB->Unlock();
	//D3DXMATRIX matWorld;
	//D3DXMatrixIdentity(&matWorld);

	//_SINGLE(CDevice)->GetDevice()->SetTransform(D3DTS_WORLD, &matWorld);
	//_SINGLE(CDevice)->GetDevice()->SetTexture(0, m_pTexture->GetTextureInfo());
	m_pTexture->SetTexture();
	//_SINGLE(CDevice)->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	//_SINGLE(CDevice)->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	//_SINGLE(CDevice)->GetDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_NEVER);
	//_SINGLE(CDevice)->GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pShader->BeginPass(uPass);

	_SINGLE(CDevice)->GetDevice()->SetStreamSource(0, m_pVB, 0, sizeof(_tagTerrainVertex));
	_SINGLE(CDevice)->GetDevice()->SetFVF(VTXTERRAINFVF);
	_SINGLE(CDevice)->GetDevice()->SetIndices(m_pIB);

	//_SINGLE(CDevice)->GetDevice()->SetRenderState(D3DRS_LIGHTING, false);
	if(GetAsyncKeyState(VK_LSHIFT) & 0x8000)
		_SINGLE(CDevice)->GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	else
		_SINGLE(CDevice)->GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	
	_SINGLE(CDevice)->GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_tInfo.iVtxNum,
		0, m_iTriNum);
	//_SINGLE(CDevice)->GetDevice()->SetRenderState(D3DRS_LIGHTING, true);
	//_SINGLE(CDevice)->GetDevice()->SetTexture(0, NULL);
	//_SINGLE(CDevice)->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pShader->EndPass();
//터레인 폴리곤 수 추가
#ifdef _DEBUG
	_SINGLE(CDebug)->AddFaceCount( (UINT)m_iTriNum );
#endif

}

bool CTerrainMesh::CreateTerrainInfo(const TERRAININFO& tInfo)
{
	m_tInfo = tInfo;

	if(!CreateVertexInfo())
		return false;

	if(!CreateIndexInfo())
		return false;

	
	m_QuadTree = new CQuadTree( m_tInfo.iRow, m_tInfo.iCol );
	
	m_QuadTree->Build( m_pvHeightMap );
	return true;
}

bool CTerrainMesh::CreateVertexInfo()
{
	if(_SINGLE(CDevice)->GetDevice()->CreateVertexBuffer(
		m_tInfo.iVtxNum * sizeof(VERTEXTERRAIN),
		D3DUSAGE_WRITEONLY,	VTXTERRAINFVF, D3DPOOL_MANAGED, &m_pVB, 0))
	{
		Safe_Release(m_pVB);
		return false;
	}

	//if(FAILED(D3DXCreateTextureFromFile(_SINGLE(CDevice)->GetDevice(), L"heightmap.bmp", &m_pTexture)))
	//{
	//	if(FAILED(D3DXCreateTextureFromFile(_SINGLE(CDevice)->GetDevice(), L"..\\heightmap.bmp", &m_pTexture)))
	//	{
	//		Safe_Release(m_pTexture);
	//		return false;
	//	}
	//}
	m_pTexture = _SINGLE(CResourceManager)->LoadTexture("Height", L"heightmap.bmp");
	m_pTexture->SetTextureName("heightmap.bmp");

	BITMAPFILEHEADER	fh;
	BITMAPINFOHEADER	ih;
	DWORD*				pPixel	= NULL;

	HANDLE		hFile	= NULL;

	hFile	= CreateFile( L"heightmap.bmp", GENERIC_READ, 0, 0,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	DWORD	dwRead	= 0;

	ReadFile(hFile, &fh, sizeof(fh), &dwRead, 0);
	ReadFile(hFile, &ih, sizeof(ih), &dwRead, 0);

	pPixel	= new DWORD[ih.biHeight * ih.biWidth];

	ReadFile(hFile, pPixel, sizeof(DWORD) * ih.biHeight * ih.biWidth,
		&dwRead, 0);

	CloseHandle(hFile);

	VERTEXTERRAIN* pV = NULL;
	
	m_pvHeightMap = new VERTEXTERRAIN[m_tInfo.iCol * m_tInfo.iRow];
	m_pVB->Lock(0, 0, (void**)&pV, 0);

	for(int i = 0; i < m_tInfo.iCol; ++i)
	{
		for(int j = 0; j < m_tInfo.iRow; ++j)
		{
			int iIndex = i * m_tInfo.iRow + j;
			//pV[iIndex].vPos = D3DXVECTOR3( j * m_tInfo.fCellSpacing - m_tInfo.iRow * 0.5f, 0.f, i * m_tInfo.fCellSpacing- m_tInfo.iCol * 0.5f) * 0.2f;	
			pV[iIndex].vPos = D3DXVECTOR3( j * m_tInfo.fCellSpacing, 0.f, i * m_tInfo.fCellSpacing)/* * 0.2f*/;	
			pV[iIndex].vPos.y = (pPixel[iIndex] & 0x000000ff) * 0.05f;
			//if(pPixel[iIndex] & 0x000000ff >= 200)
			//	pV[iIndex].vPos.y = 10.f;
			//else if(pPixel[iIndex] & 0x000000ff >= 100)
			//	pV[iIndex].vPos.y = 5.f;
			//else
			//	pV[iIndex].vPos.y = 0.f;
			pV[iIndex].vTex = D3DXVECTOR2( float(j) / (m_tInfo.iRow - 1.f), 1.f - float(i) / (m_tInfo.iCol - 1.f));
			pV[iIndex].vNormal = D3DXVECTOR3(0.f, 1.f, 0.f);
			m_pvHeightMap[iIndex] = pV[iIndex];
		}
	}

	m_pVB->Unlock();	
	//지형 분할 시작
	Safe_Delete(pPixel);
	return true;
}


bool CTerrainMesh::CreateIndexInfo()
{
	INDEX* pI = NULL;

	if(FAILED(_SINGLE(CDevice)->GetDevice()->CreateIndexBuffer(
		sizeof(INDEX) * m_iTriNum,
			0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIB, NULL)))
	{
		Safe_Release(m_pIB);
		return false;
	}

	m_pIB->Lock(0, 0, (void**)&pI, 0);

	LONG64 iTriNum = 0;
	for(int i = 0; i < m_tInfo.iCol - 1; ++i)
	{
		for(int j = 0; j < m_tInfo.iRow - 1; ++j)
		{
			WORD iIndex = WORD(i * m_tInfo.iRow + j);
			//인덱스는 삼각형 그리는 순서를 셋팅하는 것
			//x, z가 한 번씩 증가할 때 사각형 하나가 만들어지므로 for문 한 번에 두 개 정의
			pI[iTriNum]._0 = iIndex + (WORD)m_tInfo.iRow;
			pI[iTriNum]._1 = iIndex + (WORD)m_tInfo.iRow + 1;
			pI[iTriNum]._2 = iIndex + 1;
			++iTriNum;
 
			pI[iTriNum]._0 = iIndex + (WORD)m_tInfo.iRow;
			pI[iTriNum]._1 = iIndex + 1;
			pI[iTriNum]._2 = iIndex;
			++iTriNum;
		}
	}

	return true;
}

void CTerrainMesh::Destroy()
{
	Safe_Release(m_pVB);
	Safe_Release(m_pIB);
	Safe_Delete(m_QuadTree);
	Safe_Delete_Array(m_pvHeightMap);

}