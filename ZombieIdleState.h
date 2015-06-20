#pragma once
#include "State.h"
#include "Singleton.h"

class CZombieIdleState
	: public CState, public CSingleton<CZombieIdleState>
{
	friend CSingleton;
private:
	//이동 할 방향
	D3DXVECTOR3 m_vEnd;
	//이동 할 시간(s)
	float		m_fMove;
	//멍 때릴 시간(s)
	float		m_fStay;
	//이동 할지 멍때릴지
	bool		m_isStay;

private:
	CZombieIdleState(void);
	~CZombieIdleState(void);
public:
	void Enter(CEntity*);
	void Excute(CEntity*);
	void Exit(CEntity*);

	LPTSTR ToString();
};

