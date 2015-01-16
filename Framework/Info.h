#pragma once
#include "define.h"

class CInfo
{
private:

	vector<LPTSTR>*			m_Info;	

public:
	CInfo(void);
	~CInfo(void);

	void					m_AddInfo(LPTSTR str);

	vector<LPTSTR>*			m_GetInfo();
};

