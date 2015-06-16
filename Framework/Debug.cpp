#include "Debug.h"
#include "Device.h"
#include "TerrainMesh.h"
#include "CameraManager.h"
#include "Camera.h"
#include "KeyManager.h"
#include "ResourceManager.h"
#include "ObjectManager.h"
#include "Frustum.h"
#include "ShaderManager.h"
#include "Shader.h"
#pragma comment(lib, "winmm.lib")

CDebug::CDebug(void)
	: m_pDevice(NULL)
	, m_pGridVB(NULL)
	, m_pTerrain(NULL)
	, m_iCnt(0)
	, m_pLineVB(NULL)
	, m_pFont(NULL)
	, m_Log(NULL)
	, m_StaticLog(NULL)
	, m_LogCount(0)
	, m_StaticLogCount(0)
	, m_FaceCount(0)
	, m_FPS(0)
	, m_CurrentTime(0)
	, m_PreviousTime(0)
	, m_DeltaTime(0)
	, m_ElapsedTime(0)
	, m_FrameCnt(0)
	, m_bWireFrame(false)
	, m_LineCount(0)
	, m_PosMarkSize(10.f)
	, m_Text3dCount(0)
{
	memset(&m_Line, 0, sizeof(LPD3DXLINE));
	memset(&m_ColorList, 0, sizeof(m_ColorList[0])* LOG_COUNT);
	memset(&m_tGridMaterial, 0, sizeof(D3DMATERIAL9));
	memset(m_vList, 0, sizeof(D3DXVECTOR3) * LOG_COUNT * 2);
	memset(&m_Desc, 0, sizeof(D3DXFONT_DESC));
	memset(&m_LogRect, 0, sizeof(RECT));
	memset(&m_StaticLogRect, 0, sizeof(RECT));
	memset(&m_Text3D, 0, sizeof(LPD3DXMESH) * LOG_COUNT);
	memset(&m_Text3dPos, 0, sizeof(D3DXVECTOR3) * LOG_COUNT);
	memset(&m_TextMat, 0, sizeof(D3DXMATRIXA16));
	memset(&m_TextMove, 0, sizeof(D3DXMATRIXA16));
	memset(&m_TextRot, 0, sizeof(D3DXMATRIXA16));
	memset(&m_TextScale, 0, sizeof(D3DXMATRIXA16));

	D3DXMatrixRotationX( &m_TextRot, D3DX_PI * 0.5f );
	float scale = 1.7f;
	D3DXMatrixScaling( &m_TextScale, scale, scale, scale);

	memset(&m_FontDefine, 0, sizeof(LOGFONT) );
	memset(&m_hdc, 0, sizeof(HDC) );
	m_hdc = CreateCompatibleDC(0);

	memset(&m_TextMaterial, 0, sizeof(D3DMATERIAL9) );

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

	m_PreviousTime = m_CurrentTime = GetTickCount() * 0.001;
	//CreateVertexBuffer();

	//memset(&m_tGridMaterial, 0, sizeof(D3DMATERIAL9));
	//m_tGridMaterial.Diffuse.a = 1.f;
	//m_tGridMaterial.Diffuse.r = 1.f;
	//m_tGridMaterial.Diffuse.g = 0.8f;
	//m_tGridMaterial.Diffuse.b = 1.f;
	//m_tGridMaterial.Power = 0.2f;
	//m_tGridMaterial.Specular = m_tGridMaterial.Diffuse;
	//m_tGridMaterial.Ambient = m_tGridMaterial.Diffuse;

	//m_pTerrain = new CTerrainMesh;

	//m_pTerrain->Initialize();

	InitFont();
	InitLog();
	InitLine();

	//AddText3D( D3DXVECTOR3(10, 3, 10), _T("3D텍스트다!") );

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
	if(m_bWireFrame)
	{
		_SINGLE(CDevice)->GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}
	else
	{
		_SINGLE(CDevice)->GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}

	DrawInfo();
}


void CDebug::Destroy()
{
	Safe_Release(m_pGridVB);
	Safe_Release(m_pLineVB);

	for( int i = 0; i < LOG_COUNT; ++i)
	{
		Safe_Delete_Array(m_StaticLog[i]);
		Safe_Delete_Array(m_Log[i]);
		Safe_Release(m_Text3D[i]);
		//Safe_Delete_Array(m_vList[i]);
	}
	Safe_Delete_Array(m_StaticLog);
	Safe_Delete_Array(m_Log);
	Safe_Release(m_Line);
	Safe_Release(m_pFont); // 폰트 구조체해제

	DeleteObject(m_hFont);
	DeleteDC(m_hdc);


}

