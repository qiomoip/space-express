/*------------------------------------------------------
Project : ����
Edited  : ������

Memo    : ����ȭ Ŭ����
--------------------------------------------------------*/

#pragma once

#include "define.h"
#include "protocol.h"

class CCriticalSection
{
public:
	CCriticalSection();
	~CCriticalSection();

	void Lock();
	void Unlock();
private:
	CRITICAL_SECTION	m_cs;

};

class CSynchronize
{
public:
	CSynchronize(CCriticalSection& CS)
		:m_pSync(&CS)
	{
		m_pSync->Lock();
	}
	~CSynchronize(void)
	{
		m_pSync->Unlock();
	}

private:
	CCriticalSection*		m_pSync;
};
