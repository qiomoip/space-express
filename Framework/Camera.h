#pragma once

#include "define.h"
/*
ī�޶� Ŭ����
���� ī�޶� ����� ���� �ֱ� ������ �̱��� �ƴ�.
*/

class CCamera
{
private:

	D3DXVECTOR3				vEyePt;		//vPos
    D3DXVECTOR3				vLookatPt;	//vLook
    D3DXVECTOR3				vUpVec;		//vUp
	D3DXMATRIX				matView;
	D3DXMATRIX				matProj;
public:
	void Init();
	void Update();
	void Input();

public:
	D3DXMATRIX*			GetMatView();
	D3DXMATRIX*			GetMatProj();

public:
	CCamera(void);
	~CCamera(void);
};

