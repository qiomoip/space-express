#include "KeyManager.h"


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
	SetKeyData(KEYNAME_UP, VK_HOME);
	SetKeyData(KEYNAME_DOWN, VK_END);
	SetKeyData(KEYNAME_SPACE, VK_SPACE);
	SetKeyData(KEYNAME_TURN_UP, 'W');
	SetKeyData(KEYNAME_TURN_DOWN, 'S');
	SetKeyData(KEYNAME_TURN_NCLOCKWISE, 'Z');
	SetKeyData(KEYNAME_TURN_CLOCKWISE, 'C');
	//SetKeyData(KEYNAME_TURN_CLOCKWISE, 'C');
	SetKeyData(KEYNAME_WIREFRAME_TRIGGER , VK_TAB);
}
void CKeyManager::SetKeyState()
{
	map<KEY, KEYINFO*>::iterator iter = m_mapKey.begin();
	for(; iter != m_mapKey.end() ; ++iter)
	{
		CheckKey(iter);
	}
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