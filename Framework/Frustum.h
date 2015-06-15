#pragma once
#include "Singleton.h"
//절두체 컬링을 하는 클래스

class CEntity ;


class CFrustum : public CSingleton<CFrustum>
{
	friend CSingleton;
private:
	//절두체의 8정점
	D3DXVECTOR3 m_vtx[8];
	//현재 카메라의 월드 좌표
	D3DXVECTOR3 m_vPos;
	//절두체의 6평면
	D3DXPLANE m_plane[6];

public:

	bool Init();
	//절두체를 평면 설정
	bool setFrustum(const D3DXMATRIXA16&);
	//오브젝트가 절두체 안에 있는가?
	bool isInFrustum(const D3DXVECTOR3&,const float) ;

	//bool checkFrustumCulling(CEntity&);

	void Update(); 

	void Render();

	BOOL Draw( LPDIRECT3DDEVICE9 );

private:
	
	CFrustum(void);
	~CFrustum(void);
};

