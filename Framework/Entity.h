#pragma once
#include "define.h"
/*
��ƼƼ Ŭ����
�뵵 : 3D��ü
���� : �̸�, Ÿ��, ��ȯ ���, 
*/

class CEntity
{
private:
	
	string			Name;
	eMESH_NUM		Mesh_num;
	eTEXTURE_NUM	Texture_num;

public:
	CEntity(void);
	~CEntity(void);

	/*Entity(	std::string _name, 
			eEntity_Type _type, 
			D3DXVECTOR3 _pos, 
			eMesh_Num _mesh,
			eTexture_Num _texture);
	Entity(float posX, float posY, float posZ);*/
};

