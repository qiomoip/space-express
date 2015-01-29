#pragma once
#include <string>
#include "Enum.h"

class CMesh;
/*
��ƼƼ Ŭ����
�뵵 : 3D��ü
���� : �̸�, Ÿ��, ��ȯ ���, 
*/

class CEntity
{
private:
	
	std::string		Name;
	eMESH_NUM		Mesh_num;
	eTEXTURE_NUM	Texture_num;
	CMesh*			m_pMesh;
	eRENDER_TYPE	m_eRenderType;

public:
	void Initialize();
	void Update();
	void Render();

//Setter
public:
	void SetRenderType(const eRENDER_TYPE& eRender);
	void PushMesh(CMesh* pMesh);

//Getter
public:
	const eRENDER_TYPE& GetRenderType() const;
	const CMesh*		GetMesh() const;

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

