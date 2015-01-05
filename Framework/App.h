#pragma once
#include "define.h"

class CApp
{
private:
	HWND		m_hWnd;
	HINSTANCE	m_hInst;

public:
	HRESULT Initialize(HINSTANCE hInst);
	VOID Run();

public:
	ATOM RegisterWindow();
	void CreateWnd();

public:
	static LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );


public:
	CApp(void);
	~CApp(void);
};

