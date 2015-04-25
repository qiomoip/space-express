#include "Texture.h"
#include "Device.h"
#include "ShaderManager.h"
#include "Shader.h"

CTexture::CTexture(void)
{
}


CTexture::~CTexture(void)
{
	Destroy();
}

void CTexture::SetTextureInfo(const LPDIRECT3DTEXTURE9 pTex)
{
	m_pTex = pTex;
}

void CTexture::SetTextureName(const string& strName)
{
	m_strTextureName = strName;
}

void CTexture::SetTexture()
{
//	_SINGLE(CDevice)->GetDevice()->SetTexture(0, m_pTex);
	_SINGLE(CShaderManager)->SetTexture("g_BaseTex", m_pTex);
	m_strTextureName;
}

const LPDIRECT3DTEXTURE9 CTexture::GetTextureInfo() const
{
	return m_pTex;
}

void CTexture::Destroy()
{
	Safe_Release(m_pTex);
}