#pragma once
#include "Singleton.h"
class CMouse
	:public CSingleton<CMouse>
{
private:
	
public:
	CMouse(void);
	~CMouse(void);
};

