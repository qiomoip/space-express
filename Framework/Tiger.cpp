#include "Tiger.h"
#include "KeyManager.h"
#include "CameraManager.h"
#include "Camera.h"
#include "Debug.h"
CTiger::CTiger(void)
{
}


CTiger::~CTiger(void)
{
}


void CTiger::Initialize()
{
	CEntity::Initialize();

	m_vLocalAxis[AT_X] = D3DXVECTOR3(1.f, 0.f, 0.f);
	m_vLocalAxis[AT_Y] = D3DXVECTOR3(0.f, 1.f, 0.f);
	m_vLocalAxis[AT_Z] = D3DXVECTOR3(0.f, 0.f, -1.f);
	
}

void CTiger::Update()
{
	CEntity::Update();
	//_SINGLE(CDebug)->AddLog(6,_T("vPos : %s"), m_vPos );
}

void CTiger::Input()
{

	const KEYINFO* pInfo = _SINGLE(CKeyManager)->GetKey(KEYNAME_RIGHT);
	//중복키를 처리하기위한 벡터
	D3DXVECTOR3 vInput = D3DXVECTOR3(0, 0, 0);
	if(!pInfo)
		assert(false);
	if(pInfo->bPush || pInfo->bDown)
	{
		//vInput += m_vWorldAxis[AT_X] * (-m_fMoveSpeed);
		
		//카메라의 right 벡터, 플레이어의 룩 벡터 내적
		//그 값이 0인 경우 두 벡터는 수직
		//따라서 회전시킨다
		/*const CAMERA tCam = _SINGLE(CCameraManager)->GetCurCam()->GetCameraInfo();
		float fDot = D3DXVec3Dot(&tCam.vRight, &m_vWorldAxis[AT_Z]);
		if(fDot < 1.f)
		{
			m_fAngle[AT_Y] += D3DX_PI * 0.5f;
		}
		else*/
		{
			vInput += m_vWorldAxis[AT_X] * (-m_fMoveSpeed);
		}

		m_bTransformUpdate = true;
	}

	pInfo = _SINGLE(CKeyManager)->GetKey(KEYNAME_LEFT);
	if(!pInfo)
		assert(false);
	if(pInfo->bPush || pInfo->bDown)
	{
		vInput +=  m_vWorldAxis[AT_X] * m_fMoveSpeed;
		
		m_bTransformUpdate = true;
	}

	pInfo = _SINGLE(CKeyManager)->GetKey(KEYNAME_FRONT);
	if(!pInfo)
		assert(false);
	if(pInfo->bPush || pInfo->bDown)
	{
		vInput += m_vWorldAxis[AT_Z] * m_fMoveSpeed;
		m_bTransformUpdate = true;
	}

	pInfo = _SINGLE(CKeyManager)->GetKey(KEYNAME_BACK);
	if(!pInfo)
		assert(false);
	if(pInfo->bPush || pInfo->bDown)
	{
		vInput += m_vWorldAxis[AT_Z] * (-m_fMoveSpeed);
		m_bTransformUpdate = true;
	}
	//중복키를 합쳐서 정규화한 후 적용
	D3DXVec3Normalize( &m_vMove, &vInput);
	m_vMove *= m_fMoveSpeed;

/* //회전 제한
	pInfo = _SINGLE(CKeyManager)->GetKey(KEYNAME_TURN_RIGHT);
	if(pInfo->bPush || pInfo->bDown)
	{
		m_fAngle[AT_Y] += 0.01f;
		m_bTransformUpdate = true;
	}

	pInfo = _SINGLE(CKeyManager)->GetKey(KEYNAME_TURN_LEFT);
	if(pInfo->bPush || pInfo->bDown)
	{
		m_fAngle[AT_Y] -= 0.01f;
		m_bTransformUpdate = true;
	}

	pInfo = _SINGLE(CKeyManager)->GetKey(KEYNAME_TURN_UP);
	if(pInfo->bPush || pInfo->bDown)
	{
		m_fAngle[AT_X] += 0.01f;
		m_bTransformUpdate = true;
	}

	pInfo = _SINGLE(CKeyManager)->GetKey(KEYNAME_TURN_DOWN);
	if(pInfo->bPush || pInfo->bDown)
	{
		m_fAngle[AT_X] -= 0.01f;
		m_bTransformUpdate = true;
	}*/
}