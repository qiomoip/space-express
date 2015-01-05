#pragma once

#include <d3d9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 )
#include "Singleton.h"

class CDevice : public Singleton<CDevice>
{
	friend Singleton;

private:
	CDevice(void);
	~CDevice(void);

	LPDIRECT3D9			m_pD3D;
	LPDIRECT3DDEVICE9	m_pd3dDevice;

	LPCWSTR				m_Name;
	
public:
	
	VOID				SetProjectName(LPCWSTR _name);

	HRESULT				InitD3D( HWND hWnd );
	
	VOID				LoadData();
	VOID				LoadLevel(int _level);
	VOID				Cleanup();
	//VOID				Logic();
	VOID				Input();
	VOID				Render();
};


#define GetDevice() CDevice::GetInstance()
#define _SINGLETON(T) T::GetInstance() 