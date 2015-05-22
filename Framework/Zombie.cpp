#include "Zombie.h"


CZombie::CZombie(void) : m_Hero(NULL)
{
}


CZombie::~CZombie(void)
{
	m_Hero = NULL;
}


void CZombie::Initialize()
{
	CEntity::Initialize();
	m_fMoveSpeed *= 0.5f;

	m_vLocalAxis[AT_X] = D3DXVECTOR3(1.f, 0.f, 0.f);
	m_vLocalAxis[AT_Y] = D3DXVECTOR3(0.f, 1.f, 0.f);
	m_vLocalAxis[AT_Z] = D3DXVECTOR3(0.f, 0.f, -1.f);
}

void CZombie::Update()
{
	CEntity::Update();
}

void CZombie::Input()
{
	static bool trigger = false;
	if(GetAsyncKeyState(VK_RETURN) & 0x8000)
		trigger = true;
	if(trigger )
	{
		m_vMove = m_Hero->GetPos() - m_vPos ; 

		D3DXVec3Normalize(&m_vMove, &m_vMove );
		m_vMove *= m_fMoveSpeed;
		m_bTransformUpdate = true;
	}
}


void CZombie::SetHero(CEntity* _hero)
{
	m_Hero = _hero;
}
