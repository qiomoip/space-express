#pragma once
#include "define.h"

class CTerrainMesh
{
private:
	LPDIRECT3DVERTEXBUFFER9		m_pVB;
	LPDIRECT3DINDEXBUFFER9		m_pIB;
	LPDIRECT3DTEXTURE9			m_pTexture;

	TERRAININFO					m_tInfo;
	D3DMATERIAL9				m_tMtrl;
	string						m_strFileName;
	int							m_iTriNum;

public:
	void Initialize();
	void Render();
	void Destroy();

public:
	bool CreateVertexInfo();
	bool CreateIndexInfo();
	bool CreateTerrainInfo(const TERRAININFO& tInfo);

public:
	CTerrainMesh(void);
	~CTerrainMesh(void);
};

