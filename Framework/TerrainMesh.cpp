#include "TerrainMesh.h"
#include "Device.h"
#include "CameraManager.h"
#include "Camera.h"

CTerrainMesh::CTerrainMesh(void)
	: m_pVB(NULL)
	, m_pIB(NULL)
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
	tInfo.fHeightScale = 1.0f;
	tInfo.fCellSpacing = 0.2f;
	tInfo.iCol = 128;
	tInfo.iRow = 128;
	tInfo.iVtxNum = tInfo.iCol * tInfo.iRow;

	m_iTriNum = (tInfo.iCol - 1 ) * (tInfo.iRow - 1) * 2;

	CreateTerrainInfo(tInfo);
}

void CTerrainMesh::Render()
{
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);

	_SINGLE(CDevice)->GetDevice()->SetTransform(D3DTS_WORLD, &matWorld);

	_SINGLE(CDevice)->GetDevice()->SetStreamSource(0, m_pVB, 0, sizeof(_tagTerrainVertex));
	_SINGLE(CDevice)->GetDevice()->SetFVF(VTXTERRAINFVF);
	_SINGLE(CDevice)->GetDevice()->SetIndices(m_pIB);
	_SINGLE(CDevice)->GetDevice()->SetRenderState(D3DRS_LIGHTING, false);
	//_SINGLE(CDevice)->GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	//_SINGLE(CDevice)->GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	_SINGLE(CDevice)->GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_tInfo.iVtxNum,
		0, m_iTriNum);
	_SINGLE(CDevice)->GetDevice()->SetRenderState(D3DRS_LIGHTING, true);

}

bool CTerrainMesh::CreateTerrainInfo(const TERRAININFO& tInfo)
{
	m_tInfo = tInfo;

	if(_SINGLE(CDevice)->GetDevice()->CreateVertexBuffer(
		m_tInfo.iVtxNum * sizeof(VERTEXTERRAIN),
		D3DUSAGE_WRITEONLY,	VTXTERRAINFVF, D3DPOOL_MANAGED, &m_pVB, 0))
	{
		return false;
	}

	VERTEXTERRAIN* pV = NULL;

	m_pVB->Lock(0, 0, (void**)&pV, 0);

	for(int i = 0; i < m_tInfo.iCol; ++i)
	{
		for(int j = 0; j < m_tInfo.iRow; ++j)
		{
			int iIndex = i * m_tInfo.iRow + j;
			pV[iIndex].vPos = D3DXVECTOR3( j * m_tInfo.fCellSpacing, 0.f, i * m_tInfo.fCellSpacing);	
			pV[iIndex].vTex = D3DXVECTOR2( j / ((m_tInfo.iRow - 1.f) * m_tInfo.fCellSpacing), i / ((m_tInfo.iCol - 1.f) * m_tInfo.fCellSpacing) );
			pV[iIndex].vNormal = D3DXVECTOR3(0.f, 1.f, 0.f);
		}
	}

	m_pVB->Unlock();

	INDEX* pI = NULL;

	if(FAILED(_SINGLE(CDevice)->GetDevice()->CreateIndexBuffer(
		sizeof(INDEX) * m_iTriNum,
			0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIB, NULL)))
	{
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
	Safe_Release(m_pVB);
	Safe_Release(m_pIB);

}