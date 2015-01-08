#pragma once

#include "define.h"
/*
카메라 클래스
여러 카메라를 사용할 수도 있기 때문에 싱글톤 아님.
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

