#pragma once
#include "mesh.h"
class CBoxMesh :
	public CMesh
{
private:
	LPD3DXMESH		m_pMesh;
	D3DMATERIAL9	m_tMaterial;

	BOXSIZE			m_Size;
	float			m_fRadius;
public:
	void Render(CShader* pShader, const UINT& uPass);
	void Destroy();

	HRESULT LoadResource(const LPTSTR szMeshName);

	void	SetSize();
	//박스의 대각선 길이
	float GetSize() ;
	//박스의 가장 머리있는 두점
	BOXSIZE	GetMinMax();
	//메쉬 타입 
	 const eMESH_TYPE GetType() const ;

	 const LPD3DXMESH GetMesh()const ;
public:
	CBoxMesh(void);
	~CBoxMesh(void);
};

 