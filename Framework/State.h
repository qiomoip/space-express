#pragma once
#include "define.h"

class CEntity;
class CState
{
protected:
	CState(void){}
	~CState(void){}

public :

	virtual void Enter(CEntity*)=0;
	virtual void Excute(CEntity*)=0;
	virtual void Exit(CEntity*)=0;

	virtual LPTSTR ToString()=0;
};

