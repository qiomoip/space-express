#pragma once
#include "Mesh.h"

class CTerrainMesh
	: public CMesh
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
	void Render();
	void Destroy();

public:
	HRESULT LoadResource(const LPTSTR szMeshName);

public:
	bool CreateVertexInfo();
	bool CreateIndexInfo();
	bool CreateTerrainInfo(const TERRAININFO& tInfo);

public:
	CTerrainMesh(void);
	~CTerrainMesh(void);
};

