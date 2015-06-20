#include "ZombieIdleState.h"
#include "ZombieTrackingState.h"
#include "FiniteStateMachine.h"
#include "Entity.h"
#include "Zombie.h"
#include "Debug.h"
#include "TimeManager.h"

#include <time.h>
CZombieIdleState::CZombieIdleState(void) :
	m_fMove(0.f),
	m_fStay(0.f),
	m_isStay(true)
{
	memset( &m_vEnd, 0, sizeof(D3DXVECTOR3) );
}


CZombieIdleState::~CZombieIdleState(void)
{
}


void CZombieIdleState::Enter(CEntity* _ett)
{
	//대기 상태 진입 직후엔 멍때리기...
	m_isStay = true;
	m_fStay = 1.0f;
	_ett;
}

void CZombieIdleState::Excute(CEntity* _ett)
{
	CZombie* zombie = (CZombie*)_ett;
	D3DXVECTOR3 vLen = _ett->GetPos() - zombie->GetHero()->GetPos();
	
	//시야에 주인공이 들어오면 쫓는 상태로 변화
	if( D3DXVec3LengthSq( &vLen) <= pow(zombie->GetVisibility(), 2) )
	{
		zombie->GetFSM()->ChangeState( _SINGLE(CZombieTrackingState) );
		return ;
	}
	//배회하기 

	static double elapsedTime = 0.0;
	elapsedTime += _SINGLE(CTimeManager)->GetDeltaTime();
	//멍때리는 상태라면
	if( m_isStay)
	{
		//시간이 경과되지 않았는지?
		if(elapsedTime < (double)m_fStay )
			return ;
		else//경과 됐다면,
		{
			m_isStay = false;
			//이동할 방향 선정
			srand( (unsigned)time(NULL));
			
			int dir = rand()% 4; 
			dir *= zombie->GetPos().x;
			dir %= 4;
			if(dir == 0 )
				m_vEnd = D3DXVECTOR3(1.0f, 0, 0);
			else if( dir == 1)
				m_vEnd = D3DXVECTOR3(0, 0, 1.f);
			else if( dir == 2)
				m_vEnd = D3DXVECTOR3(-1.0f, 0, 0);
			else if( dir == 3)
				m_vEnd = D3DXVECTOR3(0, 0, -1.f);

			zombie->SetMove( m_vEnd );
			m_fMove = 2.f;
			elapsedTime = 0.0;
		}//경과시간 체크
	}
	else //멍때리는 상태가 아니라면
	{
		if(elapsedTime < (double)m_fMove)
		{//시간이 경과되지 않으면 계속 이동
			zombie->SetMove( zombie->GetMove() );
			return ;
		}
		else
		{
			m_isStay = true;
			m_fStay = 1.f;
			elapsedTime = 0.0;
		}

	}

}

void CZombieIdleState::Exit(CEntity* _ett)
{
	_ett;
}

TCHAR* CZombieIdleState::ToString()
{
	return _T("대기");
}
