#include "ThirdCam.h"
#include "KeyManager.h"
#include "Entity.h"
#include "Debug.h"

CThirdCam::CThirdCam(void) 
	: CCamera()
	, m_pLookObject(NULL)
{
	memset(&m_vDist, 0, sizeof(D3DXVECTOR3) );
	memset(&m_vInitRight, 0, sizeof(D3DXVECTOR3) );
	memset(&m_vInitUp, 0, sizeof(D3DXVECTOR3) );
}


CThirdCam::~CThirdCam(void)
{

}

void CThirdCam::Init()
{
	CCamera::Init();

	//정면 보기
//	m_vDist = D3DXVECTOR3(0.f, 0.f, 10.f);

	//탑뷰
	m_vDist = D3DXVECTOR3(0.f, 90.f, 0.f);
	m_tCam.vPos = D3DXVECTOR3( 0.f, 30.f, -10.f );
}
void CThirdCam::Update()
{
	if( m_pLookObject == NULL)
	{
		Move();
		Rotation();
	}
	else
	{  
		//따라갑니다
		D3DXVECTOR3 vLookObjectPos = m_pLookObject->GetPos();
		m_tCam.vPos = vLookObjectPos + m_vDist;

		//y축 회전 값만 뽑아옴
		//이 값으로 카메라의 축들을 회전시킨다
		float fAngle = m_pLookObject->GetRotationAngle(AT_Y);
		D3DXMATRIX matRot;
		D3DXMatrixRotationY(&matRot, fAngle);

		//카메라와 오브젝트 거리 값에 회전값을 곱한 벡터
		D3DXVECTOR3 vDist;

		D3DXVec3TransformCoord(&vDist, &m_vDist, &matRot);

		//카메라 위치 구하기 (거리 * 회전 벡터 + 오브젝트 위치 벡터)
		m_tCam.vPos = vDist + vLookObjectPos;

		//룩 벡터는 오브젝트 위치와 카메라 위치의 차벡터를 정규화한 값
		//즉, 카메라에서 오브젝트를 바라보는 값
		D3DXVECTOR3 vMinus = -vDist;
		D3DXVec3Normalize(&m_tCam.vLook, &vMinus);

		//업 벡터는 처음 오브젝트를 보던 업 벡터에서 누적 회전값을 곱한 값
		//Init값이 아니라 m_tCam.vUp을 하면 계속 미친듯이 돎. 라이트 벡터도 마찬가지...
		D3DXVec3TransformCoord(&m_tCam.vUp, &m_vInitUp, &matRot);
		D3DXVec3Normalize(&m_tCam.vUp, &m_tCam.vUp);

		//라이트 벡터는 처음 오브젝트를 보던 라이트 벡터에서 누적 회전값을 곱한 값
		D3DXVec3TransformCoord(&m_tCam.vRight, &m_vInitRight, &matRot);
		D3DXVec3Normalize(&m_tCam.vRight, &m_tCam.vRight);

	}

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
	//Right 와 Look을 외적해서UP벡터 재 정
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

	m_tCam.vPos = m_vDist + m_pLookObject->GetPos();

	m_tCam.vLook = m_pLookObject->GetPos() - m_tCam.vPos;
	D3DXVec3Normalize(&m_tCam.vLook, &m_tCam.vLook);
	
	D3DXVec3Cross(&m_tCam.vUp, &m_tCam.vLook, &m_tCam.vRight);
	D3DXVec3Normalize(&m_tCam.vUp, &m_tCam.vUp);

	D3DXVec3Cross(&m_tCam.vRight, &m_tCam.vUp, &m_tCam.vLook);
	D3DXVec3Normalize(&m_tCam.vRight, &m_tCam.vRight);

	//이 값을 반대로 해야 호랑이가 제대로 보이는데
	//이건 호랑이 로컬축 문제인가 아니면 카메라 축 문제인가;;
	m_vInitRight = -m_tCam.vRight;
	m_vInitUp = -m_tCam.vUp;
}