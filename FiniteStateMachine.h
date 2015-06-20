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
	//초기화
	void Init(CEntity*);
	//현재 상태 정보
	void SetCurrentState( CState* );
	CState* GetCurrentState();

	//업데이트
	void Update();
	//상태 변화
	void ChangeState( CState*);
	//이전 상태로 돌아감
	void RevertState();
	//특정 상태에 있는가
	bool InState( CState* );
	
	
};
//#define FSM CFiniteStateMachine