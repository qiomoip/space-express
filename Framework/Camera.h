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

};

