#include "TString.h"

CTString::CTString(void) 
	: m_String(NULL)
{
	Init();
}


CTString::~CTString(void)
{
	CleanUp();
}

void CTString::Init()
{
	m_String =  new TCHAR[255];
	memset(m_String, 0, sizeof(LPTSTR));

}

void CTString::CleanUp()
{
	Safe_Delete_Array(m_String);
}


LPTSTR	CTString::CharToTCHAR(LPSTR szStr)
{
	LPTSTR szRet = new TCHAR[256];

	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szStr, strlen(szStr) + 1,
		szRet, _tcslen(szRet) + 1);

	return szRet;
}

LPSTR	CTString::TCHARToChar(LPTSTR szStr)
{
	LPSTR szRet = new CHAR[256];
			memset(szRet, 0, sizeof(char) * 256);
			int len = WideCharToMultiByte( CP_ACP, 0, szStr, -1, NULL, 0, NULL, NULL );	
			WideCharToMultiByte( CP_ACP, 0, szStr, -1, szRet, len, NULL, NULL );

	return szRet;
}

HRESULT CTString::Tstrcpy(LPTSTR dest, LPTSTR source)
{
	_tcscpy_s(dest, _tcslen(source)+1, source);
	return S_OK;
}

HRESULT	CTString::Tstrcat(LPTSTR dest, LPTSTR source)
{
	_tcscat_s( dest, _tcslen(dest) + _tcslen(source) + 2, source);
	return S_OK;
}


LPTSTR CTString::GetStr()
{
	return m_String;
}

LPTSTR CTString::Tvprintf(LPTSTR str, ...)
{
	
	LPTSTR dest = NULL;

	dest = new TCHAR[255];

	va_list ap;
	
	va_start(ap, str);

	_vstprintf(dest, 255, str, ap);
	
	va_end(ap);


	Safe_Delete_Array(str);
	return dest;
}

LPTSTR CTString::String(LPTSTR str)
{
	LPTSTR Tstr = NULL;
	Tstr = new TCHAR[255];
	Tstrcpy(Tstr , str);

//	Safe_Delete_Array(str);
	return Tstr;
	
}

//연산자 오버로딩
VOID CTString::operator+=(LPTSTR source)
{
	Tstrcat(m_String, source);

	Safe_Delete_Array(source);
	//return m_String;
}

VOID CTString::operator+=(CTString* source)
{
	Tstrcat(m_String, source->GetStr() );
	Safe_Delete_Array(source);
}

LPTSTR	CTString::operator+(LPTSTR source1)
{
	LPTSTR str = NULL;
	str = new TCHAR[255];
	
	Tstrcpy(str, m_String);
	Tstrcat(str, source1);
	Safe_Delete_Array(source1);
	return str;
}

VOID CTString::operator=(LPTSTR source)
{
	Tstrcpy(m_String, source);
	Safe_Delete_Array(source);
}