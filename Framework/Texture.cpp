#include "Texture.h"
#include "Device.h"

CTexture::CTexture(void)
	:m_strName("")
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
	m_strName = strName;
}

void CTexture::SetTexture()
{
	_SINGLE(CDevice)->GetDevice()->SetTexture(0, m_pTex);
}

const LPDIRECT3DTEXTURE9 CTexture::GetTextureInfo() const
{
	return m_pTex;
}

const string& CTexture::SetTextureName() const
{
	return m_strName;
}

void CTexture::Destroy()
{
	Safe_Release(m_pTex);
}