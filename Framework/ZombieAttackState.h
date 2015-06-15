#pragma once
#include "state.h"
#include "Singleton.h"

class CZombieAttackState :
	public CState, public CSingleton<CZombieAttackState>
{
	friend CSingleton;
private:
	CZombieAttackState(void);
	~CZombieAttackState(void);
public:

	void Enter(CEntity*);

	void Excute(CEntity*);

	void Exit(CEntity*);

	LPTSTR ToString();
};

