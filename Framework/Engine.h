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
	LPDIRECT3DVERTEXBUFFER9		m_pVB;

public:
	HRESULT				Initialize(HWND hWnd);
	VOID				Destroy();
	VOID				Update();
	VOID				Input();
	VOID				Render();
private:
	CEngine(void);
	~CEngine(void);

//Debug
public:
#ifdef _DEBUG
	void CreateVertexBuffer();
	void DrawInfo();
	void DrawGrid();
#endif
};

