#pragma once

#include "define.h"
/*
ī�޶� Ŭ����
���� ī�޶� ����� ���� �ֱ� ������ �̱��� �ƴ�.
*/

class CCamera
{
private:

	D3DXVECTOR3				vEyePt;
    D3DXVECTOR3				vLookatPt;
    D3DXVECTOR3				vUpVec;
	D3DXMATRIX				matView;
	D3DXMATRIX				matProj;
	

public:
	CCamera(void);
	~CCamera(void);

	void Init();
	
	D3DXMATRIX*			GetMatView();
	D3DXMATRIX*			GetMatProj();


};

