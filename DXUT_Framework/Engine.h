#pragma once
#include "Singleton.h"
/*
���� Ŭ����
�ֻ��� Ŭ������ �Ŵ��� Ŭ������ �����Ѵ�.
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

