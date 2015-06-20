#pragma once
#include "state.h"
#include "Singleton.h"
class CZombieTrackingState :
	public CState, public CSingleton<CZombieTrackingState>
{
	friend CSingleton;
private:
	CZombieTrackingState(void);
	~CZombieTrackingState(void);
public:

	void Enter(CEntity*);

	void Excute(CEntity*);

	void Exit(CEntity*);

	LPTSTR ToString();
};

