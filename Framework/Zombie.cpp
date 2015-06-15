#include "Zombie.h"
#include "FiniteStateMachine.h"
#include "Debug.h"
#include "Frustum.h"
#include "ObjectManager.h"
#include "Tiger.h"

CZombie::CZombie(void) : 
	m_Hero(NULL), 
	m_pFSM(NULL),
	m_Id(0),
	m_Visibility(20.f),
	m_fPower(10.f),
	m_fRange(2.5f),
	m_fAttackSpeed(2.f),
	m_fElapsedTime(0.0)
{
	static int id = 0;
	m_Id = id++;
}


CZombie::~CZombie(void)
{
	m_Hero = NULL;
	Safe_Delete(m_pFSM);
}

void CZombie::Initialize()
{
	CEntity::Initialize();
	m_fMoveSpeed = 0.f;

	m_vLocalAxis[AT_X] = D3DXVECTOR3(1.f, 0.f, 0.f);
	m_vLocalAxis[AT_Y] = D3DXVECTOR3(0.f, 1.f, 0.f);
	m_vLocalAxis[AT_Z] = D3DXVECTOR3(0.f, 0.f, -1.f);

	m_pFSM = new CFiniteStateMachine();
	m_pFSM->Init( this );
	m_pFSM->SetCurrentState( _SINGLE(CZombieIdleState) ); 

	memset(&m_vMoveDir, 0, sizeof( D3DXVECTOR3) );
}

void CZombie::Update()
{
	//m_pFSM->Update();

	if(m_pMesh )
	{
		if (_SINGLE(CFrustum)->isInFrustum( m_vPos, GetSize() ) )
		{
			SetVisiable(true);
			_SINGLE(CObjectManager)->Push_RenderList(this);
		}
		else 
			SetVisiable(false);
	}
	memcpy(&m_matTrans._41, &m_vPos, sizeof(D3DXVECTOR3));

	if(m_bTransformUpdate)
	{
		Rotation();
		Move();
		for(int i = 0; i < AT_MAX; ++i)
		{
			//축 세팅
			D3DXVec3TransformNormal(&m_vWorldAxis[i], &m_vLocalAxis[i], &m_matRot);
			D3DXVec3Normalize(&m_vWorldAxis[i], &m_vWorldAxis[i]);
		}

		m_bTransformUpdate = false;
	}

	_SINGLE(CDebug)->AddText3D( m_Id , m_vPos,
		m_pFSM->GetCurrentState()->ToString());
}

void CZombie::Input()
{
	m_fMoveSpeed = 3.f * _SINGLE(CDebug)->GetDeltaTime();

	m_pFSM->Update();
	//D3DXVECTOR3 vLen = m_vPos - m_Hero->GetPos();
	//float fSeeDist = 20.f;
	////추적상태 전환 조건
	//if( D3DXVec3Length( &vLen ) < fSeeDist )	
	//	m_pFSM->ChangeState( _SINGLE(CZombieTrackingState) ); 
	////추적상태에서 대기 상태 전환 조건
	//else /*if(GetAsyncKeyState(VK_BACK) & 0x8000)*/
	//	m_pFSM->RevertState();
	//상태별 행동 구현
/*	if( m_pFSM->InState(_SINGLE(CZombieTrackingState)) )
	{
		m_vMove = m_Hero->GetPos() - m_vPos ; 

		D3DXVec3Normalize(&m_vMove, &m_vMove );
		m_vMove *= m_fMoveSpeed;
		m_bTransformUpdate = true;
	}*/
}

void CZombie::Attack(/*CEntity* _ett*/)
{
	//힘 만큼 택배의 파손도를 증가시킴.
	m_fElapsedTime -= _SINGLE(CDebug)->GetDeltaTime();
	if( m_fElapsedTime <= 0.0 )
	{
		((CTiger*)m_Hero)->Attacked( m_fPower );
		m_fElapsedTime = (double)m_fAttackSpeed;
	}
}



void CZombie::SetHero(CEntity* _hero)
{
	m_Hero = _hero;
}

void CZombie::SetMove(D3DXVECTOR3 _move)
{
	m_vMoveDir = _move * m_fMoveSpeed;
	m_vMove = m_vMoveDir;
	
	m_bTransformUpdate = true;
}


CEntity* CZombie::GetHero()
{
	return m_Hero;
}


int CZombie::GetId()
{
	return m_Id;
}


CFiniteStateMachine* CZombie::GetFSM()
{
	return m_pFSM;
}


float CZombie::GetVisibility()
{
	return m_Visibility;
}

D3DXVECTOR3 CZombie::GetMove()
{
	return m_vMoveDir;
}

float CZombie::GetPower()
{
	return m_fPower;
}

float CZombie::GetRange()
{
	return m_fRange;
}

