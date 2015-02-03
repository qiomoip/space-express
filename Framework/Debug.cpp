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
	//m_pTerrain = new CTerrainMesh;

	//m_pTerrain->Initialize();

	//m_pTerrain = (CTerrainMesh*)_SINGLE(CResourceManager)->LoadMesh(MT_TERRAIN, "MainTerrain");
	m_pTerrain = _SINGLE(CObjectManager)->CreateEntity(MT_TERRAIN, RTYPE_TERRAIN, "MainTerrain");

	InitFont();
	InitLog();
	AddLog(0, _T("테스트 로그 입니다.") );
	AddLog(1 ,  _T("테스트 로그 입니다.2") );
	AddLog(2, CTString::Tvprintf(_T("로그 %d 변수 출력 %d"), 123 , 123).get() );
	AddStaticLog( _T("위치가 고정된 로그"), false );

	
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
	Safe_Release(m_pFont); // 폰트 구조체해제
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
	

	m_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	m_pDevice->SetFVF(VTXCOLORFVF);
	m_pDevice->SetStreamSource( 0, m_pGridVB, 0, sizeof( VERTEXCOLOR ) );
	m_pDevice->DrawPrimitive(D3DPT_LINELIST, 0, m_iCnt/2);

	m_pDevice->SetStreamSource( 0, m_pLineVB, 0, sizeof(VERTEXCOLOR) );
	m_pDevice->SetFVF(VTXCOLORFVF);
	m_pDevice->DrawPrimitive( D3DPT_LINELIST, 0, 3 );

	m_pDevice->SetRenderState( D3DRS_LIGHTING, TRUE );
}


VOID CDebug::InitLog()
{
	m_StaticLog = new CTString();
	m_Log = new CTString*[LOG_COUNT];
	for(int i = 0; i < LOG_COUNT; ++i)
		m_Log[i] = new CTString();

}

VOID CDebug::InitFont()
{
	memset(&m_Desc, 0, sizeof(D3DXFONT_DESC)); //구조체 초기화
	
	m_Desc.CharSet = HANGUL_CHARSET;
	CTString::Tstrcpy(m_Desc.FaceName, _T("맑은 고딕") ); //폰트 설정
	m_Desc.Height = 15; //높이
	m_Desc.Width = 8; //넓이
	m_Desc.Weight = FW_BOLD; //두께
	m_Desc.Quality = ANTIALIASED_QUALITY; //품질
	m_Desc.MipLevels = 1;
	m_Desc.Italic = 0; //이텔릭
	m_Desc.OutputPrecision = OUT_DEFAULT_PRECIS;
	m_Desc.PitchAndFamily = FF_DONTCARE;

	D3DXCreateFontIndirect(_SINGLE(CDevice)->GetDevice(), &m_Desc, &m_pFont); 
	SetRect(&m_FontRect,SCREEN_WIDTH-400,10,SCREEN_WIDTH-30,SCREEN_HEIGHT); //폰트 위치
	SetRect(&m_LogRect,10,10,400,SCREEN_HEIGHT); 
}

HRESULT CDebug::DrawFont()
{
	m_pFont->DrawText(NULL, m_StaticLog->GetStr().get(), -1, &m_FontRect, DT_RIGHT | DT_EXPANDTABS | DT_WORDBREAK , COLOR_CYAN); //출력
	return S_OK;
}

HRESULT CDebug::DrawLog()
{
	for(int i = 0; i < LOG_COUNT; ++i)
	{
		m_pFont->DrawText(NULL, m_Log[i]->GetStr().get(), -1, &m_LogRect, DT_LEFT | DT_EXPANDTABS | DT_WORDBREAK, COLOR_GOLD); //출력
		m_LogRect.top += m_Desc.Height + 5;
	}
	m_LogRect.top  = 10;
	return S_OK;
}

HRESULT CDebug::AddLog(LPTSTR _log)
{
	//로그 카운트가 맥스일 경우 위에 덮어쓴다
	if( m_LogCount >= LOG_COUNT )
	{
		CTString::Tstrcpy(m_Log[0]->GetStr().get(), _log);
		*m_Log[0] = _log;
		m_LogCount = 1;
	}
	else
		//아닐 경우 그냥 로그 카운트에 넣는다
		*m_Log[m_LogCount++] = _log;
	return S_OK;
}


HRESULT CDebug::AddLog(int idx, LPTSTR _log)
{
	//로그 카운트가 맥스일 경우 위에 덮어쓴다
	if( idx >= LOG_COUNT )
	{
		//잘못된 인덱스
		return E_FAIL;
	}
	else
		//아닐 경우 그냥 로그 카운트에 넣는다
		*m_Log[idx] = _log;

	return S_OK;
}

HRESULT CDebug::AddStaticLog(LPTSTR _log, bool isOverwrite)
{
	if ( isOverwrite)
		*m_StaticLog = _log;
	else
		*m_StaticLog += _log;
	return S_OK;
}