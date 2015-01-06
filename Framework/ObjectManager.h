#pragma once

#include "Singleton.h"
#include "Define.h"

/*
오브젝트 매니저
오브젝트를 관리하오...

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

