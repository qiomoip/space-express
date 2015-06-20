#pragma once
#include "entity.h"
class CTiger :
	public CEntity
{
private:
	
	// 택배의 파손도(최대 파손도 100)
	int		m_Durability;
public:
	void Initialize();
	void Update();
	void Input();

public:
	CTiger(void);
	~CTiger(void);
	//택배 파손도 증가
	void	Attacked( int);

};

