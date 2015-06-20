#include "TimeManager.h"
#include "Debug.h"


CTimeManager::CTimeManager(void)
	: m_FPS(0)
	, m_FrameCnt(0)
{
	Init();
}


CTimeManager::~CTimeManager(void)
{
	CleanUp();
}

void CTimeManager::Init()
{
	memset(&m_TimeInfo, 0, sizeof(TIME_INFO) );
	m_TimeInfo.m_CurrentTime = m_TimeInfo.m_PreviousTime = timeGetTime() * 0.001;
}

void CTimeManager::CleanUp()
{
	m_Timer.clear();
}




double CTimeManager::GetDeltaTime()
{
	return m_TimeInfo.m_DeltaTime;
}

void CTimeManager::CheckFps()
{
	m_TimeInfo.m_CurrentTime = timeGetTime() * 0.001;
	m_TimeInfo.m_DeltaTime = (m_TimeInfo.m_CurrentTime - m_TimeInfo.m_PreviousTime);
	m_TimeInfo.m_ElapsedTime += m_TimeInfo.m_DeltaTime;
	m_TimeInfo.m_PreviousTime = m_TimeInfo.m_CurrentTime;
	m_FrameCnt++;

	if(m_TimeInfo.m_ElapsedTime >= 1.0)
	{
		m_FPS = (UINT)(m_FrameCnt / m_TimeInfo.m_ElapsedTime);

#ifdef _DEBUG
		_SINGLE(CDebug)->AddStaticLog(LOG_FPS, _T("FPS : %d"), m_FPS );
#endif

		m_TimeInfo.m_ElapsedTime = 0.0;
		m_FrameCnt = 0.f;
	}
}


bool CTimeManager::CheckTime(UINT _id, float _cycle, bool _isOneTime)
{
	std::map<UINT, TIME_INFO>::iterator it = m_Timer.find(_id);

	TIME_INFO time;
	memset(&time, 0, sizeof(TIME_INFO) );
	
	//Ÿ�̸Ӱ� �ִٸ� üũ
	if (it != m_Timer.end() )
	{
		time = it->second;
		time.m_CurrentTime = timeGetTime() * 0.001;

		time.m_DeltaTime = time.m_CurrentTime - time.m_PreviousTime;
		time.m_PreviousTime = time.m_CurrentTime;

		time.m_ElapsedTime += time.m_DeltaTime;
		


		//�ð��� ������
		if( time.m_ElapsedTime > _cycle )
		{
			//��ȸ���̸� �ٷ� ����
			if( _isOneTime )
			{
				m_Timer.erase(it );
				return true;
			}
			//��ȸ���� �ƴ϶�� �׳� ����
			time.m_ElapsedTime = 0.0;
			it->second = time;
			return true;
		}
		it->second = time;
		return false;
		
	}
	else 
	{
		//Ÿ�̸Ӱ� ���ٸ� ���� ����
		time.m_CurrentTime = time.m_PreviousTime = timeGetTime() * 0.001;
		m_Timer.insert(map<UINT, TIME_INFO>::value_type(_id, time) );
		return false;
	}
	return false;
}


bool CTimeManager::KillTimer(UINT _id)
{
	std::map<UINT, TIME_INFO>::iterator it = m_Timer.find(_id);
	if( it != m_Timer.end() )
	{
		m_Timer.erase(it );
		return true;
	}
	return false;
}
