#pragma once
#include "ZombieTrackingState.h"
#include "ZombieAttackState.h"
#include "ZombieIdleState.h"

class CState ;
class CEntity;
class CFiniteStateMachine
{
private:

	CEntity*	m_pOwner;
	CState*		m_CurrentState;
	CState*		m_PrevioustState;

public:
	CFiniteStateMachine(void);
	~CFiniteStateMachine(void);

public:
	//�ʱ�ȭ
	void Init(CEntity*);
	//���� ���� ����
	void SetCurrentState( CState* );
	CState* GetCurrentState();

	//������Ʈ
	void Update();
	//���� ��ȭ
	void ChangeState( CState*);
	//���� ���·� ���ư�
	void RevertState();
	//Ư�� ���¿� �ִ°�
	bool InState( CState* );
	
	
};
//#define FSM CFiniteStateMachine