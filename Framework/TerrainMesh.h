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
	//���� �ָ� �ִ� �� ���� �Ÿ� ����
	float GetSize();
	//���� ���̰� ����
	float GetHeight(float fPosX, float fPosZ); 
	//���̰� �ͷ��ΰ� �浹�Ǿ������� �˻�. ���� ���̴� ������ ����
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

