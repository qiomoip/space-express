#include "Tiger.h"
#include "KeyManager.h"
CTiger::CTiger(void)
{
}


CTiger::~CTiger(void)
{
}


void CTiger::Initialize()
{
	CEntity::Initialize();
}

void CTiger::Update()
{
	CEntity::Update();
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
		vInput += m_vWorldAxis[AT_X] * m_fMoveSpeed;
		m_bTransformUpdate = true;
	}

	pInfo = _SINGLE(CKeyManager)->GetKey(KEYNAME_LEFT);
	if(!pInfo)
		assert(false);
	if(pInfo->bPush || pInfo->bDown)
	{
		vInput +=  m_vWorldAxis[AT_X] * (-m_fMoveSpeed);
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
/*
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
		m_fAngle[AT_X] -= 0.01f;
		m_bTransformUpdate = true;
	}

	pInfo = _SINGLE(CKeyManager)->GetKey(KEYNAME_TURN_DOWN);
	if(pInfo->bPush || pInfo->bDown)
	{
		m_fAngle[AT_X] += 0.01f;
		m_bTransformUpdate = true;
	}*/
}