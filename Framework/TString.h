#pragma once
#include "Singleton.h"
/*
DirectX용 문자열 클래스
*/
class CTString : public CSingleton<CTString>
{
	friend CSingleton;

public:
	LPTSTR			CharToTCHAR(LPSTR szStr);	//TCHAR을 char 형태로
	LPSTR			TCHARToChar(LPTSTR szStr);	//char을 TCHAR 형태로
	
	HRESULT			Tstrcpy(LPTSTR dest, LPTSTR source);
	HRESULT			Tstrcat(LPTSTR dest, LPTSTR source);
	//즉석에서 띄울 메세지
	HRESULT			DrawFont(LPTSTR str );
	//항상 화면에 듸울 메세지
	HRESULT			DrawLog();

	HRESULT			AddLog(LPTSTR _log);

private:

	//D3D 폰트 변수
	LPD3DXFONT		m_pFont;
	D3DXFONT_DESC	m_Desc;
	RECT			m_FontRect;
	RECT			m_LogRect;
	//로그
	LPTSTR*			m_Log;
	int				m_LogCount;


	void			Init();
	void			CleanUp();
	CTString(void);
	~CTString(void);
};


//_stprintf_s(std, _T("std %d"), 123);