void CDebug::Input()
{
	CheckFPS();
	const KEYINFO* keyInfo = _SINGLE(CKeyManager)->GetKey( KEYNAME_WIREFRAME_TRIGGER ) ;

	if ( keyInfo->bPush ) 
	{
		m_bWireFrame = !m_bWireFrame;
	}
}


void CDebug::DrawInfo()
{
	AddStaticLog(LOG_FACE_COUNT, _T("Faces : %d"), m_FaceCount);
	//m_pTerrain->Render();
	//DrawGrid();

	DrawStaticLog();
	DrawLog();
	DrawLine();
	DrawText3D();
}



//
//void CDebug::DrawGrid()
//{
//
//	D3DXMATRIX matWorld;
//	D3DXMatrixIdentity(&matWorld);
//	m_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
//
//	const D3DXMATRIX* pMatProj = _SINGLE(CCameraManager)->GetCurCam()->GetMatProj();
//	const D3DXMATRIX* pMatView = _SINGLE(CCameraManager)->GetCurCam()->GetMatView();
//	D3DXMATRIX matWVP = (*pMatView) * (*pMatProj);
//
//	_SINGLE(CShaderManager)->BeginShader(SHADER_DEFAULT, "DefaultTech");
//
//	CShader* pShader = _SINGLE(CShaderManager)->FindShader(SHADER_DEFAULT);
//	
//	pShader->SetMatrix("g_matWVP", &matWVP);
//
//	pShader->BeginPass(PASS_NOTEXTURE);
//	
//	pShader->SetValue("g_mtrlMesh", &m_tGridMaterial, sizeof(D3DMATERIAL9));
//
//	//m_pDevice->SetRenderState(D3DRS_LIGHTING, false);
//
//	m_pDevice->SetFVF(VTXCOLORFVF);
//	m_pDevice->SetMaterial(&m_tGridMaterial);
//	m_pDevice->SetStreamSource( 0, m_pGridVB, 0, sizeof( VERTEXCOLOR ) );
//	m_pDevice->DrawPrimitive(D3DPT_LINELIST, 0, m_iCnt/2);
//
//	m_pDevice->SetStreamSource( 0, m_pLineVB, 0, sizeof(VERTEXCOLOR) );
//	m_pDevice->SetFVF(VTXCOLORFVF);
//	m_pDevice->DrawPrimitive( D3DPT_LINELIST, 0, 3 );
//
//	pShader->EndPass();
//
//	_SINGLE(CShaderManager)->EndShader(SHADER_DEFAULT);
//}


VOID CDebug::InitLog()
{

	m_StaticLog = new LPTSTR[LOG_COUNT];
	m_Log = new LPTSTR[LOG_COUNT];
	for(int i = 0; i < LOG_COUNT; ++i)
	{
		m_Log[i]		= new TCHAR[255];
		m_StaticLog[i] = new TCHAR[255];
		_tcscpy_s(m_Log[i], 255,  _T("") );
		_tcscpy_s(m_StaticLog[i], 255,  _T("") );

	}
}

VOID CDebug::InitFont()
{
	memset(&m_Desc, 0, sizeof(D3DXFONT_DESC)); //구조체 초기화

	m_Desc.CharSet = HANGUL_CHARSET;
	_tcscpy_s(m_Desc.FaceName, _tcslen(_T("맑은 고딕")) + 1 , _T("맑은 고딕") ); //폰트 설정
	m_Desc.Height = 16; //높이
	m_Desc.Width = 7; //넓이
	m_Desc.Weight = FW_MEDIUM; //두께
	m_Desc.Quality = ANTIALIASED_QUALITY; //품질
	m_Desc.MipLevels = 1;
	m_Desc.Italic = 0; //이텔릭
	m_Desc.OutputPrecision = OUT_DEFAULT_PRECIS;
	m_Desc.PitchAndFamily = FF_DONTCARE;

	D3DXCreateFontIndirect(_SINGLE(CDevice)->GetDevice(), &m_Desc, &m_pFont); 
	SetRect(&m_StaticLogRect,SCREEN_WIDTH-400,10,SCREEN_WIDTH-30,SCREEN_HEIGHT); //폰트 위치
	SetRect(&m_LogRect,10,10,400,SCREEN_HEIGHT); 


	//3D폰트 설정
	m_FontDefine.lfHeight = 50;
	m_FontDefine.lfWidth = 24;
	//굵기 0~1000(두꺼움)
	m_FontDefine.lfWeight = 100;
	m_FontDefine.lfItalic = false;
	m_FontDefine.lfUnderline = false;
	m_FontDefine.lfStrikeOut = false;
	m_FontDefine.lfCharSet = DEFAULT_CHARSET;
	_tcscpy_s(m_FontDefine.lfFaceName, _T("맑은 고딕") );
	m_hFont = CreateFontIndirect(&m_FontDefine);

	m_TextMaterial.Diffuse.a = 1.f;
	m_TextMaterial.Diffuse.r = 0.3f;
	m_TextMaterial.Diffuse.g = 0.8;
	m_TextMaterial.Diffuse.b = 0.6f;
	m_TextMaterial.Power = 0.2f;
	m_TextMaterial.Specular = m_TextMaterial.Diffuse;
	m_TextMaterial.Ambient = m_TextMaterial.Diffuse;

}

