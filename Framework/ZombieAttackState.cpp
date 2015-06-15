#include "ZombieAttackState.h"
#include "FiniteStateMachine.h"
#include "Zombie.h"

CZombieAttackState::CZombieAttackState(void)
{
}


CZombieAttackState::~CZombieAttackState(void)
{
}

void CZombieAttackState::Enter(CEntity* _ett)
{
	((CZombie*)_ett)->Attack();
}

void CZombieAttackState::Excute(CEntity* _ett)
{
	CZombie* zombie = (CZombie*)_ett;
	D3DXVECTOR3 vLen = _ett->GetPos() - zombie->GetHero()->GetPos();
	
	//��Ÿ� ������ ������ ���� ���·�
	if( D3DXVec3LengthSq( &vLen) > pow(zombie->GetRange(), 2) )
		zombie->GetFSM()->ChangeState( _SINGLE(CZombieTrackingState) );

	zombie->Attack();
}

void CZombieAttackState::Exit(CEntity*)
{

}

LPTSTR CZombieAttackState::ToString()
{
	return _T("����");
}
