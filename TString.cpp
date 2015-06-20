#include "TString.h"

CTString::CTString(void) 
	: m_String(NULL)
{
	Init();
}

CTString::CTString(LPTSTR str) 
	: m_String(NULL)
{
	Init();
	Tstrcpy(m_String.get(), str);
}

CTString::~CTString(void)
{
	CleanUp();
}

void CTString::Init()
{
	m_String = shared_ptr<TCHAR>(new TCHAR[255]);
	memset(m_String.get(), 0, sizeof(LPTSTR));

}

void CTString::CleanUp()
{
	//Safe_Delete_Array(m_String);
}


LPTSTR	CTString::CharToTCHAR(LPSTR szStr)
{
	LPTSTR szRet(new TCHAR[256]);

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


shared_ptr<TCHAR> CTString::GetStr()
{
	return m_String;
}

shared_ptr<TCHAR> CTString::Tvprintf(LPTSTR str, ...)
{
	
	shared_ptr<TCHAR> dest(new TCHAR[255]);

	va_list ap;
	
	va_start(ap, str);

	_vstprintf(dest.get(), 255, str, ap);
	
	va_end(ap);


	//Safe_Delete_Array(str);
	return dest;
}
/*
LPTSTR CTString::String(LPTSTR str)
{
	LPTSTR Tstr = NULL;
	Tstr = new TCHAR[255];
	Tstrcpy(Tstr , str);
	
	return Tstr;
	
}*/

//연산자 오버로딩
VOID CTString::operator+=(LPTSTR source)
{
	Tstrcat(m_String.get(), source);

	//Safe_Delete_Array(source);
	//return m_String;
}

VOID CTString::operator+=(CTString* source)
{
	Tstrcat(m_String.get(), source->GetStr().get());
	//Safe_Delete_Array(source);
}

VOID CTString::operator+=(D3DXVECTOR3 vec)
{
	shared_ptr<TCHAR> str(new TCHAR[100]);
	Tstrcat(str.get(), Tvprintf(_T(" (%.2f, %.2f, %.2f) "), vec.x, vec.y, vec.z).get() );
	Tstrcat(m_String.get(),  str.get());
}


shared_ptr<TCHAR>	CTString::operator+(LPTSTR source1)
{
	shared_ptr<TCHAR> str(new TCHAR[255]);
	
	Tstrcpy(str.get(), m_String.get() );
	Tstrcat(str.get(), source1 );
	
	//Safe_Delete_Array(source1);
	return str;
}

shared_ptr<TCHAR>	CTString::operator+(CTString* source1)
{
	shared_ptr<TCHAR> str(new TCHAR[255]);
	
	Tstrcpy(str.get(), m_String.get() );
	Tstrcat(str.get(), source1->GetStr().get() );
	
	//Safe_Delete_Array(source1);
	return str;
}

shared_ptr<TCHAR> CTString::operator+(D3DXVECTOR3 vec)
{
	shared_ptr<TCHAR> str(new TCHAR[10]);
	Tstrcpy(str.get(), m_String.get());
	Tstrcat(str.get(), Tvprintf(_T(" (%.2f, %.2f, %.2f) "), vec.x, vec.y, vec.z).get() );
	//Safe_Delete_Array(source1);
	return str;

}

VOID CTString::operator=(LPTSTR source)
{
	Tstrcpy(m_String.get(), source);
	//Safe_Delete_Array(source);
}