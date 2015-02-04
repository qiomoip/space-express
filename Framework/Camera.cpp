#include "Camera.h"
#include "KeyManager.h"
#include "Device.h"

CCamera::CCamera(void)
{
}


CCamera::~CCamera(void)
{
}

void CCamera::Init()
{
	D3DXMatrixIdentity( &m_tCam.matView);
	D3DXMatrixIdentity( &m_tCam.matProj);

	m_tCam.vPos = D3DXVECTOR3( -3.f, 10.f, -10.f );
	m_tCam.vLook= D3DXVECTOR3( 0.0f, 0.0f, 1.0f );
	m_tCam.vUp = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
	m_tCam.vRight = D3DXVECTOR3(1.f, 0.f, 0.f);
	memset(m_tCam.iDir, 0, sizeof(int) * AT_MAX);
	memset(m_tCam.iAngle, 0, sizeof(int) * AT_MAX);
	D3DXQuaternionIdentity( &m_tCam.qAngle );
	
	m_tCam.fSmoothMove = 0.03f;
	m_tCam.fSmoothRotate = 0.003f;

	D3DXMatrixLookAtLH( &m_tCam.matView, &m_tCam.vPos, &m_tCam.vLook, &m_tCam.vUp );
	D3DXMatrixRotationAxis(&m_tCam.matView, &m_tCam.vRight, D3DX_PI * 0.5f);
	D3DXMatrixPerspectiveFovLH( &m_tCam.matProj, D3DX_PI / 4, 1.0f, 1.0f, 1000.0f );
}

void CCamera::Update()
{
	SetViewMatrix();
}

void CCamera::Input()
{
}

D3DXMATRIX* CCamera::GetMatView() 
{
	return &m_tCam.matView;
}

D3DXMATRIX* CCamera::GetMatProj() 
{
	return &m_tCam.matProj;
}

CAMERA CCamera::GetCameraInfo()
{
	return m_tCam;
}

void CCamera::SetTransform()
{
	_SINGLE(CDevice)->GetDevice()->SetTransform( D3DTS_VIEW, 
		&m_tCam.matView);
	_SINGLE(CDevice)->GetDevice()->SetTransform( D3DTS_PROJECTION, 
		&m_tCam.matProj );
}

void CCamera::SetViewMatrix()
{
	D3DXVec3Cross(&m_tCam.vRight, &m_tCam.vUp, &m_tCam.vLook);
	D3DXVec3Normalize(&m_tCam.vLook, &m_tCam.vLook);
	D3DXVec3Cross(&m_tCam.vUp, &m_tCam.vLook, &m_tCam.vRight);
	D3DXVec3Normalize(&m_tCam.vUp, &m_tCam.vUp);
	D3DXVec3Normalize(&m_tCam.vRight, &m_tCam.vRight);

	/*D3DXMatrixLookAtLH( &m_tCam.matView, &m_tCam.vPos, &m_tCam.vLook, &m_tCam.vUp );
	D3DXMatrixPerspectiveFovLH( &m_tCam.matProj, D3DX_PI / 4, 1.0f, 1.0f, 1000.0f );
	*/
	float fX = -D3DXVec3Dot(&m_tCam.vRight, &m_tCam.vPos);
	float fY = -D3DXVec3Dot(&m_tCam.vUp, &m_tCam.vPos);
	float fZ = -D3DXVec3Dot(&m_tCam.vLook, &m_tCam.vPos);

	m_tCam.matView._11 = m_tCam.vRight.x;
	m_tCam.matView._12 = m_tCam.vUp.x;
	m_tCam.matView._13 = m_tCam.vLook.x;
	m_tCam.matView._14 = 0.f;

	m_tCam.matView._21 = m_tCam.vRight.y;
	m_tCam.matView._22 = m_tCam.vUp.y;
	m_tCam.matView._23 = m_tCam.vLook.y;
	m_tCam.matView._24 = 0.f;

	m_tCam.matView._31 = m_tCam.vRight.z;
	m_tCam.matView._32 = m_tCam.vUp.z;
	m_tCam.matView._33 = m_tCam.vLook.z;
	m_tCam.matView._34 = 0.f;

	m_tCam.matView._41 = fX;
	m_tCam.matView._42 = fY;
	m_tCam.matView._43 = fZ;
	m_tCam.matView._44 = 1.f;
}

void CCamera::SetPos(const D3DXVECTOR3& vPos)
{
	m_tCam.vPos = vPos;
}
void CCamera::SetData(const D3DXVECTOR3& vUp, const D3DXVECTOR3& vLook, const D3DXVECTOR3& vRight)
{
	m_tCam.vLook = vLook;
	m_tCam.vRight = vRight;
	m_tCam.vUp = vUp;
}