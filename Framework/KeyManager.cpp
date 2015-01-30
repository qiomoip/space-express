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
	SetKeyData("KEY_ROT_X_RIGHT", 'D');
	SetKeyData("KEY_ROT_X_LEFT", 'A');
	SetKeyData("KEY_START", VK_SPACE);
	SetKeyData("KEY_UP", VK_UP);
	SetKeyData("KEY_DOWN", VK_DOWN);
	SetKeyData("KEY_RIGHT", VK_RIGHT);
	SetKeyData("KEY_LEFT", VK_LEFT);
	SetKeyData("KEY_SPACE", VK_SPACE);
	SetKeyData("KEY_ROT_Y_UP", 'W');
	SetKeyData("KEY_ROT_Y_DOWN", 'S');
	SetKeyData("KEY_Entity_RotY-", 'Z');
	SetKeyData("KEY_Entity_RotY+", 'X');
}
void CKeyManager::SetKeyState()
{
	map<string, KEYINFO*>::iterator iter = m_mapKey.begin();
	for(; iter != m_mapKey.end() ; ++iter)
	{
		CheckKey(iter);
	}
}

bool CKeyManager::SetKeyData(const string& eKeyName, const int& iKey)
{
	map<string, KEYINFO*>::iterator iter = m_mapKey.find(eKeyName);
	if(iter != m_mapKey.end())
	{
		return false;
	}
	KEYINFO* pKey = new KEYINFO;
	memset(pKey, 0, sizeof(KEYINFO));
	
	pKey->iKey = iKey;
	m_mapKey.insert(map<string, KEYINFO*>::value_type(eKeyName, pKey));
	return true;
}

const KEYINFO* CKeyManager::GetKey(const string& eKey) const
{
	map<string, KEYINFO*>::const_iterator iter = m_mapKey.find(eKey);

	if(iter == m_mapKey.end())
	{
		return NULL;
	}
	return iter->second;
}

void CKeyManager::CheckKey(map<string, KEYINFO*>::iterator iter)
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