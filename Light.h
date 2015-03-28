#pragma once
#include "define.h"

class CLight
{
private:
	D3DLIGHT9	m_tLightInfo;

public:
	void Initialize(const D3DCOLORVALUE& colDif , const D3DCOLORVALUE& colSpc, const D3DCOLORVALUE& colAmb, const D3DLIGHTTYPE& eType);
	
	void SetPointLightInfo(const D3DXVECTOR3& vPos, const float& fRange);
	void SetDirectionalLightInfo(const D3DXVECTOR3& vDir);
	void SetSpotLightInfo(const D3DXVECTOR3& vPos, const float& fRange, const float& fOutAngle, const float& fInAngle, const float& fFalloff);

	void SetLightInfo(const D3DLIGHT9& tInfo);

	const D3DLIGHT9* GetLightInfo() const;

public:
	CLight(void);
	~CLight(void);
};

