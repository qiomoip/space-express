#include "ThirdCam.h"
#include "KeyManager.h"
#include "Entity.h"


#include "Debug.h"
//typedef struct _tagCamera
//{
//      D3DXMATRIX matView;
//      D3DXMATRIX matProj;
//      D3DXVECTOR3 vPos;
//      D3DXVECTOR3 vLook;
//      D3DXVECTOR3 vUp;
//      D3DXVECTOR3 vRight;
//}CAMERA;

CThirdCam::CThirdCam(void)
	: CCamera()
	, m_pLookObject(NULL)
{
}


CThirdCam::~CThirdCam(void)
{

}

void CThirdCam::Init()
{
	CCamera::Init();
}
void CThirdCam::Update()
{
	Move();
	Rotation();
	CCamera::Update();
		
	D3DXVECTOR3 vPos = m_tCam.vPos;
	D3DXVECTOR3 vLook = m_tCam.vLook;
	D3DXVECTOR3 vUp = m_tCam.vUp;
	D3DXVECTOR3 vRight = m_tCam.vRight;
	CTString* str = new CTString();
	_SINGLE(CDebug)->AddStaticLog( _S("카메라 정보 \nvPos :") + vPos + "\nvLookAt : %.2f, %.2f, %.2f \nUp : %.2f, %.2f, %.2f \nvRight : %.2f, %.2f, %.2f"), 
		vPos.x, vPos.y, vPos.z, vLook.x, vLook.y, vLook.z, vUp.x, vUp.y, vUp.z, vRight .x, vRight.y, vRight.z ) );
}

void CThirdCam::Rotation()
{
	if(m_tCam.iAngle[AT_X])
		Pitch();
	if(m_tCam.iAngle[AT_Y])
		Yaw();
	if(m_tCam.iAngle[AT_Z])
		Roll();
}
void CThirdCam::Input()
{
	memset(m_tCam.iDir, 0, sizeof(int) * AT_MAX);
	memset(m_tCam.iAngle, 0, sizeof(int) * AT_MAX);
	const KEYINFO* pInfo = _SINGLE(CKeyManager)->GetKey("KEY_UP");
	if(!pInfo)
		return;
	if(pInfo->bPush || pInfo->bDown)
	{
		m_tCam.iDir[AT_Y] = 1;
	}

	pInfo = _SINGLE(CKeyManager)->GetKey("KEY_DOWN");
	if(pInfo->bPush || pInfo->bDown)
	{
		m_tCam.iDir[AT_Y] = -1;
	}

	pInfo = _SINGLE(CKeyManager)->GetKey("KEY_ROT_X_RIGHT");
	if(pInfo->bPush || pInfo->bDown)
	{
		m_tCam.iAngle[AT_Y] = 1;
	}

	pInfo = _SINGLE(CKeyManager)->GetKey("KEY_ROT_X_LEFT");
	if(pInfo->bPush || pInfo->bDown)
	{
		m_tCam.iAngle[AT_Y] = -1;
	}

	pInfo = _SINGLE(CKeyManager)->GetKey("KEY_ROT_Y_UP");
	if(pInfo->bPush || pInfo->bDown)
	{
		m_tCam.iAngle[AT_X] = -1;
	}

	pInfo = _SINGLE(CKeyManager)->GetKey("KEY_ROT_Y_DOWN");
	if(pInfo->bPush || pInfo->bDown)
	{
		m_tCam.iAngle[AT_X] = 1;
	}

	pInfo = _SINGLE(CKeyManager)->GetKey("KEY_RIGHT");
	if(pInfo->bPush || pInfo->bDown)
	{
		m_tCam.iDir[AT_X] = 1;
	}

	pInfo = _SINGLE(CKeyManager)->GetKey("KEY_LEFT");
	if(pInfo->bPush || pInfo->bDown)
	{
		m_tCam.iDir[AT_X] = -1;
	}
}

void CThirdCam::Yaw()
{
	D3DXMATRIX matRot;
	D3DXMatrixRotationAxis(&matRot, &m_tCam.vUp, D3DX_PI * m_tCam.fSmooth  * m_tCam.iAngle[AT_Y]);

	D3DXVec3TransformCoord(&m_tCam.vRight, &m_tCam.vRight, &matRot);
	D3DXVec3TransformCoord(&m_tCam.vLook, &m_tCam.vLook, &matRot);
}
void CThirdCam::Pitch()
{
	D3DXMATRIX matRot;
	D3DXMatrixRotationAxis(&matRot, &m_tCam.vRight, D3DX_PI * m_tCam.fSmooth  * m_tCam.iAngle[AT_X]);

	D3DXVec3TransformCoord(&m_tCam.vUp, &m_tCam.vUp, &matRot);
	D3DXVec3TransformCoord(&m_tCam.vLook, &m_tCam.vLook, &matRot);
}
void CThirdCam::Roll()
{
	D3DXMATRIX matRot;
	D3DXMatrixRotationAxis(&matRot, &m_tCam.vLook, D3DX_PI * m_tCam.fSmooth  * m_tCam.iAngle[AT_Z]);

	D3DXVec3TransformCoord(&m_tCam.vRight, &m_tCam.vRight, &matRot);
	D3DXVec3TransformCoord(&m_tCam.vUp, &m_tCam.vUp, &matRot);
}
void CThirdCam::Move()
{
	D3DXVECTOR3 vDir;

	if(m_tCam.iDir[AT_X])
	{
		D3DXVec3Cross(&vDir, &m_tCam.vUp, &m_tCam.vLook);
		D3DXVec3Normalize(&vDir, &vDir);

		m_tCam.vPos += vDir * 0.05f * (float)m_tCam.iDir[AT_X];
	}
	if(m_tCam.iDir[AT_Y])
	{
		//D3DXVec3Cross(&vDir, &m_tCam.vLook, &m_tCam.vRight);
		//D3DXVec3Normalize(&vDir, &vDir);

		//m_tCam.vPos += vDir * 0.05f * (float)m_tCam.iDir[AT_Y];
		m_tCam.vPos += D3DXVECTOR3(0.f, 0.2f, 0.f) * m_tCam.iDir[AT_Y];
	}

	if(m_tCam.iDir[AT_Z])
	{
		D3DXVec3Cross(&vDir, &m_tCam.vRight, &m_tCam.vUp);
		D3DXVec3Normalize(&vDir, &vDir);

		m_tCam.vPos += vDir * 0.05f * (float)m_tCam.iDir[AT_Z];
	}
	
	
	//m_tCam.vPos += m_tCam.vLook * 0.01f * m_tCam.iDir;
}

void CThirdCam::SetLookObject(CEntity* pEntity)
{
	m_pLookObject = pEntity;
}