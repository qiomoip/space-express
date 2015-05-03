#include "ThirdCam.h"
#include "KeyManager.h"
#include "Entity.h"
#include "Debug.h"

CThirdCam::CThirdCam(void) 
	: CCamera()
	, m_pLookObject(NULL)
{
	memset(&m_vDist, 0, sizeof(D3DXVECTOR3) );
}


CThirdCam::~CThirdCam(void)
{

}

void CThirdCam::Init()
{
	CCamera::Init();
	m_vDist = D3DXVECTOR3(0.f, 0.f, -10.f);
	m_tCam.vPos = D3DXVECTOR3( 0.f, 30.f, -10.f );
}
void CThirdCam::Update()
{
	if( m_pLookObject == NULL)
	{
		Move();
		Rotation();
	}
	//else
	//{ 

	//	D3DXVECTOR3 vDist;
	//	memset(&vDist, 0, sizeof(D3DXVECTOR3));
	//	D3DXVec3TransformCoord(&vDist, &m_vDist, &m_pLookObject->GetMatWorld());
	//	m_tCam.vPos = vDist;

	//	D3DXVec3Normalize(&vDist, &vDist);

	//	D3DXVECTOR3 vRight(1.f, 0.f, 0.f);
	//	D3DXVECTOR3 vUp(0.f, 1.f, 0.f);

	//	//¾å
	//	//D3DXMATRIX matRot;
	//	//
	//	//D3DXMatrixRotationAxis(&matRot, &/*m_tCam.vUp*/vRight, m_pLookObject->m_fAngle[AT_X]);

	//	//memcpy(&matRot._41, &m_pLookObject->m_vPos, sizeof(D3DXVECTOR3));

	//	//m_tCam.vLook = m_pLookObject->GetPos() - m_tCam.vPos;

	//	//D3DXVec3Normalize(&m_tCam.vLook, &m_tCam.vLook);

	//	//D3DXVec3Cross(&m_tCam.vRight, &vUp, &m_tCam.vLook);
	//	//D3DXVec3Cross(&m_tCam.vUp, &m_tCam.vLook, &m_tCam.vRight);

	//	//D3DXVec3Normalize(&m_tCam.vRight, &m_tCam.vRight);
	//	//D3DXVec3Normalize(&m_tCam.vUp, &m_tCam.vUp);
	//	const float fAngle = m_pLookObject->GetRotationAngle(AT_Y);
	//	
	//	//¾å



	//	m_tCam.vLook = m_pLookObject->GetPos() - m_tCam.vPos;
	//	D3DXVec3Normalize(&m_tCam.vLook, &m_tCam.vLook);
	//	D3DXVec3TransformNormal(&m_tCam.vRight, &vRight, &m_pLookObject->GetMatWorld());
	//	D3DXVec3TransformNormal(&m_tCam.vUp, &vUp, &m_pLookObject->GetMatWorld());
	//	D3DXVec3Normalize(&m_tCam.vRight, &m_tCam.vRight);
	//	D3DXVec3Normalize(&m_tCam.vUp, &m_tCam.vUp);

	//}

	CCamera::Update();
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
/*	memset(m_tCam.iDir, 0, sizeof(int) * AT_MAX);
	memset(m_tCam.iAngle, 0, sizeof(int) * AT_MAX);
	const KEYINFO* pInfo = _SINGLE(CKeyManager)->GetKey("KEY_UP");
	if(!pInfo)
		return;
	if(pInfo->bPush || pInfo->bDown)
	{
		m_tCam.iDir[AT_Z] = 1;
	}

	pInfo = _SINGLE(CKeyManager)->GetKey("KEY_DOWN");
	if(pInfo->bPush || pInfo->bDown)
	{
		m_tCam.iDir[AT_Z] = -1;
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
	}*/
}

