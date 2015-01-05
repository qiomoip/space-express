#pragma once
#include <string>
#include "Define.h"
/*
��ƼƼ Ŭ����
�뵵 : 3D��ü
���� : �̸�, Ÿ��, ��ȯ ���, 
*/

class Entity
{
private:
	
	std::string		Name;
	eEntity_Type	Type;
	eMesh_Num		Mesh;
	eTexture_Num	Texture;

	D3DXMATRIXA16	matWorld;
	D3DXMATRIXA16	matTranslate;
	D3DXMATRIXA16	matRotate;
	D3DXMATRIXA16	matScale;

public:
	Entity(void);
	~Entity(void);

	/*Entity(	std::string _name, 
			eEntity_Type _type, 
			D3DXVECTOR3 _pos, 
			eMesh_Num _mesh,
			eTexture_Num _texture);
	Entity(float posX, float posY, float posZ);*/
};

