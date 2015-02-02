#pragma once

#include "Singleton.h"


class CDevice : public CSingleton<CDevice>
{
	friend CSingleton;

private:
	LPDIRECT3D9			m_pD3D;
	LPDIRECT3DDEVICE9	m_pd3dDevice;
	LPD3DXLINE			m_pLine;

	//D3D 폰트 변수
	LPD3DXFONT		m_pFont;
	D3DXFONT_DESC	m_Desc;
	RECT			m_FontRect;
	RECT			m_LogRect;

	CTString**		m_Log;
	CTString*		m_StaticLog;
	int				m_LogCount;

//getter
public:
	LPDIRECT3DDEVICE9	GetDevice() const;
	LPD3DXLINE			GetLine() const;

public:
	HRESULT Initialize(HWND hWnd);

public:
	HRESULT				CreateDevice( HWND hWnd );

	VOID				LoadData();
	VOID				LoadLevel(int _level);
	VOID				Cleanup();
	VOID				InitFont();
	VOID				InitLog();

	//즉석에서 띄울 메세지
	HRESULT			DrawFont();
	//항상 화면에 듸울 메세지
	HRESULT			DrawLog();
	//로그 추가
	HRESULT			AddLog(LPTSTR _log);
	//특정 인덱스에 로그 추가
	HRESULT			AddLog(int _idx, LPTSTR _log);
	//고정된 위치(우측상단)에 로그 출력
	HRESULT			AddStaticLog(LPTSTR _log);
	
	
private:
	CDevice(void);
	~CDevice(void);
};
