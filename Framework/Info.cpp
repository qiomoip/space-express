#include "Info.h"
#include <tchar.h>

CInfo::CInfo(void)
{
	m_Info = new vector<LPTSTR>;
}


CInfo::~CInfo(void)
{
	//vector<LPTSTR>::iterator it = m_Info->begin();
//	for(; it != m_Info->end(); ++it)
	//	Safe_Delete_Array( it );
	m_Info->clear();
	SAFE_DELETE(m_Info);
}


void CInfo::m_AddInfo(const LPTSTR str)
{
	m_Info->push_back( str );
}

vector<LPTSTR>* CInfo::m_GetInfo()
{
	return m_Info;
}