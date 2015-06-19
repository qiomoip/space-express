#pragma once
#include "define.h"

class CTexture;
class CShader;

class CMesh
{
protected:
	//vector<CTexture*>	m_vecTexture;
	CTexture**			m_arrayTexture;

	eMESH_TYPE			m_ColType;
public:
	virtual void Render(CShader* pShader, const UINT& uPass)PURE;
	virtual void Destroy();

	virtual HRESULT LoadResource(const LPTSTR szMeshName)PURE;

	virtual float GetSize() PURE;

	virtual const eMESH_TYPE GetColliderType() const {return m_ColType;}

	virtual const LPD3DXMESH GetMesh() const {return NULL;};
	
	virtual bool GetCollisionPos(RAY& tRay);

public:
	CMesh(void);
	virtual ~CMesh(void);
};

