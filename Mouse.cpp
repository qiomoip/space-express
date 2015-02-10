#include "Mouse.h"
#include "CameraManager.h"
#include "Device.h"
#include "ObjectManager.h"
#include "Entity.h"
#include "TerrainMesh.h"

CMouse* CMouse::m_pInstance = 0;

CMouse::CMouse(void)
{
	memset(&m_pt, 0, sizeof(POINT));
	memset(&m_tRay, 0, sizeof(RAY));
}


CMouse::~CMouse(void)
{
}

void CMouse::CaculateMousePos()
{
	GetCursorPos(&m_pt);
	ScreenToClient(m_hWnd, &m_pt);
}

void CMouse::CaculateRay()
{
	float fX = 0.f;
	float fY = 0.f;

	D3DVIEWPORT9 vp;
	_SINGLE(CDevice)->GetDevice()->GetViewport(&vp);

	D3DXMATRIX matProj;
	_SINGLE(CDevice)->GetDevice()->GetTransform(D3DTS_PROJECTION, &matProj);

	fX = (((2.f * m_pt.x) / vp.Width) - 1.f) / matProj(0, 0);
	fY = (((-2.f * m_pt.y) / vp.Height) + 1.f) / matProj(1, 1);

	m_tRay.vOrigin = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_tRay.vDir = D3DXVECTOR3(fX, fY, 1.f);

	D3DXVec3Normalize(&m_tRay.vDir, &m_tRay.vDir);

}

RAY CMouse::TransformRay(const D3DXMATRIX* pMat)
{
	RAY tRay;
	memset(&tRay, 0, sizeof(RAY));

	D3DXMATRIX matInv;

	D3DXMatrixInverse(&matInv, NULL, pMat);

	D3DXVec3TransformCoord(&tRay.vOrigin, &m_tRay.vOrigin, &matInv);
	D3DXVec3TransformNormal(&tRay.vDir, &m_tRay.vDir, &matInv);

	D3DXVec3Normalize(&tRay.vDir, &tRay.vDir);

	return tRay;
}

bool CMouse::IntersectRayToSphere(RAY* pRay, const D3DXVECTOR3& vPos, const float fRadius)
{
	D3DXVECTOR3 vDir = pRay->vOrigin - vPos;

	float b = 2.f * D3DXVec3Dot(&pRay->vDir, &vDir);
	float c = D3DXVec3Dot(&vDir, &vDir) - (fRadius * fRadius);

	float d = (b * b) - (4.f * c);

	if(d < 0.f)
		return false;

	d = sqrtf(d);

	float s0 = (-b + d) * 0.5f;
	float s1 = (-b - d) * 0.5f;

	if(s0 >= 0.f || s1 >= 0.f)
	{
		if(s0 > s1)
		{
			if(s1 >= 0.f)
			{
				pRay->vIntersectPos = pRay->vOrigin + pRay->vDir * s1;
			}
		}

		else
		{
			if(s0 >= 0.f)
			{
				pRay->vIntersectPos	=
					pRay->vOrigin + pRay->vDir * s0;
			}
		}

		return true;
	}

	return false;
}


const RAY& CMouse::GetRay() const
{
	return m_tRay;
}

void CMouse::SetHwnd(const HWND& hWnd)
{
	m_hWnd = hWnd;
}

float CMouse::GetHeight()
{
	float fHeight = 0.f;

	//오브젝트 매니저에서 메인 터레인을 가져온다
	//레이와 터레인 오브젝트의 충돌 지점 계산
	CEntity* pEntity = _SINGLE(CObjectManager)->FindObject("MainTerrain");
	if(!pEntity)
	{
		Safe_Delete(pEntity);
		return 0.f;
	}

	LPDIRECT3DVERTEXBUFFER9 pVB = ((CTerrainMesh*)pEntity->GetMesh())->GetVtxInfo();


	//x, z 좌표 찾아서 셀 찾고
	//셀과 충돌하는가 검사
	//셀의 삼각형 두 개로 나눠서 
	//IntersectTri로 체크한다

	

	return fHeight;
}