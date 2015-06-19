#pragma once
#include "Entity.h"

class CBaseButton
	: public CEntity
{
protected:
	RECT	m_tRC;

public:
	void Input();

public:
	//버튼의 렉트 구조체를 셋팅(필수)
	void SetRectData(const RECT& tRect);

	//pt는 마우스의 위치 (뷰포트 좌표)
	bool IntersectPT( const POINT& pt );

public:
	//버튼이 눌렸을 때 실행될 함수 (반드시 정의하도록 PURE)
	virtual void Schedule()PURE;
	

public:
	CBaseButton(void);
	virtual ~CBaseButton(void);
};

