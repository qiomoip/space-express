#pragma once

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
	HRESULT CreateEntity();
	HRESULT CreateCamera();

public:
	HRESULT				Initialize(HWND hWnd);
	VOID				Destroy();
	VOID				Update();
	VOID				Input();
	VOID				Render();
private:
	CEngine(void);
	~CEngine(void);
};

