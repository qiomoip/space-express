#include "KeyManager.h"


CKeyManager::CKeyManager(void)
{
}


CKeyManager::~CKeyManager(void)
{
}

void CKeyManager::SetKeyState()
{
	map<KEY_STATE, KEYINFO*>::iterator iter = m_mapKey.begin();
	for(int i = 0; i < m_mapKey.size(); ++i, ++iter)
	{
		CheckKey(iter);
	}
}

bool CKeyManager::SetKeyData(const KEY_STATE& eKeyName, const int& iKey)
{
	map<KEY_STATE, KEYINFO*>::iterator iter = m_mapKey.find(eKeyName);
	if(iter != m_mapKey.end())
	{
		return false;
	}
	KEYINFO* pKey = new KEYINFO;
	memset(pKey, 0, sizeof(KEYINFO));
	
	pKey->iKey = iKey;
	m_mapKey.insert(map<KEY_STATE, KEYINFO*>::value_type(eKeyName, pKey));
	return true;
}

const KEYINFO* CKeyManager::GetKey(const KEY_STATE& eKey) const
{
	map<KEY_STATE, KEYINFO*>::const_iterator iter = m_mapKey.find(eKey);

	if(iter == m_mapKey.end())
	{
		return NULL;
	}
	return iter->second;
}

void CKeyManager::CheckKey(map<KEY_STATE, KEYINFO*>::iterator iter)
{
	static int iCnt = 0;
	if(GetAsyncKeyState(iter->second->iKey) & 0x8000)
	{
		iter->second->bUp = false;
		if(!iter->second->bPush)
		{
			iter->second->bPush = true;
			iter->second->bDown = false;
			
		}
		else
		{
			iter->second->bPush = false;
			iter->second->bDown = true;
			++iCnt;
			int a = 10;
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
			iCnt = 0;
		}
		iter->second->bPush = false;
		iter->second->bDown = false;
	}
}