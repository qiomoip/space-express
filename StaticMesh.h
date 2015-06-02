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
	//�޽��� ����� �޽� ����(sphere)�� ����
	float	GetSize();
	const LPD3DXMESH GetMesh() const ;

	 const eMESH_TYPE GetType() const ;

public:
	CStaticMesh(void);
	~CStaticMesh(void);
};

