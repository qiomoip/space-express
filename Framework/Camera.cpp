#include "Camera.h"
#include "KeyManager.h"

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

	vEyePt = D3DXVECTOR3( -3.f, 3.f, -3.f );
	vLookatPt = D3DXVECTOR3( 0.0f, 0.0f, 1.0f );
	vUpVec = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );

	D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
	D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI / 4, 1.0f, 1.0f, 1000.0f );

	_SINGLE(CKeyManager)->SetKeyData(KEY_RIGHT, VK_RIGHT);
	_SINGLE(CKeyManager)->SetKeyData(KEY_LEFT, VK_LEFT);
}

void CCamera::Update()
{
	Input();

	D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
}

void CCamera::Input()
{
	const KEYINFO* pInfo = _SINGLE(CKeyManager)->GetKey(KEY_RIGHT);
	if(!pInfo)
		return;
	if(pInfo->bPush || pInfo->bDown)
	{
		vEyePt += D3DXVECTOR3(0.05f, 0.f, 0.f);
	}
	pInfo = _SINGLE(CKeyManager)->GetKey(KEY_LEFT);
	if(pInfo->bPush || pInfo->bDown)
	{
		vEyePt -= D3DXVECTOR3(0.05f, 0.f, 0.f);
	}
}


D3DXMATRIX* CCamera::GetMatView() 
{
	return &matView;
}

D3DXMATRIX* CCamera::GetMatProj() 
{
	return &matProj;
}

