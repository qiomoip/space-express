#pragma once
#include "define.h"

class CTexture;
class CShader;

class CMesh
{
protected:
	//vector<CTexture*>	m_vecTexture;
	CTexture**			m_arrayTexture;
public:
	virtual void Render(CShader* pShader, const UINT& uPass)PURE;
	virtual void Destroy();

	virtual HRESULT LoadResource(const LPTSTR szMeshName)PURE;

public:
	CMesh(void);
	virtual ~CMesh(void);
};

