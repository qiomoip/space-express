#pragma once
#include "define.h"
#include <memory>
/*
문자열 클래스

분리 헤더 필요한 헤더
tchar.h
windows.h
문자열 상수를 입력할때 _T대신 _S를 사용
*/

class CTString
{
public:
	CTString(void);
	CTString(LPTSTR str);
	~CTString(void);
	
	void					Init();
	void					CleanUp();

	static shared_ptr<TCHAR>	CharToTCHAR(LPSTR szStr);	//TCHAR을 char 형태로
	static LPSTR				TCHARToChar(LPTSTR szStr);	//char을 TCHAR 형태로
	
	//문자열 삽입
	static HRESULT				Tstrcpy(LPTSTR dest, LPTSTR source);
	//문자열 붙이기
	static HRESULT				Tstrcat(LPTSTR dest, LPTSTR source);
	//변수포함 문자열 출력
	static shared_ptr<TCHAR>	Tvprintf(LPTSTR str, ...);

	shared_ptr<TCHAR>			GetStr();

	//문자열 상수를 문자열 변수로 변환
	// _S("문자열"); 으로 사용하면 이 함수를 자동으로 호출해 준다.
	//static LPTSTR			String( LPTSTR str);
	

	//연산자 오버로딩
	VOID						operator+=(LPTSTR source);
	VOID						operator+=(CTString* source);
	VOID						operator+=(D3DXVECTOR3 vector);

	shared_ptr<TCHAR>			operator+(LPTSTR source1);
	shared_ptr<TCHAR>			operator+(CTString* source1);
	shared_ptr<TCHAR>			operator+(D3DXVECTOR3 vector);
	VOID						operator=(LPTSTR source);
	
private:
	//로그
	shared_ptr<TCHAR>		m_String;
};


//_stprintf_s(std, _T("std %d"), 123);

#define _S(_STR_)	CTString::String(_T(_STR_))

