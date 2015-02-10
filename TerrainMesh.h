#pragma once
#include "Mesh.h"
class CTexture;

class CTerrainMesh
	: public CMesh
{
private:
	LPDIRECT3DVERTEXBUFFER9		m_pVB;
	LPDIRECT3DINDEXBUFFER9		m_pIB;
	CTexture*					m_pTexture;

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
	const LPDIRECT3DVERTEXBUFFER9	GetVtxInfo() const ;
	const LPDIRECT3DINDEXBUFFER9	GetIdxInfo() const ;
	const TERRAININFO				GetTerrainInfo() const;

public:
	CTerrainMesh(void);
	~CTerrainMesh(void);
};

