#include "TerrainMesh.h"
#include "Device.h"

CTerrainMesh::CTerrainMesh(void)
	: m_pVB(NULL)
	, m_pIB(NULL)
	, m_pPos(NULL)
	, m_strFileName("")
{
	memset(&m_tInfo, 0, sizeof(m_tInfo));
	memset(&m_tMtrl, 0, sizeof(m_tMtrl));
}


CTerrainMesh::~CTerrainMesh(void)
{
}

void CTerrainMesh::Initialize()
{
	CreateTerrainInfo();
}

void CTerrainMesh::Render()
{
}

bool CTerrainMesh::CreateTerrainInfo()
{
	HRESULT hr = 0;

	hr = _SINGLE(CDevice)->GetDevice()->CreateVertexBuffer(
		m_tInfo.m_iVtxNum * sizeof(VERTEXTERRAIN),
		D3DUSAGE_WRITEONLY,	VTXTERRAINFVF, D3DPOOL_MANAGED, &m_pVB, 0);

	if(FAILED(hr))
		return false;

	VERTEXTERRAIN* pV = NULL;

	m_pVB->Lock(0, 0, (void**)&pV, 0);

	for(int i = 0; i < m_tInfo.m_iCol; ++i)
	{
		for(int j = 0; j < m_tInfo.m_iRow; ++j)
		{
			int iIndex = i * m_tInfo.m_iRow + j;
			pV[iIndex].vPos = D3DXVECTOR3(i * m_tInfo.m_iCellSpacing, 0.f, j * m_tInfo.m_iCellSpacing);
			pV[iIndex].vTex = D3DXVECTOR2(j * 1.0f / (float)m_tInfo.m_iRow, i * 1.0f / (float)m_tInfo.m_iCol);
		}
	}

	m_pVB->Unlock();


	return true;
}