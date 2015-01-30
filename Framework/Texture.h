#pragma once
#include "define.h"

class CTexture
{
private:
	LPDIRECT3DTEXTURE9	m_pTex;
	string				m_strName;

public:
	void Destroy();

public:
	void SetTexture();

public:
	void SetTextureInfo(const LPDIRECT3DTEXTURE9 pTex);
	void SetTextureName(const string& strName);

public:
	const LPDIRECT3DTEXTURE9 GetTextureInfo() const;
	const string& SetTextureName() const;

public:
	CTexture(void);
	~CTexture(void);
};

