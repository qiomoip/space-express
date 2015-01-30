#pragma once

#include "Singleton.h"


class CDevice : public CSingleton<CDevice>
{
	friend CSingleton;

private:
	LPDIRECT3D9			m_pD3D;
	LPDIRECT3DDEVICE9	m_pd3dDevice;
	LPD3DXLINE			m_pLine;

	//D3D ��Ʈ ����
	LPD3DXFONT		m_pFont;
	D3DXFONT_DESC	m_Desc;
	RECT			m_FontRect;
	RECT			m_LogRect;

	CTString**		m_Log;
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

	//�Ｎ���� ��� �޼���
	HRESULT			DrawFont(LPTSTR str );
	//�׻� ȭ�鿡 ��� �޼���
	HRESULT			DrawLog();
	//�α� �߰�
	HRESULT			AddLog(LPTSTR _log);
	HRESULT			AddLog(int _idx, LPTSTR _log);
	
	
private:
	CDevice(void);
	~CDevice(void);
};
