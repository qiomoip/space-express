#include "Debug.h"
#include "Device.h"
#include "TerrainMesh.h"
#include "CameraManager.h"
#include "Camera.h"
#include "KeyManager.h"
#include "ResourceManager.h"
#include "ObjectManager.h"
#include "TString.h"


CDebug::CDebug(void)
	: m_pGridVB(NULL)
	, m_pTerrain(NULL)
	, m_pDevice(NULL)
	, m_iCnt(0)
	, m_pLineVB(NULL)
	, m_pFont(NULL)
	, m_Desc()
	, m_FontRect()
	, m_LogRect()
	, m_Log(NULL)
	, m_StaticLog(NULL)
	, m_LogCount(0)
{
}


CDebug::~CDebug(void)
{
	Destroy();
}

void CDebug::Initialize()
{
	m_pDevice = _SINGLE(CDevice)->GetDevice();
	if(!m_pDevice)
		return;
	CreateVertexBuffer();

	memset(&m_tGridMaterial, 0, sizeof(D3DMATERIAL9));
	m_tGridMaterial.Diffuse.a = 1.f;
	m_tGridMaterial.Diffuse.r = 1.f;
	m_tGridMaterial.Diffuse.g = 0.8f;
	m_tGridMaterial.Diffuse.b = 1.f;
	m_tGridMaterial.Power = 0.2f;
	m_tGridMaterial.Specular = m_tGridMaterial.Diffuse;
	m_tGridMaterial.Ambient = m_tGridMaterial.Diffuse;
	
	//m_pTerrain = new CTerrainMesh;

	//m_pTerrain->Initialize();

	InitFont();
	InitLog();

	AddLog(0, _T("�׽�Ʈ �α� �Դϴ�.%d"), 0 );
	AddLog(1, _T("�׽�Ʈ �α� �Դϴ�.%d"), 1 );
	AddLog(0, _T("�α� %d ���� ��� %d"), 123 , 123 );
	AddStaticLog(true, _T("��ġ�� ������ �α�%d"), 0 );

	
}

void CDebug::CreateVertexBuffer()
{
	float x1 = -128;
	float x2 = 128;
	float y1 = -128;
	float y2 = 128;
	float stepX = 1.f;
	float stepY = 1.f;
	const DWORD gridColor = D3DCOLOR_XRGB(0, 0, 0);

	if(_SINGLE(CDevice)->GetDevice()->CreateVertexBuffer(
		128 * 128 * sizeof(VERTEXCOLOR),
		D3DUSAGE_WRITEONLY,	VTXTERRAINFVF, D3DPOOL_MANAGED, &m_pGridVB, 0))
	{
		return;
	}

	VERTEXCOLOR* tempVB = NULL;

	m_pGridVB->Lock(0, 0, (void**)&tempVB, 0);

    for ( float x = x1; x<=x2; x+= stepX )
    {
		tempVB[m_iCnt].vPos = D3DXVECTOR3(x, 0.f, y1);
        tempVB[m_iCnt].dwColor = gridColor;
        ++m_iCnt;
        tempVB[m_iCnt].vPos = D3DXVECTOR3(x, 0.f, y2);
        tempVB[m_iCnt].dwColor = gridColor;
        ++m_iCnt;
    }

	m_pGridVB->Unlock();
 
    for ( float y = y1; y<= y2; y+= stepY )
    {
        tempVB[m_iCnt].vPos = D3DXVECTOR3(x1, 0.f, y);
        tempVB[m_iCnt].dwColor = gridColor;
        ++m_iCnt;
        tempVB[m_iCnt].vPos = D3DXVECTOR3(x2, 0.f, y);
        tempVB[m_iCnt].dwColor = gridColor;
        ++m_iCnt;
    }

	if(_SINGLE(CDevice)->GetDevice()->CreateVertexBuffer(
		6 * sizeof(VERTEXCOLOR),
		D3DUSAGE_WRITEONLY,	VTXTERRAINFVF, D3DPOOL_MANAGED, &m_pLineVB, 0))
	{
		return;
	}

	//VERTEXCOLOR colorVtx[] = { {D3DXVECTOR3(-200.0f, 0.0f, 0.0f),  0xffff0000 }, // red = +x Axis
	VERTEXCOLOR colorVtx[] = { {D3DXVECTOR3(0.f, 0.0f, 0.0f),  0xffff0000 }, // red = +x Axis
	{ D3DXVECTOR3(200.0f, 0.0f, 0.0f),  0xffff0000 },
	//{ D3DXVECTOR3(0.0f, -200.0f, 0.0f),  0xff00ff00 }, // green = +y Axis
	{ D3DXVECTOR3(0.0f, 0.f, 0.0f),  0xff00ff00 }, // green = +y Axis
	{ D3DXVECTOR3(0.0f, 200.0f, 0.0f),  0xff00ff00 },
	{ D3DXVECTOR3(0.0f, 0.0f, 200.0f),  0xff0000ff }, // blue = +z Axis
	//{ D3DXVECTOR3(0.0f, 0.0f, -200.0f),  0xff0000ff }};
	{ D3DXVECTOR3(0.0f, 0.0f, 0.f),  0xff0000ff }};
	void *pVertices = NULL;

    m_pLineVB->Lock( 0, sizeof(colorVtx), (void**)&pVertices, 0 );
    memcpy( pVertices, colorVtx, sizeof(colorVtx) );
    m_pLineVB->Unlock();
}


void CDebug::Update()
{

}

void CDebug::Render()
{
	
	DrawInfo();
}


void CDebug::Destroy()
{
	Safe_Release(m_pGridVB);
	Safe_Release(m_pLineVB);

	Safe_Delete(m_StaticLog);
	for( int i = 0; i < LOG_COUNT; ++i)
		Safe_Delete(m_Log[i]);
	Safe_Delete_Array(m_Log);
	Safe_Release(m_pFont); // ��Ʈ ����ü����
}

