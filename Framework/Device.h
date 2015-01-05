#pragma once

#include "define.h"
#include "Singleton.h"

class CDevice : public CSingleton<CDevice>
{
	friend CSingleton;

private:
	LPDIRECT3D9			m_pD3D;
	LPDIRECT3DDEVICE9	m_pd3dDevice;

//getter
public:
	LPDIRECT3DDEVICE9	GetDevice() const;

public:
	HRESULT Initialize(HWND hWnd);

public:
	HRESULT				CreateDevice( HWND hWnd );

	VOID				LoadData();
	VOID				LoadLevel(int _level);
	VOID				Cleanup();
	
private:
	CDevice(void);
	~CDevice(void);
};