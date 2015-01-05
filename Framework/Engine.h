#pragma once
#include "define.h"
#include "Singleton.h"

class CDevice;

class CEngine
	: public CSingleton<CEngine>
{
friend CSingleton;

private:
	LPCWSTR				m_Name;
	CDevice*			m_pDevice;

public:
	HRESULT				Initialize(HWND hWnd);
	VOID				Destroy();
	VOID				SetProjectName(LPCWSTR _name);
	VOID				Update();
	VOID				Input();
	VOID				Render();
private:
	CEngine(void);
	~CEngine(void);
};

