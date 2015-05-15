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
	//�ڽ��� �밢�� ����
	float GetSize() ;
	//�ڽ��� ���� �Ӹ��ִ� ����
	BOXSIZE	GetMinMax();
	//�޽� Ÿ�� 
	 const eMESH_TYPE GetType() const ;

	 const LPD3DXMESH GetMesh()const ;
public:
	CBoxMesh(void);
	~CBoxMesh(void);
};

 