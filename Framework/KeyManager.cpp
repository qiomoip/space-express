#include "KeyManager.h"
#include "Debug.h"
#include "Mouse.h"

CKeyManager::CKeyManager(void)
{
}


CKeyManager::~CKeyManager(void)
{
	Destroy();
}

void CKeyManager::Initialize()
{
	SetKeyData(KEYNAME_TURN_RIGHT, 'D');
	SetKeyData(KEYNAME_TURN_LEFT, 'A');
	SetKeyData(KEYNAME_START, VK_RETURN);
	SetKeyData(KEYNAME_FRONT, VK_UP);
	SetKeyData(KEYNAME_BACK, VK_DOWN);
	SetKeyData(KEYNAME_RIGHT, VK_RIGHT);
	SetKeyData(KEYNAME_LEFT, VK_LEFT);
	SetKeyData(KEYNAME_HOME, VK_HOME);
	SetKeyData(KEYNAME_END, VK_END);
	SetKeyData(KEYNAME_INS, VK_INSERT);
	SetKeyData(KEYNAME_DEL, VK_DELETE);
	SetKeyData(KEYNAME_PGUP, VK_PRIOR);
	SetKeyData(KEYNAME_PGDN, VK_NEXT);
	SetKeyData(KEYNAME_SPACE, VK_SPACE);
	SetKeyData(KEYNAME_TURN_UP, 'W');
	SetKeyData(KEYNAME_TURN_DOWN, 'S');
	SetKeyData(KEYNAME_TURN_NCLOCKWISE, 'Z');
	SetKeyData(KEYNAME_TURN_CLOCKWISE, 'C');
	//SetKeyData(KEYNAME_TURN_CLOCKWISE, 'C');
	SetKeyData(KEYNAME_WIREFRAME_TRIGGER , VK_TAB);
	SetKeyData(KEY_NAME_L_BUTTON, VK_LBUTTON);
	SetKeyData(KEY_NAME_R_BUTTON, VK_RBUTTON);
}
void CKeyManager::SetKeyState()
{
	map<KEY, KEYINFO*>::iterator iter = m_mapKey.begin();
	for(; iter != m_mapKey.end() ; ++iter)
	{
		CheckKey(iter);
	}
#ifdef _DEBUG
	_SINGLE(CDebug)->AddStaticLog(LOG_KEY_INFO_0, _T("카메라 상하 회전 : W,S")  );
	_SINGLE(CDebug)->AddStaticLog(LOG_KEY_INFO_1, _T("카메라 좌우 회전 : A,D")  );
	_SINGLE(CDebug)->AddStaticLog(LOG_KEY_INFO_2, _T("카메라 전후 이동 : HOME, END")  );
	_SINGLE(CDebug)->AddStaticLog(LOG_KEY_INFO_3, _T("카메라 상하 이동 : INS, PAGE_UP")  );
	_SINGLE(CDebug)->AddStaticLog(LOG_KEY_INFO_4, _T("카메라 좌우 이동 : DEL, PAGE_DOWN")  );
	_SINGLE(CDebug)->AddStaticLog(LOG_KEY_INFO_5, _T("캐릭터 4방향 이동: 화살표")  );
#endif

	_SINGLE(CMouse)->CaculateMousePos();
	_SINGLE(CMouse)->CaculateRay();
}

bool CKeyManager::SetKeyData(const KEY eKeyName, const int& iKey)
{
	map<KEY, KEYINFO*>::iterator iter = m_mapKey.find(eKeyName);
	if(iter != m_mapKey.end())
	{
		return false;
	}
	KEYINFO* pKey = new KEYINFO;
	memset(pKey, 0, sizeof(KEYINFO));
	
	pKey->iKey = iKey;
	m_mapKey.insert(map<KEY, KEYINFO*>::value_type(eKeyName, pKey));
	return true;
}

const KEYINFO* CKeyManager::GetKey(const KEY eKey) const
{
	map<KEY, KEYINFO*>::const_iterator iter = m_mapKey.find(eKey);

	if(iter == m_mapKey.end())
	{
		return NULL;
	}
	return iter->second;
}

void CKeyManager::CheckKey(map<KEY, KEYINFO*>::iterator iter)
{
	if(GetAsyncKeyState(iter->second->iKey) & 0x8000)
	{
		iter->second->bUp = false;
		if(!iter->second->bPush)
		{
			if(!iter->second->bDown)
			{
				iter->second->bPush = true;
				iter->second->bDown = false;
			}
		}
		else
		{
			iter->second->bPush = false;
			iter->second->bDown = true;
		}
	}
	else
	{
		if(iter->second->bDown || iter->second->bPush)
		{
			iter->second->bUp = true;
		}
		else
		{
			iter->second->bUp = false;
		}
		iter->second->bPush = false;
		iter->second->bDown = false;
	}
}

void CKeyManager::Destroy()
{
	Safe_Delete_Array_Map(m_mapKey);
}