#pragma once
#include "define.h"
/*
문자열 클래스

분리 헤더 필요한 헤더
tchar.h
windows.h
*/

class CTString
{
public:
	CTString(void);
	~CTString(void);
	
	void					Init();
	void					CleanUp();

	static LPTSTR			CharToTCHAR(LPSTR szStr);	//TCHAR을 char 형태로
	static LPSTR			TCHARToChar(LPTSTR szStr);	//char을 TCHAR 형태로
	
	static HRESULT			Tstrcpy(LPTSTR dest, LPTSTR source);
	static HRESULT			Tstrcat(LPTSTR dest, LPTSTR source);
	static LPTSTR			Tvprintf(LPTSTR str, ...);

	LPTSTR					GetStr();
	

	//연산자 오버로딩
	VOID					operator+=(LPTSTR source);
	VOID					operator+=(CTString* source);

	LPTSTR					operator+(LPTSTR source1);
	VOID					operator=(LPTSTR source);
	
private:
	//로그
	LPTSTR			m_String;
};


//_stprintf_s(std, _T("std %d"), 123);
