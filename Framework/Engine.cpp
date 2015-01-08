#include "Engine.h"
#include "Device.h"

CEngine::CEngine(void)
	: m_pDevice(NULL)
	, m_Name(NULL)
#ifdef _DEBUG
	, m_pVB(NULL)
#endif
{
}

CEngine::~CEngine(void)
{
}

VOID CEngine::Render()
{
	if( NULL == m_pDevice->GetDevice() )
        return;

    // Clear the backbuffer to a blue color
    m_pDevice->GetDevice()->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB( 200, 200, 200 ), 1.0f, 0 );

    // Begin the scene
    if( SUCCEEDED( m_pDevice->GetDevice()->BeginScene() ) )
    {
        // Rendering of scene objects can happen here
#ifdef _DEBUG
		DrawInfo();
#endif
        // End the scene
        m_pDevice->GetDevice()->EndScene();
    }

    // Present the backbuffer contents to the display
    m_pDevice->GetDevice()->Present( NULL, NULL, NULL, NULL );
}

HRESULT CEngine::Initialize(HWND hWnd)
{
	m_pDevice = _SINGLE(CDevice);

	if(FAILED(m_pDevice->Initialize(hWnd)))
	{
		return E_FAIL;
	}

#ifdef _DEBUG
	CreateVertexBuffer();
#endif

	return S_OK;
}

VOID CEngine::Destroy()
{
	if(m_pDevice)
		m_pDevice->Cleanup();
}

#ifdef _DEBUG
void CEngine::CreateVertexBuffer()
{
	 UINT   dwSize = ( 1280 + 12 ) * sizeof( VERTEXCOLOR );
	m_pDevice->GetDevice()->CreateVertexBuffer( dwSize, 0, VTXCOLORFVF, D3DPOOL_MANAGED,
      &m_pVB, NULL );
	VERTEXCOLOR*   vertices = new VERTEXCOLOR[ dwSize ];
	DWORD      dwCountHalfLine = 1280 / 8;
   FLOAT      fMaxDist      = dwCountHalfLine * 1.0f;
   FLOAT      fTmpDist      = -fMaxDist;

   for( DWORD i = 0 ; i < 1280 / 2 ; i += 2 )
   {
      if( i == 1280 / 4 ) fTmpDist += 1.0f;
	  vertices[i].vPos = D3DXVECTOR3(-fMaxDist, 0.0f, fTmpDist);
	  vertices[i].dwColor = D3DCOLOR_XRGB(125, 125, 125);

	  vertices[i+1].vPos = D3DXVECTOR3(fMaxDist, 0.0f, fTmpDist);
	  vertices[i+1].dwColor = D3DCOLOR_XRGB(125, 125, 125);

      fTmpDist += 1.0f;
   }

   fTmpDist   = -fMaxDist;
   for( DWORD i = 1280 / 2 ; i < 200 ; i += 2 )
   {
      if( i == 1280 / 4 *3 ) fTmpDist += 1.0f;
	  vertices[i].vPos = D3DXVECTOR3(fTmpDist, 0.0f, -fMaxDist);
	  vertices[i].dwColor = D3DCOLOR_XRGB(125, 125, 125);
	  vertices[i+1].vPos = D3DXVECTOR3(fTmpDist, 0.0f, -fMaxDist);
	  vertices[i+1].dwColor = D3DCOLOR_XRGB(125, 125, 125);
      fTmpDist += 1.0f;
   }

   vertices[1280 + 0].vPos = D3DXVECTOR3(0.f, 0.f, 0.f);
   vertices[1280 + 0].dwColor = D3DCOLOR_XRGB(255, 0, 0);

   vertices[1280 + 1].vPos = D3DXVECTOR3(fMaxDist, 0.0f, 0.0f);
   vertices[1280 + 1].dwColor = D3DCOLOR_XRGB(255, 0, 0);

   vertices[1280 + 2].vPos = D3DXVECTOR3(0.f, 0.f, 0.f);
   vertices[1280 + 2].dwColor = D3DCOLOR_XRGB(125, 125, 125);

   vertices[1280 + 3].vPos = D3DXVECTOR3(-fMaxDist, 0.0f, 0.0f);
   vertices[1280 + 3].dwColor = D3DCOLOR_XRGB(125, 125, 125);

   vertices[1280 + 4].vPos = D3DXVECTOR3(0.f, 0.f, 0.f);
   vertices[1280 + 4].dwColor = D3DCOLOR_XRGB(0, 255, 0);

   vertices[1280 + 5].vPos = D3DXVECTOR3(0.0f,  fMaxDist, 0.0f);
   vertices[1280 + 5].dwColor = D3DCOLOR_XRGB(0, 255, 0);

   vertices[1280 + 6].vPos = D3DXVECTOR3(0.f, 0.f, 0.f);
   vertices[1280 + 6].dwColor = D3DCOLOR_XRGB(125, 125, 125);

   vertices[1280 + 7].vPos = D3DXVECTOR3(0.0f, -fMaxDist, 0.0f);
   vertices[1280 + 7].dwColor = D3DCOLOR_XRGB(125, 125, 125);

   vertices[1280 + 8].vPos = D3DXVECTOR3(0.f, 0.f, 0.f);
   vertices[1280 + 8].dwColor = D3DCOLOR_XRGB(0, 0, 255);

   vertices[1280 + 9].vPos = D3DXVECTOR3(0.0f, 0.0f,  fMaxDist);
   vertices[1280 + 9].dwColor = D3DCOLOR_XRGB(0, 0, 255);

   vertices[1280 + 10].vPos = D3DXVECTOR3(0.f, 0.f, 0.f);
   vertices[1280 + 10].dwColor = D3DCOLOR_XRGB(125, 125, 125);

   vertices[1280 + 11].vPos = D3DXVECTOR3(0.0f, 0.0f, -fMaxDist);
   vertices[1280 + 11].dwColor = D3DCOLOR_XRGB(125, 125, 125);

   // 3. Lock
   VOID* pVertices;
   m_pVB->Lock( 0, dwSize, &pVertices, 0 ) ;

   memcpy( pVertices, vertices, dwSize );

   // 4. Unlock
   m_pVB->Unlock();

   Safe_Delete_Array( vertices );


}

void CEngine::DrawInfo()
{
	DrawGrid();
}

void CEngine::DrawGrid()
{
	D3DXMATRIX matIden;
	D3DXMatrixIdentity(&matIden);
	m_pDevice->GetDevice()->SetTransform(D3DTS_WORLD, &matIden);
	m_pDevice->GetDevice()->SetRenderState(D3DRS_LIGHTING, false);
	m_pDevice->GetDevice()->SetFVF(VTXCOLORFVF);
	m_pDevice->GetDevice()->SetStreamSource( 0, m_pVB, 0, sizeof( VERTEXCOLOR ) );
   m_pDevice->GetDevice()->DrawPrimitive( D3DPT_LINELIST, 0, ( 1280 + 12 ) / 2 );
   m_pDevice->GetDevice()->SetRenderState( D3DRS_LIGHTING, TRUE );
}
#endif