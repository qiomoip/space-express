#pragma once
#include "define.h"

class CTerrainMesh
{
private:
	LPDIRECT3DVERTEXBUFFER9		m_pVB;
	LPDIRECT3DINDEXBUFFER9		m_pIB;

	TERRAININFO					m_tInfo;
	D3DXVECTOR3*				m_pPos;
	D3DMATERIAL9				m_tMtrl;
	string						m_strFileName;

public:
	void Initialize();
	void Render();

public:
	bool CreateTerrainInfo();

public:
	CTerrainMesh(void);
	~CTerrainMesh(void);
};

