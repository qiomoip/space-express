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
	D3DXMatrixIdentity( &matView);
	D3DXMatrixIdentity( &matProj);

	vEyePt = D3DXVECTOR3( 3.0f, 3.0f,-3.0f );
	vLookatPt = D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	vUpVec = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );

	D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
	D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI / 4, 1.0f, 1.0f, 1000.0f );
}


D3DXMATRIX* CCamera::GetMatView() 
{
	return &matView;
}

D3DXMATRIX* CCamera::GetMatProj() 
{
	return &matProj;
}

