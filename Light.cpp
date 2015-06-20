#include "Light.h"


CLight::CLight(void)
{
	memset(&m_tLightInfo, 0, sizeof(D3DLIGHT9));
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

void CLight::Initialize(const D3DCOLORVALUE& colDif, const D3DCOLORVALUE& colSpc, const D3DCOLORVALUE& colAmb, const D3DLIGHTTYPE& eType)
{
	memset(&m_tLightInfo, 0, sizeof(D3DLIGHT9));
	m_tLightInfo.Ambient = colAmb;
	m_tLightInfo.Diffuse = colDif;
	m_tLightInfo.Specular = colSpc;
	m_tLightInfo.Type = eType;
}

void CLight::SetPointLightInfo(const D3DXVECTOR3& vPos, const float& fRange)
{
	m_tLightInfo.Position = vPos;
	m_tLightInfo.Range = fRange;
}

void CLight::SetDirectionalLightInfo(const D3DXVECTOR3& vDir)
{
	m_tLightInfo.Direction = vDir;
}

void CLight::SetSpotLightInfo(const D3DXVECTOR3& vPos, const float& fRange, const float& fOutAngle, const float& fInAngle, const float& fFalloff)
{
	m_tLightInfo.Position = vPos;
	m_tLightInfo.Range = fRange;
	m_tLightInfo.Phi = fOutAngle;
	m_tLightInfo.Theta = fInAngle;
	m_tLightInfo.Falloff = fFalloff;
}