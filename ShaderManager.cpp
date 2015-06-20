#include "ShaderManager.h"
#include "Shader.h"
#include "Entity.h"

CShaderManager::CShaderManager(void)
	: m_pCurShader(NULL)
{
}


CShaderManager::~CShaderManager(void)
{
	Clear();
}

HRESULT CShaderManager::CreateShader(const eSHADER_KEY& eShader, const TCHAR* pName)
{
	if(FindShader(eShader))
		return S_OK;

	CShader* pShader = new CShader;
	if(FAILED(pShader->Initialize(pName)))
	{
		Safe_Delete(pShader);

		return E_FAIL;
	}

	m_mapShader.insert(map<eSHADER_KEY, CShader*>::value_type(eShader, pShader));

	return S_OK;

}

void CShaderManager::BeginShader(const eSHADER_KEY& eShader, const string& strTechKey)
{
	CShader* pShader = FindShader(eShader);

	if(!pShader)
		return;
	SetCurShader(pShader);

	//테크닉 핸들 얻기 & 테크닉 활성화
	pShader->SetTech(strTechKey.c_str());

	//활성화 테크닉 시작

	pShader->Begin();
}

void CShaderManager::EndShader(const eSHADER_KEY& eShader)
{
	CShader* pShader = FindShader(eShader);

	if(!pShader)
		return;

	pShader->End();

	ResetCurShader();
}

void CShaderManager::SetCurShader(CShader* pShader)
{
	m_pCurShader = pShader;
}

void CShaderManager::ResetCurShader()
{
	m_pCurShader = NULL;
}

CShader* CShaderManager::FindShader(const eSHADER_KEY& eShader) const
{
	map<eSHADER_KEY, CShader*>::const_iterator iter = m_mapShader.find(eShader);

	if(iter == m_mapShader.end())
		return NULL;

	return iter->second;
}

void CShaderManager::Clear()
{
	Safe_Delete_Map(m_mapShader);
}

void CShaderManager::SetFloat(const LPCSTR szName, const float& f)
{
	m_pCurShader->SetFloat(szName, f);
}

void CShaderManager::SetMatrix(const LPCSTR szName, const D3DXMATRIX* pMat)
{
	m_pCurShader->SetMatrix(szName, pMat);
}

void CShaderManager::SetString(const LPCSTR szName, const LPCSTR pString)
{
	m_pCurShader->SetString(szName, pString);
}

void CShaderManager::SetTexture(const LPCSTR szName, const LPDIRECT3DBASETEXTURE9 pTexture)
{
	m_pCurShader->SetTexture(szName, pTexture);
}

void CShaderManager::SetVector4(const LPCSTR szName, const D3DXVECTOR4* pVector)
{
	m_pCurShader->SetVector4(szName, pVector);
}

void CShaderManager::SetVector3(const LPCSTR szName, const D3DXVECTOR3* pVector)
{
	m_pCurShader->SetVector3(szName, pVector);
}
void CShaderManager::SetValue(const LPCSTR szName, const void* pValue, const UINT& uSize)
{
	m_pCurShader->SetValue(szName, pValue, uSize);
}