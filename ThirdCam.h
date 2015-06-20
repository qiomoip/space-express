#pragma once
#include "Camera.h"

class CEntity;

class CThirdCam
	: public CCamera
{
private:
	CEntity*		m_pLookObject;
	D3DXVECTOR3		m_vDist;

	//y축 회전시 카메라도 회전하고 싶을 때 사용하는 초기값
	//룩 오브젝트를 설정할 때 같이 설정
	D3DXVECTOR3		m_vInitRight;
	D3DXVECTOR3		m_vInitUp;
public:
	virtual void Init();
	virtual void Update();
	virtual void Input();

public:
	void Yaw();
	void Pitch();
	void Roll();
	void Move();
	void Rotation();

public:
	void SetLookObject(CEntity* pEntity);

public:
	CThirdCam(void);
	~CThirdCam(void);
};

