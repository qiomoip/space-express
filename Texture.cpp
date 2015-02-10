#include "Texture.h"
#include "Device.h"

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

void CTexture::SetTexture()
{
	_SINGLE(CDevice)->GetDevice()->SetTexture(0, m_pTex);
}

const LPDIRECT3DTEXTURE9 CTexture::GetTextureInfo() const
{
	return m_pTex;
}

void CTexture::Destroy()
{
	Safe_Release(m_pTex);
}