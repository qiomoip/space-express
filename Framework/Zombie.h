#pragma once
#include "Entity.h"

class CFiniteStateMachine;

class CZombie : public CEntity
{
private:
	//���� ���� ��ȣ
	int			m_Id;
	//�Ѿư� ���ΰ�
	CEntity*	m_Hero;	
	//�þ߰Ÿ�
	float		m_Visibility;
	//�̵��� �Ÿ� ����.
	D3DXVECTOR3 m_vMoveDir;
	//���ݷ�
	float		m_fPower;
	//���� �ӵ�
	float		m_fAttackSpeed;
	//����ð�(���ݼӵ� ���꿡 ���)
	double		m_fElapsedTime;
	//�����Ÿ�
	float		m_fRange;
	//FSM��ü
	CFiniteStateMachine*		m_pFSM;
public:
	CZombie(void);
	~CZombie(void);

	void Initialize();
	void Update();
	void Input();
	//�ù��� �ļյ� �߰�(���ο��� �ӵ� ����)
	void Attack(/*CEntity**/ );
	//setter
	//���� ��ǥ ����
	void SetHero(CEntity*);
	//move�Լ� ����, �̵� ���� true
	void SetMove(D3DXVECTOR3);
	//getter
	CEntity* GetHero();
	//ID ���
	int  GetId();
	//FSM ��ȯ
	CFiniteStateMachine* GetFSM();
	//�þ߰Ÿ� ��ȯ
	float GetVisibility();
	
	D3DXVECTOR3 GetMove();

	float GetPower();

	float GetRange();

	
};

