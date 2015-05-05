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
	void Render(CShader* pShader, const UINT& uPass);
	void Destroy();

public:
	HRESULT LoadMesh(const LPTSTR szMeshName);
	HRESULT LoadTexture();
	//메쉬의 사이즈를 메쉬 정보(sphere)에 저장
	float	GetSize();
	LPD3DXMESH GetMesh();

public:
	CStaticMesh(void);
	~CStaticMesh(void);
};

