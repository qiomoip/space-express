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
	
	//���������̶�� �ٶ󺸴� ���⵵ ����
	if ( !m_isFixed )
		m_vLookatPt = m_vLookatPt - m_vEyePt + Dest; //������

	m_vEyePt = Dest;

	D3DXMatrixLookAtLH( &m_matView, &m_vEyePt, &m_vLookatPt, &m_vUpVec );
	D3DXMatrixPerspectiveFovLH( &m_matProj, D3DX_PI / 4, 1.0f, 1.0f, 1000.0f );	
}

HRESULT	 CCamera::SetCamera(D3DXVECTOR3 _vEye, D3DXVECTOR3 _vLookat, D3DXVECTOR3 _vUpVec, bool _isFixed)
{
	m_vEyePt = _vEye;
	m_vLookatPt = _vLookat;
	m_vUpVec = _vUpVec;
	m_isFixed = _isFixed;

	D3DXMatrixLookAtLH( &m_matView, &m_vEyePt, &m_vLookatPt, &m_vUpVec );
	D3DXMatrixPerspectiveFovLH( &m_matProj, D3DX_PI / 4, 1.0f, 1.0f, 1000.0f );	

	return S_OK;
}