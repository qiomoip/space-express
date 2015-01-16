#pragma once
#include "Singleton.h"
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
	
	map<eTYPE, map<LPTSTR, CEntity*>>*	m_Objects;

public:

	void								Init();
	
	void								CleanUp();

	bool								Load();
	
#ifdef _DEBUG
private:	
	CInfo*									m_Info;
#endif
};

