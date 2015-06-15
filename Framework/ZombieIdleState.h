#pragma once
#include "State.h"
#include "Singleton.h"

class CZombieIdleState
	: public CState, public CSingleton<CZombieIdleState>
{
	friend CSingleton;
private:
	//�̵� �� ����
	D3DXVECTOR3 m_vEnd;
	//�̵� �� �ð�(s)
	float		m_fMove;
	//�� ���� �ð�(s)
	float		m_fStay;
	//�̵� ���� �۶�����
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

