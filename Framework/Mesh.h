#pragma once
#include "define.h"

class CTexture;

class CMesh
{
protected:
	vector<CTexture*>	m_vecTexture;
public:
	virtual void Render()PURE;
	virtual void Destroy();

	virtual HRESULT LoadResource(const LPTSTR szMeshName)PURE;

public:
	CMesh(void);
	virtual ~CMesh(void);
};

