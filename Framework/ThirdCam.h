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
	void Rotation();

public:
	CThirdCam(void);
	~CThirdCam(void);
};

