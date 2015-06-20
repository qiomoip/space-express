#include "Camera.h"
#include "KeyManager.h"
#include "Device.h"

CCamera::CCamera(void)
{
	memset(&m_tCam, 0, sizeof(CAMERA));
}


CCamera::~CCamera(void)
{
}

void CCamera::Init()
{
	D3DXMatrixIdentity( &m_tCam.matView[VIEW_PERSPECTIVE]);
	D3DXMatrixIdentity( &m_tCam.matProj[VIEW_PERSPECTIVE]);

	D3DXMatrixIdentity( &m_tCam.matView[VIEW_ORTHOGONAL]);
	D3DXMatrixIdentity( &m_tCam.matProj[VIEW_ORTHOGONAL]);

	m_tCam.vPos = D3DXVECTOR3( 0.f, 10.f, -10.f );
	m_tCam.vLook= D3DXVECTOR3( 0.0f, 0.0f, 1.0f );
	m_tCam.vUp = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
	m_tCam.vRight = D3DXVECTOR3(1.f, 0.f, 0.f);
	memset(m_tCam.iDir, 0, sizeof(int) * AT_MAX);
	memset(m_tCam.iAngle, 0, sizeof(int) * AT_MAX);
	D3DXQuaternionIdentity( &m_tCam.qAngle );
	
	m_tCam.fSmoothMove = 0.03f;
	m_tCam.fSmoothRotate = 0.003f;

		D3DXMatrixLookAtLH( &m_tCam.matView[VIEW_PERSPECTIVE], &m_tCam.vPos, &m_tCam.vLook, &m_tCam.vUp );
	D3DXMatrixRotationAxis(&m_tCam.matView[VIEW_PERSPECTIVE], &m_tCam.vRight, D3DX_PI * 0.5f);
	D3DXMatrixPerspectiveFovLH( &m_tCam.matProj[VIEW_PERSPECTIVE], /*D3DX_PI / 4*/D3DX_PI / 4.f , 1.0f, 1.0f, 1000.0f );

	//직교투영
	D3DXMatrixOrthoOffCenterLH(&m_tCam.matProj[VIEW_ORTHOGONAL], 
		0, SCREEN_WIDTH, SCREEN_HEIGHT, 0.f, 0.f, 1000.f); 
}

void CCamera::Update()
{
	SetViewMatrix();
}

void CCamera::Input()
{
}

const D3DXMATRIX* CCamera::GetMatView(const eVIEW_TYPE& eView) const
{
	return &m_tCam.matView[eView];
	
}

const D3DXMATRIX* CCamera::GetMatProj(const eVIEW_TYPE& eView) const 
{
	return &m_tCam.matProj[eView];
}

const D3DXMATRIX CCamera::GetMatViewProj(const eVIEW_TYPE& eView) const 
{
	return (m_tCam.matView[eView] * m_tCam.matProj[eView]);
}

const CAMERA CCamera::GetCameraInfo() const
{
	return m_tCam;
}

void CCamera::SetTransform(const eVIEW_TYPE& eView)
{
	_SINGLE(CDevice)->GetDevice()->SetTransform( D3DTS_VIEW, 
		&m_tCam.matView[eView]);
	_SINGLE(CDevice)->GetDevice()->SetTransform( D3DTS_PROJECTION, 
		&m_tCam.matProj[eView] );
}
void CCamera::SetViewMatrix()
{
	//D3DXVec3Cross(&m_tCam.vRight, &m_tCam.vUp, &m_tCam.vLook);
	D3DXVec3Normalize(&m_tCam.vLook, &m_tCam.vLook);
	//D3DXVec3Cross(&m_tCam.vUp, &m_tCam.vLook, &m_tCam.vRight);
	D3DXVec3Normalize(&m_tCam.vUp, &m_tCam.vUp);
	D3DXVec3Normalize(&m_tCam.vRight, &m_tCam.vRight);

	/*D3DXMatrixLookAtLH( &m_tCam.matView, &m_tCam.vPos, &m_tCam.vLook, &m_tCam.vUp );
	D3DXMatrixPerspectiveFovLH( &m_tCam.matProj, D3DX_PI / 4, 1.0f, 1.0f, 1000.0f );
	*/
	float fX = -D3DXVec3Dot(&m_tCam.vRight, &m_tCam.vPos);
	float fY = -D3DXVec3Dot(&m_tCam.vUp, &m_tCam.vPos);
	float fZ = -D3DXVec3Dot(&m_tCam.vLook, &m_tCam.vPos);

	m_tCam.matView[VIEW_PERSPECTIVE]._11 = m_tCam.vRight.x;
	m_tCam.matView[VIEW_PERSPECTIVE]._12 = m_tCam.vUp.x;
	m_tCam.matView[VIEW_PERSPECTIVE]._13 = m_tCam.vLook.x;
	m_tCam.matView[VIEW_PERSPECTIVE]._14 = 0.f;

	m_tCam.matView[VIEW_PERSPECTIVE]._21 = m_tCam.vRight.y;
	m_tCam.matView[VIEW_PERSPECTIVE]._22 = m_tCam.vUp.y;
	m_tCam.matView[VIEW_PERSPECTIVE]._23 = m_tCam.vLook.y;
	m_tCam.matView[VIEW_PERSPECTIVE]._24 = 0.f;

	m_tCam.matView[VIEW_PERSPECTIVE]._31 = m_tCam.vRight.z;
	m_tCam.matView[VIEW_PERSPECTIVE]._32 = m_tCam.vUp.z;
	m_tCam.matView[VIEW_PERSPECTIVE]._33 = m_tCam.vLook.z;
	m_tCam.matView[VIEW_PERSPECTIVE]._34 = 0.f;

	m_tCam.matView[VIEW_PERSPECTIVE]._41 = fX;
	m_tCam.matView[VIEW_PERSPECTIVE]._42 = fY;
	m_tCam.matView[VIEW_PERSPECTIVE]._43 = fZ;
	m_tCam.matView[VIEW_PERSPECTIVE]._44 = 1.f;
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

void CCamera::SetCamera(const CAMERA& _tCamera)
{
	m_tCam = _tCamera;
}