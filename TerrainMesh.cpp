#include "TerrainMesh.h"
#include "Device.h"
#include "CameraManager.h"
#include "Camera.h"

CTerrainMesh::CTerrainMesh(void)
	: m_pVB(NULL)
	, m_pIB(NULL)
	, m_pTexture(NULL)
	, m_strFileName("")
{
	memset(&m_tInfo, 0, sizeof(m_tInfo));
	memset(&m_tMtrl, 0, sizeof(m_tMtrl));
}


CTerrainMesh::~CTerrainMesh(void)
{
	Destroy();
}

void CTerrainMesh::Initialize()
{
	TERRAININFO tInfo;
	memset(&tInfo, 0, sizeof(tInfo));
	tInfo.fHeightScale = 1.f;
	tInfo.fCellSpacing = 1.f;
	tInfo.iCol = 129;
	tInfo.iRow = 129;
	tInfo.iVtxNum = tInfo.iCol * tInfo.iRow;

	m_iTriNum = (tInfo.iCol - 1 ) * (tInfo.iRow - 1) * 2;

	CreateTerrainInfo(tInfo);
}

void CTerrainMesh::Render()
{
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);

	_SINGLE(CDevice)->GetDevice()->SetTransform(D3DTS_WORLD, &matWorld);
	_SINGLE(CDevice)->GetDevice()->SetTexture(0, m_pTexture);
	//_SINGLE(CDevice)->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	//_SINGLE(CDevice)->GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	//_SINGLE(CDevice)->GetDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_NEVER);

	_SINGLE(CDevice)->GetDevice()->SetStreamSource(0, m_pVB, 0, sizeof(_tagTerrainVertex));
	_SINGLE(CDevice)->GetDevice()->SetFVF(VTXTERRAINFVF);
	_SINGLE(CDevice)->GetDevice()->SetIndices(m_pIB);
	_SINGLE(CDevice)->GetDevice()->SetRenderState(D3DRS_LIGHTING, false);
	//_SINGLE(CDevice)->GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//_SINGLE(CDevice)->GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	_SINGLE(CDevice)->GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_tInfo.iVtxNum,
		0, m_iTriNum);
	_SINGLE(CDevice)->GetDevice()->SetRenderState(D3DRS_LIGHTING, true);
	_SINGLE(CDevice)->GetDevice()->SetTexture(0, NULL);
	//_SINGLE(CDevice)->GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

}

bool CTerrainMesh::CreateTerrainInfo(const TERRAININFO& tInfo)
{
	m_tInfo = tInfo;

	if(!CreateVertexInfo())
		return false;

	if(CreateIndexInfo())
		return false;

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

	if(FAILED(D3DXCreateTextureFromFile(_SINGLE(CDevice)->GetDevice(), L"heightmap.bmp", &m_pTexture)))
	{
		if(FAILED(D3DXCreateTextureFromFile(_SINGLE(CDevice)->GetDevice(), L"..\\heightmap.bmp", &m_pTexture)))
		{
			Safe_Release(m_pTexture);
			return false;
		}
	}

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

	m_pVB->Lock(0, 0, (void**)&pV, 0);

	for(int i = 0; i < m_tInfo.iCol; ++i)
	{
		for(int j = 0; j < m_tInfo.iRow; ++j)
		{
			int iIndex = i * m_tInfo.iRow + j;
			pV[iIndex].vPos = D3DXVECTOR3( j * m_tInfo.fCellSpacing - m_tInfo.iRow * 0.5f, 0.f, i * m_tInfo.fCellSpacing- m_tInfo.iCol * 0.5f) * 0.2f;	
			pV[iIndex].vPos.y = (pPixel[iIndex] & 0x000000ff) * 0.05f;
			//if(pPixel[iIndex] & 0x000000ff >= 200)
			//	pV[iIndex].vPos.y = 10.f;
			//else if(pPixel[iIndex] & 0x000000ff >= 100)
			//	pV[iIndex].vPos.y = 5.f;
			//else
			//	pV[iIndex].vPos.y = 0.f;
			pV[iIndex].vTex = D3DXVECTOR2( float(j) / (m_tInfo.iRow - 1.f), 1.f - float(i) / (m_tInfo.iCol - 1.f));
			pV[iIndex].vNormal = D3DXVECTOR3(0.f, 1.f, 0.f);
		}
	}

	m_pVB->Unlock();
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
			int iIndex = i * m_tInfo.iRow + j;
			//인덱스는 삼각형 그리는 순서를 셋팅하는 것
			//x, z가 한 번씩 증가할 때 사각형 하나가 만들어지므로 for문 한 번에 두 개 정의
			pI[iTriNum]._0 = iIndex + m_tInfo.iRow;
			pI[iTriNum]._1 = iIndex + m_tInfo.iRow + 1;
			pI[iTriNum]._2 = iIndex + 1;
			++iTriNum;
 
			pI[iTriNum]._0 = iIndex + m_tInfo.iRow;
			pI[iTriNum]._1 = iIndex + 1;
			pI[iTriNum]._2 = iIndex;
			++iTriNum;
		}
	}

	m_pIB->Unlock();
	return true;
}

void CTerrainMesh::Destroy()
{
	Safe_Release(m_pTexture);
	Safe_Release(m_pVB);
	Safe_Release(m_pIB);

}