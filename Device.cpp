#include "Device.h"
#include "TString.h"

CDevice::CDevice(void)
	: m_pD3D(NULL)
	, m_pd3dDevice(NULL)
	, m_pLine(NULL)

{
}

CDevice::~CDevice(void)
{
	Cleanup();
}



HRESULT CDevice::CreateDevice(HWND hWnd)
{
	// Create the D3D object, which is needed to create the D3DDevice.
    if( NULL == ( m_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        return E_FAIL;


    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof( d3dpp ) );
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D24S8;
	d3dpp.FullScreen_RefreshRateInHz	= D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval		= D3DPRESENT_INTERVAL_IMMEDIATE;
	d3dpp.MultiSampleType			= D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality		= 0;
	d3dpp.BackBufferWidth	= SCREEN_WIDTH;
	d3dpp.BackBufferHeight	= SCREEN_HEIGHT;
	d3dpp.BackBufferFormat	= D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount	= 1;
	d3dpp.Flags				= 0;

    if( FAILED( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &m_pd3dDevice ) ) )
    {
        return E_FAIL;
    }

    // Device state would normally be set here

	//Create Line
	if(FAILED(D3DXCreateLine(m_pd3dDevice, &m_pLine)))
	{
		return E_FAIL;
	}

    return S_OK;
}

VOID CDevice::Cleanup()
{

	if( m_pLine != NULL)
		m_pLine->Release();

	if( m_pd3dDevice != NULL )
        m_pd3dDevice->Release();

    if( m_pD3D != NULL )
        m_pD3D->Release();
}

LPDIRECT3DDEVICE9 CDevice::GetDevice() const
{
	return m_pd3dDevice;
}

LPD3DXLINE	CDevice::GetLine() const
{
	return m_pLine;
}

HRESULT CDevice::Initialize(HWND hWnd)
{
	HRESULT hr = CreateDevice(hWnd);

	return hr;
}