#pragma once
#include "entity.h"
class CTiger :
	public CEntity
{
private:
	
	// �ù��� �ļյ�(�ִ� �ļյ� 100)
	int		m_Durability;
public:
	void Initialize();
	void Update();
	void Input();

public:
	CTiger(void);
	~CTiger(void);
	//�ù� �ļյ� ����
	void	Attacked( int);

};

