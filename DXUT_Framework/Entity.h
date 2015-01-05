#pragma once
#include <string>
#include "Define.h"
/*
엔티티 클래스
용도 : 3D전체
내용 : 이름, 타입, 변환 행렬, 
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

