
#include "Sync.h"
#define		SPINCOUNT	4000 // 보통 스핀카운터 매직넘버 4천 따름

CCriticalSection::CCriticalSection()
{
// spincount 함수가 사용가능한 윈도우2000이상 아니면 기존함수 사용
#if(_WIN32_WINNT >= 0x0500)
	InitializeCriticalSectionAndSpinCount(&m_cs,SPINCOUNT);
#else
	InitializeCriticalSection(&m_cs);
#endif
}

CCriticalSection::~CCriticalSection()
{
	DeleteCriticalSection(&m_cs);
}

void CCriticalSection::Lock()
{
#if(_WIN32_WINNT >= 0x4000)
	TryEnterCriticalSection(&m_cs);
#else
	EnterCriticalSection(&m_cs);
#endif
}

void CCriticalSection::Unlock()
{
	LeaveCriticalSection(&m_cs);
}
