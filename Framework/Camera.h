#pragma once

#include "define.h"
/*
ī�޶� Ŭ����
���� ī�޶� ����� ���� �ֱ� ������ �̱��� �ƴ�.
*/
class CEntity;

class CCamera
{
private:
	//ī�޶� ��ġ
	D3DXVECTOR3				m_vEyePt;
	//ī�޶� �ü�
    D3DXVECTOR3				m_vLookatPt;
	//ī�޶� ������
    D3DXVECTOR3				m_vUpVec;
	//ī�޶� �����
	D3DXMATRIX				m_matView;
	//ī�޶� �������
	D3DXMATRIX				m_matProj;
	//ī�޶� ���� ���� ����(FALSE�̶�� ��������)
	bool					m_isFixed;
	//������ �����ϴ� ������Ʈ.(NULL�̶�� ���� �ٶ󺸴� ��ġ�� ����)
	CEntity*				m_LookatObj;
	//ȸ�� ��
	float					m_Angle;
	

public:
	CCamera(void);
	~CCamera(void);
	//ī�޶� �ʱ�ȭ
	void				Init();
	//View��� ��ȯ
	D3DXMATRIX*			GetMatView();
	//Proj��� ��ȯ
	D3DXMATRIX*			GetMatProj();
	//���� ���� ���� ��ȯ
	bool				ToggleFix();
	//ī�޶� �̵�
	void				MoveCamera(D3DXVECTOR3 vPos);
	//ī�޶� ȸ��
	void				RotateCamera(float _fAngle);
	//ī�޶� ����
	HRESULT				SetCamera(D3DXVECTOR3 _vEye, D3DXVECTOR3 _vLookat, D3DXVECTOR3 _vUpVec, bool _isFixed);

};

