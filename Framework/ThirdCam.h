#pragma once
#include "Camera.h"

class CEntity;

class CThirdCam
	: public CCamera
{
private:
	CEntity*		m_pLookObject;
	D3DXVECTOR3		m_vDist;
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

