#pragma once

#include "Singleton.h"
#include "Entity.h"
#include "Define.h"
#include "Enum.h"

/*
������Ʈ �Ŵ���
*/

class CObjectManager : public CSingleton<CObjectManager>
{
private:
	friend CSingleton;
	CObjectManager(void);
	~CObjectManager(void);

	map<eTYPE, map<string, CEntity*>>*	m_Objects;

public:

	void Init();
	
	
	
};

