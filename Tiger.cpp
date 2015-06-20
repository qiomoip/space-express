#include "Tiger.h"
#include "KeyManager.h"
#include "CameraManager.h"
#include "Camera.h"
#include "Debug.h"
#include "TimeManager.h"

CTiger::CTiger(void)
	: m_Durability(0)
{
}


CTiger::~CTiger(void)
{
}


void CTiger::Initialize()
{
	CEntity::Initialize();

	m_Durability = 0;
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
	m_fMoveSpeed = 10.0 * _SINGLE(CTimeManager)->GetDeltaTime();
	const KEYINFO* pInfo = _SINGLE(CKeyManager)->GetKey(KEYNAME_RIGHT);
	//�ߺ�Ű�� ó���ϱ����� ����
	D3DXVECTOR3 vInput = D3DXVECTOR3(0, 0, 0);
	if(!pInfo)
		assert(false);
	if(pInfo->bPush || pInfo->bDown)
	{
		//vInput += m_vWorldAxis[AT_X] * (-m_fMoveSpeed);	
		//ī�޶��� right ����, �÷��̾��� �� ���� ����
		//�� ���� 0�� ��� �� ���ʹ� ����
		//���� ȸ����Ų��
		/*const CAMERA tCam = _SINGLE(CCameraManager)->GetCurCam()->GetCameraInfo();
		float fDot = D3DXVec3Dot(&tCam.vRight, &m_vWorldAxis[AT_Z]);
		if(fDot < 1.f)
		{
			m_fAngle[AT_Y] += D3DX_PI * 0.5f;
		}
		else*/
		{
			vInput -= m_vWorldAxis[AT_X] /** (-m_fMoveSpeed)*/;
		}

		m_bTransformUpdate = true;
	}

	pInfo = _SINGLE(CKeyManager)->GetKey(KEYNAME_LEFT);
	if(!pInfo)
		assert(false);
	if(pInfo->bPush || pInfo->bDown)
	{
		vInput +=  m_vWorldAxis[AT_X] /** m_fMoveSpeed*/;
		
		m_bTransformUpdate = true;
	}

	pInfo = _SINGLE(CKeyManager)->GetKey(KEYNAME_FRONT);
	if(!pInfo)
		assert(false);
	if(pInfo->bPush || pInfo->bDown)
	{
		vInput += m_vWorldAxis[AT_Z]/* * m_fMoveSpeed*/;
		m_bTransformUpdate = true;
	}

	pInfo = _SINGLE(CKeyManager)->GetKey(KEYNAME_BACK);
	if(!pInfo)
		assert(false);
	if(pInfo->bPush || pInfo->bDown)
	{
		vInput -= m_vWorldAxis[AT_Z] /** (-m_fMoveSpeed)*/;
		m_bTransformUpdate = true;
	}
	//�ߺ�Ű�� ���ļ� ����ȭ�� �� ����
	D3DXVec3Normalize( &m_vMove, &vInput);
	//m_vMove *= m_fMoveSpeed;

/* //ȸ�� ����
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

void CTiger::Attacked( int _durability)
{
	
	if( m_Durability + _durability > 100 )
		m_Durability = 100;
	else 
		m_Durability += _durability;
	_SINGLE(CDebug)->AddLog(6, _T("�ļյ� ����. ���� �ļյ� : %d"), m_Durability);
}