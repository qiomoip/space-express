#pragma once
#include "define.h"

class CShader
{
private:
	LPD3DXEFFECT m_pEffect;
	LPD3DXBUFFER m_pErrBuffer;
	map<string, D3DXHANDLE>	m_mapHandle;

public:
	HRESULT Initialize(const TCHAR* pFileName);
	void Begin();
	void End();

public:
	void CreateHandle(const LPCSTR pName);

	//setter
public:
	void SetFloat(const LPCSTR szName, const float& f);
	void SetMatrix(const LPCSTR szName, const D3DXMATRIX* pMat);
	void SetString(const LPCSTR szName, const LPCSTR pString);
	void SetTexture(const LPCSTR szName, const LPDIRECT3DBASETEXTURE9 pTexture);
	void SetVector4(const LPCSTR szName, const D3DXVECTOR4* pVector);
	void SetVector3(const LPCSTR szName, const D3DXVECTOR3* pVector);
	void SetValue(const LPCSTR szName, const void* pValue, const UINT& uSize);

	void SetTech(const LPCSTR pName);
	void BeginPass(const UINT& uPass);
	void CommitChanges();
	void EndPass();
	//getter
public:
	const D3DXHANDLE GetHandle(LPCSTR pName); 

public:
	CShader(void);
	~CShader(void);
};

