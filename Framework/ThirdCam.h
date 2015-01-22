#pragma once
#include "Camera.h"

class CThirdCam
	: public CCamera
{
public:
	virtual void Init();
	virtual void Update();
	virtual void Input();

public:
	void Yaw();
	void Pitch();
	void Roll();
	void Move();

public:
	CThirdCam(void);
	~CThirdCam(void);
};

