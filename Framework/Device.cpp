#include "Device.h"
#include "TString.h"

CDevice::CDevice(void)
	: m_pD3D(NULL)
	, m_pd3dDevice(NULL)
	, m_pLine(NULL)
	, m_pFont(NULL)
	, m_Desc()
	, m_FontRect()
	, m_LogRect()
	, m_Log(NULL)
	, m_LogCount(0)
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

	//Create Line
	if(FAILED(D3DXCreateLine(m_pd3dDevice, &m_pLine)))
	{
		return E_FAIL;
	}

    return S_OK;
}

VOID CDevice::Cleanup()
{
	for( int i = 0; i < LOG_COUNT; ++i)
		Safe_Delete(m_Log[i]);
	Safe_Delete_Array(m_Log);

	Safe_Release(m_pFont); // ��Ʈ ����ü����

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

	InitFont();
	InitLog();
	return hr;
}

VOID CDevice::InitLog()
{
	m_Log = new CTString*[LOG_COUNT];
	for(int i = 0; i < LOG_COUNT; ++i)
		m_Log[i] = new CTString();

	AddLog( _S("�α� �߰�." ) );
	
}

VOID CDevice::InitFont()
{
	memset(&m_Desc, 0, sizeof(D3DXFONT_DESC)); //����ü �ʱ�ȭ
	
	m_Desc.CharSet = HANGUL_CHARSET;
	CTString::Tstrcpy(m_Desc.FaceName, _T("���� ���") ); //��Ʈ ����
	m_Desc.Height = 15; //����
	m_Desc.Width = 8; //����
	m_Desc.Weight = FW_BOLD; //�β�
	m_Desc.Quality = ANTIALIASED_QUALITY; //ǰ��
	m_Desc.MipLevels = 1;
	m_Desc.Italic = 0; //���ڸ�
	m_Desc.OutputPrecision = OUT_DEFAULT_PRECIS;
	m_Desc.PitchAndFamily = FF_DONTCARE;

	D3DXCreateFontIndirect(_SINGLE(CDevice)->GetDevice(), &m_Desc, &m_pFont); 
	SetRect(&m_FontRect,SCREEN_WIDTH-200,10,SCREEN_WIDTH-30,SCREEN_HEIGHT); //��Ʈ ��ġ
	SetRect(&m_LogRect,10,10,400,SCREEN_HEIGHT); 
}

HRESULT CDevice::DrawFont(LPTSTR str )
{
	m_pFont->DrawText(NULL, str, -1, &m_FontRect, DT_RIGHT | DT_EXPANDTABS | DT_WORDBREAK , COLOR_CYAN); //���
	Safe_Delete_Array(str);
	return S_OK;
}

HRESULT CDevice::DrawLog()
{
	for(int i = 0; i < LOG_COUNT; ++i)
	{
		m_pFont->DrawText(NULL, m_Log[i]->GetStr(), -1, &m_LogRect, DT_LEFT | DT_EXPANDTABS | DT_WORDBREAK, COLOR_GOLD); //���
		m_LogRect.top += m_Desc.Height + 5;
	}
	m_LogRect.top  = 10;
	return S_OK;
}

HRESULT CDevice::AddLog(LPTSTR _log)
{
	//�α� ī��Ʈ�� �ƽ��� ��� ���� �����
	if( m_LogCount >= LOG_COUNT )
	{
		//0������ ���
		//memset(m_Log[0], 0, sizeof(wchar_t) * 100);
		CTString::Tstrcpy(m_Log[0]->GetStr(), _log);
		m_LogCount = 1;
	}
	else
		//�ƴ� ��� �׳� �α� ī��Ʈ�� �ִ´�
		CTString::Tstrcpy(m_Log[m_LogCount++]->GetStr(), _log);

	Safe_Delete_Array(_log);
	return S_OK;
}

HRESULT CDevice::AddLog(int idx, LPTSTR _log)
{
	//�α� ī��Ʈ�� �ƽ��� ��� ���� �����
	if( idx >= LOG_COUNT )
	{
		//�߸��� �ε���
		return E_FAIL;
	}
	else
		//�ƴ� ��� �׳� �α� ī��Ʈ�� �ִ´�
		CTString::Tstrcpy(m_Log[idx]->GetStr(), _log);

	Safe_Delete_Array(_log);
	return S_OK;
}