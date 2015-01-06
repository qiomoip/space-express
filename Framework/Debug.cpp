#include "Debug.h"
#include "Device.h"


CDebug::CDebug(void)
	: m_pGridVB(NULL)
{
}


CDebug::~CDebug(void)
{
	Destroy();
}

void CDebug::Initialize()
{
	CreateVertexBuffer();
}

void CDebug::CreateVertexBuffer()
{
	UINT   dwSize = ( 1280 + 12 ) * sizeof( VERTEXCOLOR );
	_SINGLE(CDevice)->GetDevice()->CreateVertexBuffer( dwSize, 0, VTXCOLORFVF, D3DPOOL_MANAGED,
      &m_pGridVB, NULL );
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
   m_pGridVB->Lock( 0, dwSize, &pVertices, 0 ) ;

   memcpy( pVertices, vertices, dwSize );

   // 4. Unlock
   m_pGridVB->Unlock();

   Safe_Delete_Array( vertices );
}


void CDebug::Update()
{
}

void CDebug::Render()
{
	DrawInfo();
}

void CDebug::DrawInfo()
{
	DrawGrid();
}

void CDebug::DrawGrid()
{
	D3DXMATRIX matIden;
	D3DXMatrixIdentity(&matIden);
	_SINGLE(CDevice)->GetDevice()->SetTransform(D3DTS_WORLD, &matIden);
	_SINGLE(CDevice)->GetDevice()->SetRenderState(D3DRS_LIGHTING, false);
	_SINGLE(CDevice)->GetDevice()->SetFVF(VTXCOLORFVF);
	_SINGLE(CDevice)->GetDevice()->SetStreamSource( 0, m_pGridVB, 0, sizeof( VERTEXCOLOR ) );
	_SINGLE(CDevice)->GetDevice()->DrawPrimitive( D3DPT_LINELIST, 0, ( 1280 + 12 ) / 2 );
	_SINGLE(CDevice)->GetDevice()->SetRenderState( D3DRS_LIGHTING, TRUE );
}

void CDebug::Destroy()
{
	Safe_Release(m_pGridVB);
}