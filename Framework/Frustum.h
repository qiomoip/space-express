#pragma once
#include "Singleton.h"
//����ü �ø��� �ϴ� Ŭ����

class CEntity ;


class CFrustum : public CSingleton<CFrustum>
{
	friend CSingleton;
private:
	//����ü�� 8����
	D3DXVECTOR3 m_vtx[8];
	//���� ī�޶��� ���� ��ǥ
	D3DXVECTOR3 m_vPos;
	//����ü�� 6���
	D3DXPLANE m_plane[6];

public:

	bool Init();
	//����ü�� ��� ����
	bool setFrustum(const D3DXMATRIXA16&);
	//������Ʈ�� ����ü �ȿ� �ִ°�?
	bool isInFrustum(const D3DXVECTOR3&,const float) ;

	//bool checkFrustumCulling(CEntity&);

	void Update(); 

	void Render();

	BOOL Draw( LPDIRECT3DDEVICE9 );

private:
	
	CFrustum(void);
	~CFrustum(void);
};

