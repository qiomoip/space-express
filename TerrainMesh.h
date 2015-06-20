#pragma once
#include "Mesh.h"
class CTexture;
class CQuadTree;

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

	CQuadTree*					m_QuadTree;
	VERTEXTERRAIN*				m_pvHeightMap;
	
public:
	void Render(CShader* pShader, const UINT& uPass);
	void Destroy();

public:
	//가장 멀리 있는 두 점의 거리 리턴
	float GetSize();
	//셀의 높이값 리턴
	float GetHeight(float fPosX, float fPosZ); 
	//레이가 터레인과 충돌되었는지를 검사. 여기 레이는 월드의 레이
	bool GetCollisionPos(RAY& tRay);


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

