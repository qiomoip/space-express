#pragma once
#include "Singleton.h"

class CKeyManager
	: public CSingleton<CKeyManager>
{
	friend CSingleton;
private:
	map<string, KEYINFO*>		m_mapKey;

public:
	void Initialize();
	void Destroy();

public:
	void SetKeyState();
	bool SetKeyData(const string& eKeyName, const int& iKey);
	void CheckKey(map<string, KEYINFO*>::iterator iter);

public:
	const KEYINFO* GetKey(const string& eKey) const;

private:
	CKeyManager(void);
	~CKeyManager(void);
};

