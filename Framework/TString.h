#pragma once
#include "Singleton.h"
/*
DirectX�� ���ڿ� Ŭ����
*/
class CTString : public CSingleton<CTString>
{
	friend CSingleton;

public:
	LPTSTR			CharToTCHAR(LPSTR szStr);	//TCHAR�� char ���·�
	LPSTR			TCHARToChar(LPTSTR szStr);	//char�� TCHAR ���·�
	
	HRESULT			Tstrcpy(LPTSTR dest, LPTSTR source);
	HRESULT			Tstrcat(LPTSTR dest, LPTSTR source);
	//�Ｎ���� ��� �޼���
	HRESULT			DrawFont(LPTSTR str );
	//�׻� ȭ�鿡 ��� �޼���
	HRESULT			DrawLog();

	HRESULT			AddLog(LPTSTR _log);

private:

	//D3D ��Ʈ ����
	LPD3DXFONT		m_pFont;
	D3DXFONT_DESC	m_Desc;
	RECT			m_FontRect;
	RECT			m_LogRect;
	//�α�
	LPTSTR*			m_Log;
	int				m_LogCount;


	void			Init();
	void			CleanUp();
	CTString(void);
	~CTString(void);
};


//_stprintf_s(std, _T("std %d"), 123);
