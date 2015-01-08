#include "Debug.h"
#include "Device.h"
#include "TerrainMesh.h"
#include "CameraManager.h"
#include "Camera.h"
#include "KeyManager.h"


CDebug::CDebug(void)
	: m_pGridVB(NULL)
	, m_pTerrain(NULL)
	, m_pDevice(NULL)
	, m_iCnt(0)
	, m_pLineVB(NULL)
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
	m_pTerrain = new CTerrainMesh;

	m_pTerrain->Initialize();

	_SINGLE(CKeyManager)->SetKeyData(KEY_START, VK_SPACE);
}

void CDebug::CreateVertexBuffer()
{
	int x1 = -128;
	int x2 = 128;
	int y1 = -128;
	int y2 = 128;
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

	VERTEXCOLOR colorVtx[] = { {D3DXVECTOR3(-200.0f, 0.0f, 0.0f),  0xffff0000 }, // red = +x Axis
	{ D3DXVECTOR3(200.0f, 0.0f, 0.0f),  0xffff0000 },
	{ D3DXVECTOR3(0.0f, -200.0f, 0.0f),  0xff00ff00 }, // green = +y Axis
	{ D3DXVECTOR3(0.0f, 200.0f, 0.0f),  0xff00ff00 },
	{ D3DXVECTOR3(0.0f, 0.0f, 200.0f),  0xff0000ff }, // blue = +z Axis
	{ D3DXVECTOR3(0.0f, 0.0f, -200.0f),  0xff0000ff }};

	void *pVertices = NULL;

    m_pLineVB->Lock( 0, sizeof(colorVtx), (void**)&pVertices, 0 );
    memcpy( pVertices, colorVtx, sizeof(colorVtx) );
    m_pLineVB->Unlock();
}


void CDebug::Update()
{
	/*if(_SINGLE(CKeyManager)->GetKey(KEY_START)->bUp)
	{
		int a = 10;
	}
	if(_SINGLE(CKeyManager)->GetKey(KEY_START)->bPush)
	{
		int b = 10;
	}
	if(_SINGLE(CKeyManager)->GetKey(KEY_START)->bDown)
	{
		int c = 10;
	}*/
}

void CDebug::Render()
{
	DrawInfo();
}

void CDebug::DrawInfo()
{
	m_pTerrain->Render();
	DrawGrid();
}

void CDebug::DrawGrid()
{
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);

	m_pDevice->SetTransform(D3DTS_WORLD, &matWorld);
	m_pDevice->SetTransform(D3DTS_VIEW, _SINGLE(CCameraManager)->GetCamera(CN_MAIN)->GetMatView());
	m_pDevice->SetTransform(D3DTS_PROJECTION, _SINGLE(CCameraManager)->GetCamera(CN_MAIN)->GetMatProj());

	m_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	m_pDevice->SetFVF(VTXCOLORFVF);
	m_pDevice->SetStreamSource( 0, m_pGridVB, 0, sizeof( VERTEXCOLOR ) );
	m_pDevice->DrawPrimitive(D3DPT_LINELIST, 0, m_iCnt/2);

	m_pDevice->SetStreamSource( 0, m_pLineVB, 0, sizeof(VERTEXCOLOR) );
	m_pDevice->SetFVF(VTXCOLORFVF);
	m_pDevice->DrawPrimitive( D3DPT_LINELIST, 0, 3 );


	m_pDevice->SetRenderState( D3DRS_LIGHTING, TRUE );


}

void CDebug::Destroy()
{
	Safe_Release(m_pGridVB);
}