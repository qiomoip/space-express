#pragma once
#include "mesh.h"
class CBoxMesh :
	public CMesh
{
private:
	LPD3DXMESH	m_pMesh;
	D3DMATERIAL9	m_tMaterial;

public:
	void Render(CShader* pShader, const UINT& uPass);
	void Destroy();

	HRESULT LoadResource(const LPTSTR szMeshName);

	float GetSize() ;

public:
	CBoxMesh(void);
	~CBoxMesh(void);
};

