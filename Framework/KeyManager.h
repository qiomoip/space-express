#pragma once
#include "Singleton.h"

class CKeyManager
	: public CSingleton<CKeyManager>
{
	friend CSingleton;
private:
	map<KEY_STATE, KEYINFO*>		m_mapKey;

public:
	void SetKeyState();
	bool SetKeyData(const KEY_STATE& eKeyName, const int& iKey);
	void CheckKey(map<KEY_STATE, KEYINFO*>::iterator iter);

public:
	const KEYINFO* GetKey(const KEY_STATE& eKey) const;

private:
	CKeyManager(void);
	~CKeyManager(void);
};

