#include "BoxMesh.h"
#include "Device.h"
#include "Shader.h"

CBoxMesh::CBoxMesh(void)
	: m_pMesh(NULL)
{
	memset(&m_tMaterial, 0, sizeof(D3DMATERIAL9));
	memset(&m_Size.vMax, 0, sizeof(D3DXVECTOR3));
	memset(&m_Size.vMin, 0, sizeof(D3DXVECTOR3));
	m_ColType = MT_BOX;
}


CBoxMesh::~CBoxMesh(void)
{
	Safe_Release(m_pMesh);
}

void CBoxMesh::Render(CShader* pShader, const UINT& uPass)
{
	pShader->SetValue("g_mtrlMesh", &m_tMaterial, sizeof(D3DMATERIAL9));
	pShader->BeginPass(uPass);
	m_pMesh->DrawSubset(0);
	pShader->EndPass();
}

void CBoxMesh::Destroy()
{
}

HRESULT CBoxMesh::LoadResource(const LPTSTR szMeshName)
{
	if(FAILED(D3DXCreateBox(_SINGLE(CDevice)->GetDevice(), 1.f, 1.f, 1.f, &m_pMesh,
		NULL)))
	{
		return E_FAIL;
	}

	
	m_tMaterial.Diffuse.a = 1.f;
	m_tMaterial.Diffuse.r = 1.f;
	m_tMaterial.Diffuse.g = 1.f;
	m_tMaterial.Diffuse.b = 1.f;
	m_tMaterial.Power = 0.2f;
	m_tMaterial.Specular = m_tMaterial.Diffuse;
	m_tMaterial.Ambient = m_tMaterial.Diffuse;
	SetSize();
	return S_OK;
}

void CBoxMesh::SetSize()
{
	D3DXVECTOR3 vPos = D3DXVECTOR3(10.f, 0.f, 10.f);
	//D3DXVECTOR3 vMax;
	//D3DXVECTOR3 vMin;
	//
	//memset(&vMax, 0, sizeof(D3DXVECTOR3));
	//memset(&vMin, 0, sizeof(D3DXVECTOR3));

	float fRadius = -1.f;
	if(m_pMesh )	
	{
		BYTE* ppVB = NULL;
		m_pMesh->LockVertexBuffer( 0, (VOID**) &ppVB);

		if(FAILED(D3DXComputeBoundingBox((D3DXVECTOR3*)ppVB, m_pMesh->GetNumVertices(),
			m_pMesh->GetNumBytesPerVertex(), &m_Size.vMin, &m_Size.vMax)))
		{
			m_fRadius = fRadius;
			return;
		}

		D3DXVECTOR3 vLen = m_Size.vMax - m_Size.vMin;
		fRadius = D3DXVec3Length(&vLen);
		fRadius *= 0.5f;
	}
	m_fRadius = fRadius;
}


float CBoxMesh::GetSize()
{
	return m_fRadius;
}

BOXSIZE CBoxMesh::GetMinMax()
{
	return m_Size;
}

 const eMESH_TYPE CBoxMesh::GetType() const 
{
	return m_ColType;
}

 const LPD3DXMESH CBoxMesh::GetMesh() const 
 {
	 return m_pMesh;
 }
