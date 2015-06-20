#include "BaseButton.h"
#include "KeyManager.h"
#include "Mouse.h"

CBaseButton::CBaseButton(void)
{
	memset(&m_tRC, 0, sizeof(RECT));
}


CBaseButton::~CBaseButton(void)
{
}

void CBaseButton::SetRectData(const RECT& tRect)
{
	m_tRC = tRect;
}

bool CBaseButton::IntersectPT( const POINT& pt )
{
	if(m_tRC.left <= pt.x && pt.x <= m_tRC.right &&
		m_tRC.top <= pt.y && pt.y <= m_tRC.bottom)
		return true;

	return false;
}

void CBaseButton::Input()
{
	const KEYINFO* pInfo = _SINGLE(CKeyManager)->GetKey(KEY_NAME_R_BUTTON);
	if(!pInfo)
		return;

	//´­·È´Âµ¥ ÀÚ±â¶û Ãæµ¹
	if(pInfo->bPush)
	{
		POINT pt = _SINGLE(CMouse)->GetMousePos();

		if(IntersectPT(pt))
		{
			Schedule();
		}
	}

	CEntity::Input();
}