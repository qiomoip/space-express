#pragma once
#include "mesh.h"
class CTexture;

class CUIMesh :
	public CMesh
{
private:
	LPDIRECT3DVERTEXBUFFER9		m_pVB;
	LPDIRECT3DINDEXBUFFER9		m_pIB;
	CTexture*					m_pTexture;

public:
	HRESULT LoadResource(const LPTSTR szMeshName);
	void Render(CShader* pShader, const UINT& uPass);
	void Destroy();
	
public:
	float GetSize();
	bool GetCollisionPos(RAY& tRay);

public:
	HRESULT CreateVertexBuffer();
	HRESULT LoadTexture(const LPTSTR _meshName );

public:
	CUIMesh(void);
	~CUIMesh(void);
};

