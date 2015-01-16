#pragma once
#include "Singleton.h"
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

