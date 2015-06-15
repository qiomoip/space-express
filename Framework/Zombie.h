#pragma once
#include "Entity.h"

class CFiniteStateMachine;

class CZombie : public CEntity
{
private:
	//좀비 구분 번호
	int			m_Id;
	//쫓아갈 주인공
	CEntity*	m_Hero;	
	//시야거리
	float		m_Visibility;
	//이동할 거리 저장.
	D3DXVECTOR3 m_vMoveDir;
	//공격력
	float		m_fPower;
	//공격 속도
	float		m_fAttackSpeed;
	//경과시간(공격속도 연산에 사용)
	double		m_fElapsedTime;
	//사정거리
	float		m_fRange;
	//FSM객체
	CFiniteStateMachine*		m_pFSM;
public:
	CZombie(void);
	~CZombie(void);

	void Initialize();
	void Update();
	void Input();
	//택배의 파손도 추가(내부에서 속도 조절)
	void Attack(/*CEntity**/ );
	//setter
	//따라갈 목표 설정
	void SetHero(CEntity*);
	//move함수 설정, 이동 상태 true
	void SetMove(D3DXVECTOR3);
	//getter
	CEntity* GetHero();
	//ID 출력
	int  GetId();
	//FSM 반환
	CFiniteStateMachine* GetFSM();
	//시야거리 반환
	float GetVisibility();
	
	D3DXVECTOR3 GetMove();

	float GetPower();

	float GetRange();

	
};

