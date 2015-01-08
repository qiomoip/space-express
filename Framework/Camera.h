#pragma once

#include "define.h"
/*
카메라 클래스
여러 카메라를 사용할 수도 있기 때문에 싱글톤 아님.
*/
class CEntity;

class CCamera
{
private:
	//카메라 위치
	D3DXVECTOR3				m_vEyePt;
	//카메라 시선
    D3DXVECTOR3				m_vLookatPt;
	//카메라 업벡터
    D3DXVECTOR3				m_vUpVec;
	//카메라 뷰행렬
	D3DXMATRIX				m_matView;
	//카메라 투영행렬
	D3DXMATRIX				m_matProj;
	//카메라 시점 고정 여부(FALSE이라면 자유시점)
	bool					m_isFixed;
	//시점을 고정하는 오브젝트.(NULL이라면 현재 바라보는 위치로 고정)
	CEntity*				m_LookatObj;
	

public:
	CCamera(void);
	~CCamera(void);
	//카메라 초기화
	void				Init();
	//View행렬 반환
	D3DXMATRIX*			GetMatView();
	//Proj행렬 반환
	D3DXMATRIX*			GetMatProj();
	//시점 고정 여부 전환
	bool				ToggleFix();
	//카메라 이동
	void				MoveCamera(D3DXVECTOR3 vPos);

};

