#include "Mouse.h"
#include "CameraManager.h"
#include "Camera.h"
#include "Device.h"

CMouse* CMouse::m_pInstance = 0;

CMouse::CMouse(void)
	: m_hWnd(NULL)
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

	////이렇게 하면 안 됨 (뭔지 모르겠지만 레이가 계속 뷰포트의 중앙에 갖다박음...)
	//_SINGLE(CCameraManager)->GetCurCam()->GetMatProj();

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

	//D3DXVec3Normalize(&vDir, &vDir);

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