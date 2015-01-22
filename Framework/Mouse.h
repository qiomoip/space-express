#pragma once
#include <iostream>
#include <Windows.h>
#include <mmsystem.h>
#include <d3dx9.h>
using namespace std;

typedef struct _tagRay
{
	D3DXVECTOR3 vOrigin;
	D3DXVECTOR3 vDir;
	D3DXVECTOR3 vIntersectPos;
}RAY;

class CMouse
{
private:
	static CMouse* m_pInstance;
	POINT	m_pt;
	RAY		m_tRay;

public:
	void CaculateMousePos();
	void CaculateRay();
	RAY TransformRay(const D3DXMATRIX* pMat);
	bool IntersectRayToSphere(RAY* pRay, const D3DXVECTOR3& vPos, const float fRadius);

public:
	const RAY& GetRay() const;

//Singleton
public:
	static CMouse* GetInstance()
	{
		if(!m_pInstance)
		{
			m_pInstance = new CMouse;
		}
		return m_pInstance;
	}
	void DestroyInstance()
	{
		if(m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = 0;
		}
	}
private:
	CMouse(void);
	~CMouse(void);
};



