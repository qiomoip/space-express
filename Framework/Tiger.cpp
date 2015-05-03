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
	if(!pInfo)
		return;
	if(pInfo->bPush || pInfo->bDown)
	{
		m_vPos += m_vWorldAxis[AT_X] * 0.01f;
	}

	pInfo = _SINGLE(CKeyManager)->GetKey(KEYNAME_LEFT);
	if(!pInfo)
		return;
	if(pInfo->bPush || pInfo->bDown)
	{
		m_vPos -= m_vWorldAxis[AT_X] * 0.01f;
	}

	pInfo = _SINGLE(CKeyManager)->GetKey(KEYNAME_FRONT);
	if(!pInfo)
		return;
	if(pInfo->bPush || pInfo->bDown)
	{
		m_vPos += m_vWorldAxis[AT_Z] * 0.01f;
	}

	pInfo = _SINGLE(CKeyManager)->GetKey(KEYNAME_BACK);
	if(!pInfo)
		return;
	if(pInfo->bPush || pInfo->bDown)
	{
		m_vPos -= m_vWorldAxis[AT_Z] * 0.01f;
	}

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
	}
}