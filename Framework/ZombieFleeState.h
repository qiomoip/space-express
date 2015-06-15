#pragma once
#include "state.h"
#include "Singleton.h"
class CZombieFleeState :
	public CState, public CSingleton<CZombieFleeState>
{
	friend CSingleton;
private:
	CZombieFleeState(void);
	~CZombieFleeState(void);
public:
	void Enter(CEntity*);

	void Excute(CEntity*);

	void Exit(CEntity*);

	LPTSTR ToString();
};

