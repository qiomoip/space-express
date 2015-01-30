#include "TString.h"
#include "Device.h"

CTString::CTString(void)
	: m_pFont(NULL)
	, m_LogCount(0)
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
	memset(m_Log, 0, sizeof(LPTSTR) * LOG_COUNT);

	for(int i = 0 ; i < LOG_COUNT; ++i)
	{
		m_Log[i] = new wchar_t[100];
		memset(m_Log[i], 0, sizeof(wchar_t) * 100);
	}

	memset(&m_Desc, 0, sizeof(D3DXFONT_DESC)); //����ü �ʱ�ȭ
	
	m_Desc.CharSet = HANGUL_CHARSET;
	Tstrcpy(m_Desc.FaceName, _T("���� ���") ); //��Ʈ ����
	m_Desc.Height = 15; //����
	m_Desc.Width = 8; //����
	m_Desc.Weight = FW_BOLD; //�β�
	m_Desc.Quality = ANTIALIASED_QUALITY; //ǰ��
	m_Desc.MipLevels = 1;
	m_Desc.Italic = 0; //���ڸ�
	m_Desc.OutputPrecision = OUT_DEFAULT_PRECIS;
	m_Desc.PitchAndFamily = FF_DONTCARE;

	D3DXCreateFontIndirect(_SINGLE(CDevice)->GetDevice(), &m_Desc, &m_pFont); 
	SetRect(&m_FontRect,SCREEN_WIDTH-200,10,SCREEN_WIDTH-30,SCREEN_HEIGHT); //��Ʈ ��ġ
	SetRect(&m_LogRect,10,10,400,SCREEN_HEIGHT); 

	AddLog( _T("Log0") );
	AddLog( _T("�α׸� ����� ����..1") );
	AddLog( _T("�α׸� ����� ����..2") );
	AddLog( _T("�α׸� ����� ����..3") );
	AddLog( _T("�α׸� ����� ����..4") );
	AddLog( _T("�α׸� ����� ����..5") );
	AddLog( _T("�α׸� ����� ����..6") );
	AddLog( _T("�α׸� ����� ����..7") );
	AddLog( _T("�α׸� ����� ����..8") );
	AddLog( _T("�α׸� ����� ����..9") );
	AddLog( _T("�α׸� ����� ����..10") );
	AddLog( _T("�α׸� ����� ����..11") );
	AddLog( _T("�α׸� ����� ����..12") );
	AddLog( _T("�α׸� ����� ����..13") );
	AddLog( _T("�α׸� ����� ����..14") );

	AddLog( _T("Log15") );
	AddLog( _T("�α׸� ����� ����..16") );
	AddLog( _T("�α׸� ����� ����..17") );
	AddLog( _T("�α׸� ����� ����..18") );
	AddLog( _T("�α׸� ����� ����..19") );
	AddLog( _T("�α׸� ����� ����..20") );
	AddLog( _T("�α׸� ����� ����..21") );
	AddLog( _T("�α׸� ����� ����..22") );
	AddLog( _T("�α׸� ����� ����..23") );
	AddLog( _T("�α׸� ����� ����..24") );
	AddLog( _T("�α׸� ����� ����..25") );
	AddLog( _T("�α׸� ����� ����..26") );
	AddLog( _T("�α׸� ����� ����..27") );
	AddLog( _T("�α׸� ����� ����..28") );
	AddLog( _T("�α׸� ����� ����..29") );

	AddLog( _T("�α׸� ����� ����..30") );
	AddLog( _T("�α׸� ����� ����..31") );
	AddLog( _T("�α׸� ����� ����..32") );
	AddLog( _T("�α׸� ����� ����..33") );
	AddLog( _T("�α׸� ����� ����..34") );

	Tstrcat(m_Log[0], _T(" �� �� �� "));

}

void CTString::CleanUp()
{
	for(int i = 0; i < LOG_COUNT; ++i)
	{
		Safe_Delete_Array(m_Log[i]);
	}
	Safe_Delete_Array(m_Log);
	Safe_Release(m_pFont); // com��ü �ڿ�����
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
	_tcscpy(dest, source);
	return S_OK;
}

HRESULT	CTString::Tstrcat(LPTSTR dest, LPTSTR source)
{
	_tcscat_s( dest, _tcslen(dest) + _tcslen(source) + 2, source);
	return S_OK;
}

HRESULT CTString::DrawFont(LPTSTR str )
{
	
	m_pFont->DrawText(NULL, str, -1, &m_FontRect, DT_RIGHT | DT_EXPANDTABS | DT_WORDBREAK , COLOR_CYAN); //���
	return S_OK;
}

HRESULT CTString::DrawLog()
{
	for(int i = 0; i < LOG_COUNT; ++i)
	{
		m_pFont->DrawText(NULL, m_Log[i], -1, &m_LogRect, DT_LEFT | DT_EXPANDTABS | DT_WORDBREAK, COLOR_GOLD); //���
		m_LogRect.top += m_Desc.Height + 5;
	}
	m_LogRect.top  = 10;
	return S_OK;
}

HRESULT CTString::AddLog(LPTSTR _log)
{
	//�α� ī��Ʈ�� �ƽ��� ��� ���� �����
	if( m_LogCount >= LOG_COUNT )
	{
		//0������ ���
		memset(m_Log[0], 0, sizeof(wchar_t) * 100);
		Tstrcpy(m_Log[0], _log);
		m_LogCount = 1;
	}
	else
	{
		//�ƴ� ��� �׳� �α� ī��Ʈ�� �ִ´�
		Tstrcpy(m_Log[m_LogCount++], _log);
		//++m_LogCount;
	}

	return S_OK;
}