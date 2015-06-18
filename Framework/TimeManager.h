#pragma once
#include "singleton.h"

class CTimeManager :
	public CSingleton<CTimeManager>
{
	friend CSingleton;
private:
	CTimeManager(void);
	~CTimeManager(void);

private :
	//FPS
	UINT			m_FPS;
	//FPS측정용 시간
	TIME_INFO		m_TimeInfo;
	float			m_FrameCnt;
	//타이머 관리용 di값.
	std::map<UINT, TIME_INFO> m_Timer;

public:

	void Init();
	void CleanUp();
	//getter;
	double GetDeltaTime();

	//FPS체크
	void CheckFps();
	//타이머 체크 새로운ID값이면 타이머를 생성한다.(ID, 주기, 일회성 여부)
	bool CheckTime(UINT id, float cycle, bool isOnetime = false);
	//타이머 제거
	bool KillTimer(UINT id);
	
};

