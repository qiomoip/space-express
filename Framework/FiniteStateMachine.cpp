#include "FiniteStateMachine.h"
#include "Entity.h"
#include "State.h"
#include "Debug.h"
#include "Zombie.h"
CFiniteStateMachine::CFiniteStateMachine(void)
{
}

CFiniteStateMachine::~CFiniteStateMachine(void)
{
}

void CFiniteStateMachine::Init( CEntity* _owner)
{
	m_pOwner = _owner;
}

void CFiniteStateMachine::SetCurrentState( CState* _state)
{
	m_CurrentState = m_PrevioustState = _state;
	
	_SINGLE(CDebug)->AddText3D( ((CZombie*)m_pOwner)->GetId() , m_pOwner->GetPos(),
		m_CurrentState->ToString());
}

CState* CFiniteStateMachine::GetCurrentState()
{
	return m_CurrentState;
}


void CFiniteStateMachine::Update()
{
	m_CurrentState->Excute(m_pOwner);
	
}

void CFiniteStateMachine::ChangeState( CState* _pState)
{
	//이전과 같은 상태일경우 넘어감.
	if( InState( _pState) )
		return ;
	m_PrevioustState = m_CurrentState;

	m_PrevioustState->Exit(m_pOwner);
	m_CurrentState = _pState;
	m_CurrentState->Enter(m_pOwner);
	
	_SINGLE(CDebug)->AddText3D( ((CZombie*)m_pOwner)->GetId() , m_pOwner->GetPos(),
		m_CurrentState->ToString());
}

void CFiniteStateMachine::RevertState()
{
	CState* temp = m_CurrentState;
	m_CurrentState = m_PrevioustState;
	m_PrevioustState = temp;

	_SINGLE(CDebug)->AddText3D( ((CZombie*)m_pOwner)->GetId() , m_pOwner->GetPos(),
		m_CurrentState->ToString());
}

bool CFiniteStateMachine::InState( CState* _state)
{
	if( _tcscmp( m_CurrentState->ToString(), _state->ToString() ) == 0 )
		return true;
	return false;
}



