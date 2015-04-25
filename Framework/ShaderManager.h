#pragma once
#include "Singleton.h"

class CShader;
class CEntity;

class CShaderManager
	: public CSingleton<CShaderManager>
{
	friend CSingleton;
private:
	map<eSHADER_KEY, CShader*>	m_mapShader;	
	CShader*					m_pCurShader;

public:
	void Clear();

public:
	HRESULT CreateShader(const eSHADER_KEY& eShader, const TCHAR* pName);
	void BeginShader(const eSHADER_KEY& eShader, const string& strTechKey);
	void EndShader(const eSHADER_KEY& eShader);
	void SetCurShader(CShader* pShader);
	void ResetCurShader();

public:
	void SetFloat(const LPCSTR szName, const float& f);
	void SetMatrix(const LPCSTR szName, const D3DXMATRIX* pMat);
	void SetString(const LPCSTR szName, const LPCSTR pString);
	void SetTexture(const LPCSTR szName, const LPDIRECT3DBASETEXTURE9 pTexture);
	void SetVector4(const LPCSTR szName, const D3DXVECTOR4* pVector);
	void SetVector3(const LPCSTR szName, const D3DXVECTOR3* pVector);
	void SetValue(const LPCSTR szName, const void* pValue, const UINT& uSize);

public:
	CShader* FindShader(const eSHADER_KEY& eShader) const;

private:
	CShaderManager(void);
	~CShaderManager(void);
};

