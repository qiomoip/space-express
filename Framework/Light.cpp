#include "Light.h"


CLight::CLight(void)
{
}


CLight::~CLight(void)
{
}

void CLight::SetLightInfo(const D3DLIGHT9& tInfo)
{
	m_tLightInfo = tInfo;
}

const D3DLIGHT9* CLight::GetLightInfo() const
{
	return &m_tLightInfo;
}