void CDebug::InitLine()
{
	D3DXCreateLine(m_pDevice, &m_Line);
	m_Line->SetWidth(1.5f);
	//두개(시작,끝)의 벡터를 갖는 라인 배열
	//m_vList = new D3DXVECTOR3*[LOG_COUNT];
	//m_ColorList = new D3DXCOLOR[LOG_COUNT];
	//memset(&m_ColorList, 0, sizeof(m_ColorList[0]) * LOG_COUNT );
	////memset(&m_vList, 0, sizeof(m_vList[0])* LOG_COUNT );

	//for( int i = 0; i < LOG_COUNT; ++i)
	//{
	//	m_vList[i] = new D3DXVECTOR3[2];
	//	
	//	//memset(&m_vList, 0, sizeof(m_vList[0]) * LOG_COUNT * 2 );
	//}
}



HRESULT CDebug::DrawStaticLog()
{
	//m_pFont->DrawText(NULL, m_StaticLog, -1, &m_FontRect, DT_RIGHT | DT_EXPANDTABS | DT_WORDBREAK , COLOR_CYAN); //출력
	for(int i = 0; i < LOG_COUNT; ++i)
	{
		m_pFont->DrawText(NULL, m_StaticLog[i], -1, &m_StaticLogRect, DT_RIGHT | DT_EXPANDTABS | DT_WORDBREAK , COLOR_CYAN); //출력
		m_StaticLogRect.top += m_Desc.Height + 5;
	}
	m_StaticLogRect.top  = 10;
	return S_OK;
}

HRESULT CDebug::DrawLog()
{
	for(int i = 0; i < LOG_COUNT; ++i)
	{
		m_pFont->DrawText(NULL, m_Log[i], -1, &m_LogRect, DT_LEFT | DT_EXPANDTABS | DT_WORDBREAK, COLOR_BLUE); //출력
		m_LogRect.top += m_Desc.Height + 5;
	}
	m_LogRect.top  = 10;
	return S_OK;
}

HRESULT	CDebug::DrawText3D()
{
	m_pDevice->BeginScene();
	for(int i = 0; i < m_Text3dCount; ++i)
	{
		if(!_SINGLE(CFrustum)->isInFrustum( m_Text3dPos[i], 3.f) )
			continue;
		D3DXMatrixTranslation( &m_TextMove, 
			m_Text3dPos[i].x, m_Text3dPos[i].y + 3.0f, m_Text3dPos[i].z +3.0f);
		m_TextMat = m_TextScale * m_TextRot * m_TextMove;
		m_pDevice->SetMaterial( &m_TextMaterial);
		m_pDevice->SetTransform(D3DTS_WORLD, &m_TextMat);
		m_Text3D[i]->DrawSubset(0);
	}
	m_pDevice->EndScene();

	//ResetText3D();

	return S_OK;
}


void CDebug::DrawLine()
{
	D3DXMATRIXA16 mat = _SINGLE(CCameraManager)->GetCurCam()->GetMatViewProj();
	//D3DXMatrixIdentity( &mat);

	m_Line->Begin();
	for(int i = 0; i < m_LineCount; ++i)
		m_Line->DrawTransform(m_vList[i],2, &mat,  m_ColorList[i]);

	m_Line->End();

}




