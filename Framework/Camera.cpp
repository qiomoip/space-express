#include "Camera.h"


CCamera::CCamera(void)
{
	Init();
}


CCamera::~CCamera(void)
{
}

void CCamera::Init()
{
	m_isFixed = TRUE;
	m_LookatObj = NULL;
	D3DXMatrixIdentity( &m_matView);
	D3DXMatrixIdentity( &m_matProj);

	m_vEyePt = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	m_vLookatPt = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	m_vUpVec = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );

	MoveCamera(D3DXVECTOR3(3.0f, 3.0f,-3.0f ) );
}


D3DXMATRIX* CCamera::GetMatView() 
{
	return &m_matView;
}

D3DXMATRIX* CCamera::GetMatProj() 
{
	return &m_matProj;
}

bool CCamera::ToggleFix()
{
	return m_isFixed = !m_isFixed;	
}

void CCamera::MoveCamera (D3DXVECTOR3 vPos)
{
	D3DXVECTOR3 Dest = vPos + m_vEyePt;
	
	//자유시점이라면 바라보는 방향도 갱신
	if ( !m_isFixed )
		m_vLookatPt = m_vLookatPt - m_vEyePt + Dest; //차벡터

	m_vEyePt = Dest;

	D3DXMatrixLookAtLH( &m_matView, &m_vEyePt, &m_vLookatPt, &m_vUpVec );
	D3DXMatrixPerspectiveFovLH( &m_matProj, D3DX_PI / 4, 1.0f, 1.0f, 1000.0f );	
}