void CDebug::Input()
{
}


void CDebug::DrawInfo()
{
	//m_pTerrain->Render();
	DrawGrid();

	DrawFont();
	DrawLog();
}

void CDebug::DrawGrid()
{
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);

	m_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	

	//m_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	m_pDevice->SetFVF(VTXCOLORFVF);
	m_pDevice->SetMaterial(&m_tGridMaterial);
	m_pDevice->SetStreamSource( 0, m_pGridVB, 0, sizeof( VERTEXCOLOR ) );
	m_pDevice->DrawPrimitive(D3DPT_LINELIST, 0, m_iCnt/2);

	m_pDevice->SetStreamSource( 0, m_pLineVB, 0, sizeof(VERTEXCOLOR) );
	m_pDevice->SetFVF(VTXCOLORFVF);
	m_pDevice->DrawPrimitive( D3DPT_LINELIST, 0, 3 );

	//m_pDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
}


VOID CDebug::InitLog()
{
	m_StaticLog = new TCHAR[255];
	memset(m_StaticLog, 0, sizeof(TCHAR)* 255 );
	m_Log = new LPTSTR[LOG_COUNT];
	for(int i = 0; i < LOG_COUNT; ++i)
	{
		m_Log[i] = new TCHAR[255];
		memset(m_Log[i], 0, sizeof(TCHAR) * 255);
	}
}

VOID CDebug::InitFont()
{
	memset(&m_Desc, 0, sizeof(D3DXFONT_DESC)); //����ü �ʱ�ȭ
	
	m_Desc.CharSet = HANGUL_CHARSET;
	_tcscpy_s(m_Desc.FaceName, _tcslen(_T("���� ���")) + 1 , _T("���� ���") ); //��Ʈ ����
	m_Desc.Height = 15; //����
	m_Desc.Width = 8; //����
	m_Desc.Weight = FW_BOLD; //�β�
	m_Desc.Quality = ANTIALIASED_QUALITY; //ǰ��
	m_Desc.MipLevels = 1;
	m_Desc.Italic = 0; //���ڸ�
	m_Desc.OutputPrecision = OUT_DEFAULT_PRECIS;
	m_Desc.PitchAndFamily = FF_DONTCARE;

	D3DXCreateFontIndirect(_SINGLE(CDevice)->GetDevice(), &m_Desc, &m_pFont); 
	SetRect(&m_FontRect,SCREEN_WIDTH-400,10,SCREEN_WIDTH-30,SCREEN_HEIGHT); //��Ʈ ��ġ
	SetRect(&m_LogRect,10,10,400,SCREEN_HEIGHT); 
}

HRESULT CDebug::DrawFont()
{
	m_pFont->DrawText(NULL, m_StaticLog, -1, &m_FontRect, DT_RIGHT | DT_EXPANDTABS | DT_WORDBREAK , COLOR_CYAN); //���
	return S_OK;
}

HRESULT CDebug::DrawLog()
{
	for(int i = 0; i < LOG_COUNT; ++i)
	{
		m_pFont->DrawText(NULL, m_Log[i], -1, &m_LogRect, DT_LEFT | DT_EXPANDTABS | DT_WORDBREAK, COLOR_GOLD); //���
		m_LogRect.top += m_Desc.Height + 5;
	}
	m_LogRect.top  = 10;
	return S_OK;
}

HRESULT CDebug::AddLog(LPTSTR _log, ...)
{
	va_list ap;
	va_start(ap, _log);
	//�α� ī��Ʈ�� �ƽ��� ��� ���� �����
	if( m_LogCount >= LOG_COUNT )
	{
		_vstprintf( m_Log[0] , 255, _log, ap);
		//CTString::Tstrcpy(m_Log[0], _log);
		//m_Log[0] = _log;
		m_LogCount = 1;
	}
	else
		//�ƴ� ��� �׳� �α� ī��Ʈ�� �ִ´�
		_vstprintf( m_Log[m_LogCount++] , 255, _log, ap);
		//m_Log[m_LogCount++] = _log;
	return S_OK;
}


HRESULT CDebug::AddLog(int idx, LPTSTR _log, ...)
{
	va_list ap;
	va_start(ap, _log);
	//�α� ī��Ʈ�� �ƽ��� ��� ���� �����
	if( idx >= LOG_COUNT )
	{
		//�߸��� �ε���
		return E_FAIL;
	}
	else
		//�ƴ� ��� �׳� �α� ī��Ʈ�� �ִ´�
		_vstprintf( m_Log[idx] , 255, _log, ap);
		//m_Log[idx] = _log;

	return S_OK;
}

HRESULT CDebug::AddStaticLog(bool isOverwrite, LPTSTR _log, ...)
{
	va_list ap;
	va_start(ap, _log);

	if ( isOverwrite)
	{
		_vstprintf( m_StaticLog, 255, _log, ap);
	}
	else
	{
		LPTSTR str = new TCHAR[255];
		
		_vstprintf( str, 255, _log, ap);
		_tcscat_s(m_StaticLog,_tcslen(m_StaticLog) + _tcslen(str) + 2, str) ;

		Safe_Delete_Array(str);
	}
	return S_OK;
}

HRESULT CDebug::VectorToString(LPTSTR dest, D3DXVECTOR3 vec)
{
	LPTSTR _vec = new TCHAR[30];
	_stprintf(_vec, _T("(%.2f, %.2f, %.2f)"), vec.x, vec.y, vec.z );
	_tcscpy(dest, _vec);
	Safe_Delete_Array(_vec);

	return S_OK;
}