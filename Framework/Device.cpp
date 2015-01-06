#include "Device.h"
#include "CameraManager.h"

CDevice::CDevice(void)
{
}

CDevice::~CDevice(void)
{
}



HRESULT CDevice::CreateDevice(HWND hWnd)
{
	// Create the D3D object, which is needed to create the D3DDevice.
    if( NULL == ( m_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        return E_FAIL;

    // Set up the structure used to create the D3DDevice. Most parameters are
    // zeroed out. We set Windowed to TRUE, since we want to do D3D in a
    // window, and then set the SwapEffect to "discard", which is the most
    // efficient method of presenting the back buffer to the display.  And 
    // we request a back buffer format that matches the current desktop display 
    // format.
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof( d3dpp ) );
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

    // Create the Direct3D device. Here we are using the default adapter (most
    // systems only have one, unless they have multiple graphics hardware cards
    // installed) and requesting the HAL (which is saying we want the hardware
    // device rather than a software one). Software vertex processing is 
    // specified since we know it will work on all cards. On cards that support 
    // hardware vertex processing, though, we would see a big performance gain 
    // by specifying hardware vertex processing.
    if( FAILED( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &m_pd3dDevice ) ) )
    {
        return E_FAIL;
    }

    // Device state would normally be set here
	_SINGLE(CCameraManager)->AddCamera( "MainCamera");
    return S_OK;
}

VOID CDevice::Cleanup()
{
	if( m_pd3dDevice != NULL )
        m_pd3dDevice->Release();

    if( m_pD3D != NULL )
        m_pD3D->Release();
}

LPDIRECT3DDEVICE9 CDevice::GetDevice() const
{
	return m_pd3dDevice;
}

HRESULT CDevice::Initialize(HWND hWnd)
{
	HRESULT hr = CreateDevice(hWnd);

	return hr;
}