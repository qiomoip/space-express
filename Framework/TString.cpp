#include "TString.h"
#include "Device.h"

CTString::CTString(void) : m_pFont(NULL), m_LogCount(0)
{
	Init();
}


CTString::~CTString(void)
{
	CleanUp();
}

void CTString::Init()
{
	 m_Log =  new LPTSTR[LOG_COUNT];
	for(int i = 0 ; i < LOG_COUNT; ++i)
	{
		m_Log[i] = new wchar_t[100];
		Tstrcpy(m_Log[i], _T("") );
	}
	memset(&m_Desc, 0, sizeof(D3DXFONT_DESC)); //구조체 초기화
	
	m_Desc.CharSet = HANGUL_CHARSET;
	Tstrcpy(m_Desc.FaceName, _T("궁서체") ); //폰트 설정
	m_Desc.Height = 15; //높이
	m_Desc.Width = 8; //넓이
	m_Desc.Weight = FW_BOLD; //두께
	m_Desc.Quality = ANTIALIASED_QUALITY; //품질
	m_Desc.MipLevels = 1;
	m_Desc.Italic = 0; //이텔릭
	m_Desc.OutputPrecision = OUT_DEFAULT_PRECIS;
	m_Desc.PitchAndFamily = FF_DONTCARE;

	D3DXCreateFontIndirect(_SINGLE(CDevice)->GetDevice(), &m_Desc, &m_pFont); 
	SetRect(&m_FontRect,SCREEN_WIDTH-200,10,SCREEN_WIDTH-30,SCREEN_HEIGHT); //폰트 위치
	SetRect(&m_LogRect,10,10,200,SCREEN_HEIGHT); 

	AddLog( _T("로그를 남길수 있슴..") );

}

void CTString::CleanUp()
{
	Safe_Release(m_pFont); // com객체 자원해제
	for(int i = 0; i < LOG_COUNT; ++i)
		delete[] m_Log[i] ;
		//Safe_Delete_Array(m_Log[i]);
	Safe_Delete_Array(m_Log);
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
	UINT length = _tcslen(source) ;
	if (length < _tcslen(dest) )
	{
		_tcscpy_s(dest, 255,source);
		return S_OK;
	}
	
	return E_FAIL;
}

HRESULT	CTString::Tstrcat(LPTSTR dest, LPTSTR source)
{
	_tcscat_s( dest, 256 ,source);
	return S_OK;
}

HRESULT CTString::DrawFont(LPTSTR str )
{
	
	m_pFont->DrawText(NULL, str, -1, &m_FontRect, DT_RIGHT | DT_EXPANDTABS | DT_WORDBREAK , COLOR_CYAN); //출력
	return S_OK;
}

HRESULT CTString::DrawLog()
{
	for(int i = 0; i < LOG_COUNT; ++i)
	{
		m_pFont->DrawText(NULL, m_Log[i], -1, &m_LogRect, DT_LEFT | DT_EXPANDTABS | DT_WORDBREAK, COLOR_GOLD); //출력
		m_FontRect.top += m_Desc.Height + 5;
	}
	m_FontRect.top  = 10;
	return S_OK;
}

HRESULT CTString::AddLog(LPTSTR _log)
{
	if ( m_LogCount < LOG_COUNT )
	{
		Tstrcat(m_Log[m_LogCount++], _log);
		return S_OK;
	}
	m_LogCount = 0;
	Tstrcpy(m_Log[m_LogCount++], _log);
	return E_FAIL;
}