//Y
void CThirdCam::Yaw()
{
	D3DXMATRIX matRot;
	D3DXVECTOR3 axis = D3DXVECTOR3(0, 1, 0);
	D3DXQUATERNION yAngle;
	D3DXQuaternionIdentity( &yAngle);
	D3DXMatrixIdentity( & matRot);

	D3DXQuaternionRotationAxis( &yAngle,  &axis, m_tCam.iAngle[AT_Y] * m_tCam.fSmoothRotate);  
	D3DXMatrixRotationQuaternion( &matRot, &yAngle);
	//D3DXMatrixRotationAxis(&matRot, &axis, D3DX_PI * m_tCam.fSmooth  * m_tCam.iAngle[AT_Y]);

	D3DXVec3TransformCoord(&m_tCam.vUp, &m_tCam.vUp, &matRot);
	D3DXVec3TransformCoord(&m_tCam.vRight, &m_tCam.vRight, &matRot);
	D3DXVec3TransformCoord(&m_tCam.vLook, &m_tCam.vLook, &matRot);
	//Right ¿Í LookÀ» ¿ÜÀûÇØ¼­UPº¤ÅÍ Àç Á¤
}
//X
void CThirdCam::Pitch()
{
	D3DXMATRIX matRot;
	D3DXQUATERNION xAngle;
	D3DXQuaternionIdentity( &xAngle);
	D3DXMatrixIdentity( & matRot);

	D3DXQuaternionRotationAxis( &xAngle,  &m_tCam.vRight, m_tCam.iAngle[AT_X] * m_tCam.fSmoothRotate);  
	D3DXMatrixRotationQuaternion( &matRot, &xAngle);

	//D3DXMatrixRotationAxis(&matRot, &m_tCam.vRight, D3DX_PI * m_tCam.fSmooth  * m_tCam.iAngle[AT_X]);

	D3DXVec3TransformCoord(&m_tCam.vRight, &m_tCam.vRight, &matRot);
	D3DXVec3TransformCoord(&m_tCam.vUp, &m_tCam.vUp, &matRot);
	D3DXVec3TransformCoord(&m_tCam.vLook, &m_tCam.vLook, &matRot);
}
//Z
void CThirdCam::Roll()
{
	D3DXMATRIX matRot;
	D3DXMatrixRotationAxis(&matRot, &m_tCam.vLook, D3DX_PI * m_tCam.fSmoothRotate  * m_tCam.iAngle[AT_Z]);

	D3DXVec3TransformCoord(&m_tCam.vRight, &m_tCam.vRight, &matRot);
	D3DXVec3TransformCoord(&m_tCam.vUp, &m_tCam.vUp, &matRot);
}
void CThirdCam::Move()
{
	D3DXVECTOR3 vDir;

	if(m_tCam.iDir[AT_X])
	{
		/*D3DXVec3Cross(&vDir, &m_tCam.vUp, &m_tCam.vLook);
		D3DXVec3Normalize(&vDir, &vDir);
		*/
		m_tCam.vPos += m_tCam.vRight * m_tCam.fSmoothMove * (float)m_tCam.iDir[AT_X];
	}
	if(m_tCam.iDir[AT_Y])
	{
		//D3DXVec3Cross(&vDir, &m_tCam.vLook, &m_tCam.vRight);
		//D3DXVec3Normalize(&vDir, &vDir);

		//m_tCam.vPos += vDir * 0.05f * (float)m_tCam.iDir[AT_Y];
		m_tCam.vPos += /*D3DXVECTOR3(0.f, 0.2f, 0.f)*/m_tCam.vUp * m_tCam.fSmoothMove * (float)m_tCam.iDir[AT_Y];
	}

	if(m_tCam.iDir[AT_Z])
	{
		/*D3DXVec3Cross(&vDir, &m_tCam.vRight, &m_tCam.vUp);
		D3DXVec3Normalize(&vDir, &vDir);
		*/
		m_tCam.vPos += m_tCam.vLook * m_tCam.fSmoothMove * (float)m_tCam.iDir[AT_Z];
	}
	
	
	//m_tCam.vPos += m_tCam.vLook * 0.01f * m_tCam.iDir;
}

void CThirdCam::SetLookObject(CEntity* pEntity)
{
	m_pLookObject = pEntity;

	/*m_tCam.vLook = m_pLookObject->GetPos() - m_tCam.vPos;
	D3DXVec3Normalize(&m_tCam.vLook, &m_tCam.vLook);
	D3DXVec3TransformNormal(&m_tCam.vRight, &m_tCam.vRight, &m_pLookObject->GetMatWorld());
	D3DXVec3TransformNormal(&m_tCam.vUp, &m_tCam.vUp, &m_pLookObject->GetMatWorld());
	D3DXVec3Normalize(&m_tCam.vRight, &m_tCam.vRight);
	D3DXVec3Normalize(&m_tCam.vUp, &m_tCam.vUp);*/
}