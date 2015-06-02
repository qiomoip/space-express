#pragma once
#include "mesh.h"
class CGridMesh :
	public CMesh
{
private:
	private:
	LPDIRECT3DVERTEXBUFFER9		m_pGridVB;
	LPDIRECT3DVERTEXBUFFER9		m_pLineVB;
	D3DMATERIAL9				m_tGridMaterial;
	int							m_iCnt;

public:
	HRESULT LoadResource(const LPTSTR szMeshName);
	void Render(CShader* pShader, const UINT& uPass);
	void Destroy();

public:
	float GetSize();

public:
	HRESULT CreateVertexBuffer();

public:
	CGridMesh(void);
	~CGridMesh(void);
};

