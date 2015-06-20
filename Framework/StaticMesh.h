#pragma once
#include "Mesh.h"

#define	INSTANCING_NUM		2000

class CStaticMesh
	: public CMesh
{
private:
	MESH_INFO*			m_pMeshInfo;
	
	LPD3DXBUFFER		m_pD3DXMtrlBuffer; //여기?

	LPD3DXMESH			m_pCloneMesh;

	LPDIRECT3DVERTEXDECLARATION9	m_pDeclGeometry;

	D3DXATTRIBUTERANGE*		m_pAttr;
	LPDIRECT3DVERTEXBUFFER9	m_pVB;
	LPDIRECT3DVERTEXBUFFER9	m_pInstancingVB;
	LPDIRECT3DINDEXBUFFER9	m_pIB;

	int						m_iAddInstanceData;

public:
	HRESULT LoadResource(const LPTSTR szMeshName);
	void Render(CShader* pShader, const UINT& uPass);
	void RenderInstance(CShader* pShader, const UINT& uPass);
	void Destroy();

public:
	HRESULT LoadMesh(const LPTSTR szMeshName);
	HRESULT LoadTexture();
	//메쉬의 사이즈를 메쉬 정보(sphere)에 저장
	float	GetSize();
	void	SetSize();
	const LPD3DXMESH GetMesh() const ;

	const eMESH_TYPE GetType() const ;

	void PushInstancingData(const D3DXMATRIX& matWorld);
	void ResetInstancingCount();

public:
	CStaticMesh(void);
	~CStaticMesh(void);
};

