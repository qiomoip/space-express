#pragma once
#include "Entity.h"



class CZombie : public CEntity
{
private:
	CEntity*	m_Hero;	
public:
	CZombie(void);
	~CZombie(void);

	void Initialize();
	void Update();
	void Input();

	
	
	void SetHero(CEntity*);
};

