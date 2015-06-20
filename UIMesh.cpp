#include "UIMesh.h"
#include "Device.h"
#include "Shader.h"
#include "Texture.h"
#include "Debug.h"
#include "ResourceManager.h"

CUIMesh::CUIMesh(void)
	: m_pVB(NULL)
	, m_pIB(NULL)
	, m_pTexture(NULL)
{
}


CUIMesh::~CUIMesh(void)
{
	Destroy();
}

HRESULT CUIMesh::LoadResource(const LPTSTR szMeshName)
{
	m_ColType = MT_UI;

	if(FAILED(CreateVertexBuffer()))
	{
		return E_FAIL;
	}

	if(FAILED(LoadTexture(szMeshName)))
	{
		return E_FAIL;
	}

	return S_OK;
}

void CUIMesh::Render(CShader* pShader, const UINT& uPass)
{
	_SINGLE(CDevice)->GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);

	m_pTexture->SetTexture();

	_SINGLE(CDevice)->GetDevice()->SetStreamSource(0, m_pVB, 0, sizeof(VTXTEXTURE));
	_SINGLE(CDevice)->GetDevice()->SetFVF(VTXTEXTUREFVF);
	//_SINGLE(CDevice)->GetDevice()->SetFVF(VTXCOLORFVF);
	_SINGLE(CDevice)->GetDevice()->SetIndices(m_pIB);

	pShader->BeginPass(uPass);

	_SINGLE(CDevice)->GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4,
		0, 2);

	pShader->EndPass();


#ifdef _DEBUG
	_SINGLE(CDebug)->AddFaceCount( 2 );
#endif
}

void CUIMesh::Destroy()
{
	Safe_Release(m_pVB);
	Safe_Release(m_pIB);
//	Safe_Delete(m_pTexture);
}

HRESULT CUIMesh::CreateVertexBuffer()
{
	/*
	0	1
	2	3
	
	*/
	if(_SINGLE(CDevice)->GetDevice()->CreateVertexBuffer(
		4 * sizeof(VTXTEXTURE), D3DUSAGE_WRITEONLY, VTXTEXTUREFVF, D3DPOOL_MANAGED, &m_pVB, NULL))
	{
		return E_FAIL;
	}
	/*if(_SINGLE(CDevice)->GetDevice()->CreateVertexBuffer(
		4 * sizeof(VERTEXCOLOR), D3DUSAGE_WRITEONLY, VTXTEXTUREFVF, D3DPOOL_MANAGED, &m_pVB, NULL))
	{
		return E_FAIL;
	}*/

	if(FAILED(_SINGLE(CDevice)->GetDevice()->CreateIndexBuffer(sizeof(INDEX) * 2,
		0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIB, NULL)))
		return E_FAIL;

	VTXTEXTURE*	pV	= NULL;
	

	m_pVB->Lock(0, 0, (void**)&pV, 0);

	pV->vPos	= D3DXVECTOR3(0.f, 0.f, 1.f);
	pV->vTex	= D3DXVECTOR2(0.f, 0.f);
	//pV->dwColor = D3DCOLOR_XRGB(0, 0, 0);
	++pV;

	pV->vPos	= D3DXVECTOR3(1.f, 0.f, 1.f);
	pV->vTex	= D3DXVECTOR2(1.f, 0.f);
	//pV->dwColor = D3DCOLOR_XRGB(100, 0, 0);
	++pV;

	pV->vPos	= D3DXVECTOR3(0.f, 1.f, 1.f);
	pV->vTex	= D3DXVECTOR2(0.f, 1.f);
	//pV->dwColor = D3DCOLOR_XRGB(0, 100, 0);
	++pV;

	pV->vPos	= D3DXVECTOR3(1.f, 1.f, 1.f);
	pV->vTex	= D3DXVECTOR2(1.f, 1.f);
	//pV->dwColor = D3DCOLOR_XRGB(0, 0, 100);

	m_pVB->Unlock();

	INDEX*	pI	= NULL;

	m_pIB->Lock(0, 0, (void**)&pI, 0);

	*pI++	= INDEX(0, 1, 3);
	*pI		= INDEX(0, 3, 2);

	m_pIB->Unlock();

	return S_OK;
}

float CUIMesh::GetSize()
{
	return 1.f;
}

bool CUIMesh::GetCollisionPos(RAY& tRay)
{
	////폴리곤과의 픽킹...
	//VTXTEXTURE* pV = NULL;
	//INDEX* pI = NULL;

	//m_pVB->Lock(0, 0, (void**)&pV, 0);

	//m_pIB->Lock(0, 0, (void**)&pI, 0);

	//WORD wIndex = 0;

	//float u = 0.f;
	//	float v = 0.f;
	//	float fDist = 0.f;

	//while(wIndex < 2)
	//{
	//	D3DXVECTOR3 v0 = pV[pI[wIndex]._0].vPos;
	//	D3DXVECTOR3 v1 = pV[pI[wIndex]._1].vPos;
	//	D3DXVECTOR3 v2 = pV[pI[wIndex]._2].vPos;
	//	if(D3DXIntersectTri(&v0,
	//			&v1,
	//			&v2,
	//			&tRay.vOrigin,
	//			&tRay.vDir,
	//			&u,
	//			&v,
	//			&fDist))
	//		{
	//			tRay.vIntersectPos = v0 + (v1 * u - v0 * u) + (v2 * v - v0 * v);

	//			m_pVB->Unlock();

	//			m_pIB->Unlock();

	//			return true;
	//		}

	//	++wIndex;
	//}
	//

	//m_pVB->Unlock();

	//m_pIB->Unlock();
	//충돌될 경우 true 리턴하고 해당 값을 tRay의 인터섹트포지션에 넣어줌...
	return false;
}

HRESULT CUIMesh::LoadTexture(const LPTSTR _meshName )
{
	m_pTexture = _SINGLE(CResourceManager)->LoadTexture("Button", L"alice.png");

	if(!m_pTexture)
		return E_FAIL;
	return S_OK;
}