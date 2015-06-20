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
	//FPS������ �ð�
	TIME_INFO		m_TimeInfo;
	float			m_FrameCnt;
	//Ÿ�̸� ������ di��.
	std::map<UINT, TIME_INFO> m_Timer;

public:

	void Init();
	void CleanUp();
	//getter;
	double GetDeltaTime();

	//FPSüũ
	void CheckFps();
	//Ÿ�̸� üũ ���ο�ID���̸� Ÿ�̸Ӹ� �����Ѵ�.(ID, �ֱ�, ��ȸ�� ����)
	bool CheckTime(UINT id, float cycle, bool isOnetime = false);
	//Ÿ�̸� ����
	bool KillTimer(UINT id);
	
};