HRESULT CDebug::AddLog(int idx, LPTSTR _log, ...)
{
	va_list ap;
	va_start(ap, _log);
	//로그 카운트가 맥스일 경우+0보다 작은 인덱스일 경우 마지막 로그의
	//아래쪽에 로그를 기록
	if(  idx  < 0 || idx >= LOG_COUNT)
	{
		if ( m_LogCount >= LOG_COUNT )
			m_LogCount = 0;
		_vstprintf( m_Log[m_LogCount++] , 255, _log, ap);
	}
	else

		_vstprintf( m_Log[idx] , 255, _log, ap);

	return S_OK;
}

HRESULT CDebug::AddStaticLog(int idx, LPTSTR _log, ...)
{
	va_list ap;
	va_start(ap, _log);

	if ( idx >= LOG_COUNT ||  idx < 0)
	{
		//로그수가 최대라면 맨위에 로그부터 덮어 씌운다.
		if ( m_StaticLogCount >= LOG_COUNT )
			m_StaticLogCount = 0;
		_vstprintf( m_StaticLog[m_StaticLogCount++], 255, _log, ap);
	}
	else
		//아닐 경우 그냥 넘겨받은 로그 카운트에 넣는다
		_vstprintf( m_StaticLog[idx], 255, _log, ap);
	return S_OK;
}

HRESULT CDebug::AddText3D( int _no, D3DXVECTOR3 _pos, LPTSTR _str)
{
	HFONT hFontOld;
	hFontOld = (HFONT)SelectObject(m_hdc, m_hFont);

	if( _no >= LOG_COUNT  || _no < 0 )
	{
		if( m_Text3dCount >= LOG_COUNT ) 
			m_Text3dCount = 0;
		_no = m_Text3dCount ;
	}

	m_Text3dPos[_no] = _pos;
	if (D3DXCreateText( m_pDevice, 
		m_hdc,
		_str,
		0.5f,
		0.4f,
		&m_Text3D[_no++],
		NULL,
		NULL)  != D3D_OK)
		assert(false);


	m_Text3dCount = _no;

	SelectObject(m_hdc, hFontOld);
	return S_OK;
}


HRESULT CDebug::VectorToString(LPTSTR dest, D3DXVECTOR3 vec)
{
	TCHAR _vec[255] = _T("");
	_stprintf(_vec, _T("(%.2f, %.2f, %.2f)"), vec.x, vec.y, vec.z );
	_tcscpy(dest, _vec);

	return S_OK;
}

void CDebug::AddLine(D3DXVECTOR3 vStart, D3DXVECTOR3 vEnd, D3DCOLOR _color)
{
	m_vList[m_LineCount][0] = vStart;
	m_vList[m_LineCount][1] = vEnd;
	m_ColorList[m_LineCount] = _color;

	m_LineCount > LOG_COUNT ? m_LineCount = 0 : m_LineCount++;
}

void CDebug::AddPosMark( D3DXVECTOR3 _pos, D3DCOLOR _color)
{
	D3DXVECTOR3 axisX = D3DXVECTOR3(m_PosMarkSize, 0, 0);
	D3DXVECTOR3 axisZ = D3DXVECTOR3(0, 0, m_PosMarkSize);
	//충돌지점 표시
	AddLine( _pos + axisX, _pos - axisX, _color);
	AddLine( _pos + axisZ, _pos - axisZ, _color);
}




void CDebug::InitFaceCount()
{
	m_FaceCount = 0;
}

void CDebug::AddFaceCount(UINT _faces)
{
	m_FaceCount += _faces;
}


void CDebug::CheckFPS()
{
	m_CurrentTime = timeGetTime() * 0.001;
	m_DeltaTime = (m_CurrentTime - m_PreviousTime);
	m_ElapsedTime += m_DeltaTime;
	m_PreviousTime = m_CurrentTime;
	m_FrameCnt++;

	if(m_ElapsedTime >= 1.0)
	{
		m_FPS = (UINT)(m_FrameCnt / m_ElapsedTime);
		AddStaticLog(LOG_FPS, _T("FPS : %d"), m_FPS );
		m_ElapsedTime = 0.0;
		m_FrameCnt = 0.f;
	}
}

double CDebug::GetDeltaTime()
{
	return m_DeltaTime;
}


void CDebug::ResetLine()
{
	memset(&m_vList, 0, sizeof(m_vList[0]) * LOG_COUNT);
	memset(&m_ColorList, 0, sizeof(m_ColorList[0]) * LOG_COUNT);
}

void CDebug::ResetText3D()
{
	memset(&m_Text3D, 0, sizeof(LPD3DXMESH) * LOG_COUNT);
	memset(&m_Text3dPos, 0, sizeof(D3DXVECTOR3) * LOG_COUNT);
	m_Text3dCount = 0;
}
