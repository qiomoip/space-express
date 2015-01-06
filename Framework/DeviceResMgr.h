#pragma once
#include "define.h"
#include "Singleton.h"

class CDeviceResMgr
	: public CSingleton<CDeviceResMgr>
{
	friend CSingleton;

private:
	CDeviceResMgr(void);
	~CDeviceResMgr(void);
};

