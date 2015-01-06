#pragma once

#include "Singleton.h"
#include "Define.h"

/*
������Ʈ �Ŵ���
������Ʈ�� �����Ͽ�...

*/

class CEntity;

class CObjectManager : public CSingleton<CObjectManager>
{
private:
	friend CSingleton;
	CObjectManager(void);
	~CObjectManager(void);

	map<eTYPE, map<string, CEntity*>>*	m_Objects;

public:

	void								Init();
	
	void								CleanUp();

	bool								Load();
	
};

