#include "Shader.h"
#include "Device.h"

CShader::CShader(void)
	: m_pEffect(NULL)
	, m_pErrBuffer(NULL)
{
}


CShader::~CShader(void)
{
}

/*
이펙트 객체 생성
성공 : S_OK
실패 : E_FAIL 
*/

HRESULT CShader::Initialize(const TCHAR* pFileName)
{
	if(FAILED(D3DXCreateEffectFromFile(_SINGLE(CDevice)->GetDevice(), pFileName, 0, 0, /*D3DXSHADER_DEBUG*/0,
		0, &m_pEffect, &m_pErrBuffer)))
	{
		//생성 실패
		MessageBoxA(0, (LPCSTR)(m_pErrBuffer->GetBufferPointer()), NULL, 0);
		Safe_Delete(m_pEffect);
		return E_FAIL;
	}

	CreateHandle("g_matWorld");
	CreateHandle("g_matView");
	CreateHandle("g_matProj");
	
	CreateHandle("g_matWV");
	CreateHandle("g_matWVP");
	CreateHandle("g_BaseTex");

	CreateHandle("g_mtrlMesh");

	return S_OK;
}

void CShader::Begin()
{
	UINT uPass = 0;
	m_pEffect->Begin(&uPass, 0);
}

	void CShader::End()
	{
		m_pEffect->End();
	}

void CShader::CreateHandle(const LPCSTR pName)
{
	if(GetHandle(pName))	//이미 있는 핸들
		return;

	D3DXHANDLE hHandle = m_pEffect->GetParameterByName(NULL, pName);

	m_mapHandle.insert(map<string, D3DXHANDLE>::value_type(pName, hHandle));
}

void CShader::SetFloat(const LPCSTR szName, const float& f)
{
	D3DXHANDLE hParam = GetHandle(szName);
	m_pEffect->SetFloat(hParam, f);
}

void CShader::SetMatrix(const LPCSTR szName, const D3DXMATRIX* pMat)
{
	D3DXHANDLE hParam = GetHandle(szName);
	m_pEffect->SetMatrix(hParam, pMat);
}

void CShader::SetString(const LPCSTR szName, const LPCSTR pString)
{
	D3DXHANDLE hParam = GetHandle(szName);
	m_pEffect->SetString(hParam, pString);
}

void CShader::SetTexture(const LPCSTR szName, const LPDIRECT3DBASETEXTURE9 pTexture)
{
	D3DXHANDLE hParam = GetHandle(szName);
	m_pEffect->SetTexture(hParam, pTexture);
}

void CShader::SetVector4(const LPCSTR szName, const D3DXVECTOR4* pVector)
{
	D3DXHANDLE hParam = GetHandle(szName);
	m_pEffect->SetVector(hParam, pVector);
}

void CShader::SetVector3(const LPCSTR szName, const D3DXVECTOR3* pVector)
{
	D3DXHANDLE hParam = GetHandle(szName);
	m_pEffect->SetValue(hParam, pVector, sizeof(D3DXVECTOR3));
}

void CShader::SetValue(const LPCSTR szName, const void* pValue, const UINT& uSize)
{
	D3DXHANDLE hParam = GetHandle(szName);
	m_pEffect->SetValue(hParam, pValue, uSize);
}

void CShader::SetTech(const LPCSTR pName)
{
	m_pEffect->SetTechnique(m_pEffect->GetTechniqueByName(pName));
}

void CShader::BeginPass(const UINT& uPass)
{
	m_pEffect->BeginPass(uPass);
}

void CShader::EndPass()
{
	m_pEffect->EndPass();
}

const D3DXHANDLE CShader::GetHandle(LPCSTR pName)
{
	map<string, D3DXHANDLE>::iterator iter = m_mapHandle.find(pName);

	if(iter == m_mapHandle.end())
		return NULL;
	return iter->second;
}