#pragma once
#include "Singleton.h"

class CMouse
	: public CSingleton<CMouse>
{
	friend CSingleton;
private:
	static CMouse* m_pInstance;
	POINT	m_pt;
	RAY		m_tRay;
	HWND	m_hWnd;

public:
	void CaculateMousePos();
	void CaculateRay();
	RAY TransformRay(const D3DXMATRIX* pMat);
	bool IntersectRayToSphere(RAY* pRay, const D3DXVECTOR3& vPos, const float fRadius);

public:
	void SetHwnd(const HWND& hWnd);
//Getter
public:
	const RAY& GetRay() const;
	const POINT& GetMousePos(){return m_pt;};

private:
	CMouse(void);
	~CMouse(void);
};



