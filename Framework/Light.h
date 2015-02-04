#pragma once
#include "define.h"

class CLight
{
private:
	D3DLIGHT9	m_tLightInfo;

public:
	void SetLightInfo(const D3DLIGHT9& tInfo);

	const D3DLIGHT9* GetLightInfo() const;

public:
	CLight(void);
	~CLight(void);
};

