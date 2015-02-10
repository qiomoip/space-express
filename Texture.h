#pragma once
#include "define.h"

class CTexture
{
private:
	LPDIRECT3DTEXTURE9	m_pTex;

public:
	void Destroy();

public:
	void SetTexture();

public:
	void SetTextureInfo(const LPDIRECT3DTEXTURE9 pTex);

public:
	const LPDIRECT3DTEXTURE9 GetTextureInfo() const;
public:
	CTexture(void);
	~CTexture(void);
};

