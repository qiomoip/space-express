
#include "Sync.h"
#define		SPINCOUNT	4000 // ���� ����ī���� �����ѹ� 4õ ����

CCriticalSection::CCriticalSection()
{
// spincount �Լ��� ��밡���� ������2000�̻� �ƴϸ� �����Լ� ���
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
