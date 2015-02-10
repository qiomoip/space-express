#pragma once
#include "Mesh.h"

class CStaticMesh
	: public CMesh
{
private:
	MESH_INFO*			m_pMeshInfo;
	LPD3DXBUFFER		m_pD3DXMtrlBuffer;

public:
	HRESULT LoadResource(const LPTSTR szMeshName);
	void Render();
	void Destroy();

public:
	HRESULT LoadMesh(const LPTSTR szMeshName);
	HRESULT LoadTexture();

public:
	CStaticMesh(void);
	~CStaticMesh(void);
};

