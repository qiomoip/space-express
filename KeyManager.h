#pragma once
#include "Singleton.h"

class CKeyManager
	: public CSingleton<CKeyManager>
{
	friend CSingleton;
private:
	map<KEY, KEYINFO*>		m_mapKey;

public:
	void Initialize();
	void Destroy();

public:
	void SetKeyState();
	bool SetKeyData(const KEY eKeyName, const int& iKey);
	void CheckKey(map<KEY, KEYINFO*>::iterator iter);
public:
	const KEYINFO* GetKey(const KEY eKey) const;

private:
	CKeyManager(void);
	~CKeyManager(void);
};

