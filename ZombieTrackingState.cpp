
#include "FiniteStateMachine.h"

#include "Zombie.h"
#include "Entity.h"

CZombieTrackingState::CZombieTrackingState(void)
{
}


CZombieTrackingState::~CZombieTrackingState(void)
{
}

void CZombieTrackingState::Enter(CEntity* _ett)
{
	_ett;
}

void CZombieTrackingState::Excute(CEntity* _ett)
{
	CZombie* zombie = (CZombie*)_ett;
	D3DXVECTOR3 vLen = _ett->GetPos() - zombie->GetHero()->GetPos();
	
	//추적하다 사정거리로 들어오면 공격 
	if( D3DXVec3LengthSq( &vLen) < pow(zombie->GetRange(), 2) )
		zombie->GetFSM()->ChangeState( _SINGLE(CZombieAttackState) );
	
	//추적하다가 시야 범위 밖으로 나가면 이전 상태로 전이.
	else if( D3DXVec3LengthSq( &vLen) >= pow(zombie->GetVisibility(), 2) )
		zombie->GetFSM()->ChangeState( _SINGLE(CZombieIdleState) );

	//추적 계속하기
	D3DXVECTOR3 vMove= zombie->GetHero()->GetPos() - 
		zombie->GetPos(); 

	D3DXVec3Normalize(&vMove, &vMove );
	zombie->SetMove( vMove);
	

}

void CZombieTrackingState::Exit(CEntity* _ett)
{
	_ett;
}

TCHAR* CZombieTrackingState::ToString()
{
	return _T("추적");
}
