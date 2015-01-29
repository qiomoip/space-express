#pragma once
#include "define.h"

class CApp
{
private:
	HWND		m_hWnd;
	HINSTANCE	m_hInst;
	LPCTSTR		m_lpClassName;

public:
	HRESULT Initialize(HINSTANCE hInst, LPCTSTR lpClassName, LPCTSTR lpCWindowName,int iWidth, int iHeight);
	VOID Run();
	void Destroy();

public:
	ATOM RegisterWindow();
	void CreateWnd(LPCTSTR lpCWindowName, int iWidth, int iHeight);

public:
	static LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

public:
	CApp(void);
	~CApp(void);
};

