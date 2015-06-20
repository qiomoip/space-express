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
	//��� ���� ���� ���Ŀ� �۶�����...
	m_isStay = true;
	m_fStay = 1.0f;
	_ett;
}

void CZombieIdleState::Excute(CEntity* _ett)
{
	CZombie* zombie = (CZombie*)_ett;
	D3DXVECTOR3 vLen = _ett->GetPos() - zombie->GetHero()->GetPos();
	
	//�þ߿� ���ΰ��� ������ �Ѵ� ���·� ��ȭ
	if( D3DXVec3LengthSq( &vLen) <= pow(zombie->GetVisibility(), 2) )
	{
		zombie->GetFSM()->ChangeState( _SINGLE(CZombieTrackingState) );
		return ;
	}
	//��ȸ�ϱ� 

	static double elapsedTime = 0.0;
	elapsedTime += _SINGLE(CTimeManager)->GetDeltaTime();
	//�۶����� ���¶��
	if( m_isStay)
	{
		//�ð��� ������� �ʾҴ���?
		if(elapsedTime < (double)m_fStay )
			return ;
		else//��� �ƴٸ�,
		{
			m_isStay = false;
			//�̵��� ���� ����
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
		}//����ð� üũ
	}
	else //�۶����� ���°� �ƴ϶��
	{
		if(elapsedTime < (double)m_fMove)
		{//�ð��� ������� ������ ��� �̵�
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
	return _T("���");
}
