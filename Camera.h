#pragma once

#include "define.h"
/*
ī�޶� Ŭ����
���� ī�޶� ����� ���� �ֱ� ������ �̱��� �ƴ�.
*/

class CCamera
{
protected:
	//D3DXVECTOR3				m_vEyePt;		//vPos
 //   D3DXVECTOR3				m_vLookatPt;	//vLook
 //   D3DXVECTOR3				m_vUpVec;		//vUp
	//D3DXMATRIX				matView;
	//D3DXMATRIX				matProj;
	CAMERA						m_tCam;

public:
	virtual void Init();
	virtual void Update();
	virtual void Input();

public:
	void SetViewMatrix();
	void SetPos(const D3DXVECTOR3& vPos);
	void SetData(const D3DXVECTOR3& vUp, const D3DXVECTOR3& vLook, const D3DXVECTOR3& vRight);
	void SetCamera(const CAMERA&	_tCamera);

public:
	D3DXMATRIX*			GetMatView();
	D3DXMATRIX*			GetMatProj();
	CAMERA				GetCameraInfo();

public:
	void SetTransform();

public:
	CCamera(void);
	virtual ~CCamera(void);
};

