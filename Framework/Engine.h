#pragma once

#include "Singleton.h"

class CDevice;
class CLight;

class CEngine
	: public CSingleton<CEngine>
{
friend CSingleton;

private:
	LPCWSTR				m_Name;
	CDevice*			m_pDevice;
	vector<CLight*>		m_vecLight;
	
public:
	HRESULT CreateEntity();
	HRESULT CreateCamera();
	HRESULT CreateLight();

public:
	HRESULT				Initialize(HWND hWnd);
	VOID				Destroy();
	VOID				Update();
	VOID				Input();
	VOID				Run();
	VOID				Collision();
	VOID				Render();
private:
	CEngine(void);
	~CEngine(void);
};

