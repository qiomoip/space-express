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
	//��ư�� ��Ʈ ����ü�� ����(�ʼ�)
	void SetRectData(const RECT& tRect);

	//pt�� ���콺�� ��ġ (����Ʈ ��ǥ)
	bool IntersectPT( const POINT& pt );

public:
	//��ư�� ������ �� ����� �Լ� (�ݵ�� �����ϵ��� PURE)
	virtual void Schedule()PURE;
	

public:
	CBaseButton(void);
	virtual ~CBaseButton(void);
};

