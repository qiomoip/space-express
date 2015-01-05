#pragma once
#include "Singleton.h"
/*
엔진 클래스
최상위 클래스로 매니저 클래스를 관리한다.
*/
class Engine : public Singleton<Engine>
{

public:
	Engine(void) {};
	~Engine(void){KillInstance();};

	void Init();

	void FrameMove();

	void FrameRender();
};

