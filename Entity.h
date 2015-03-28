#pragma once

#include "define.h"

class CMesh;

/*
엔티티 클래스
용도 : 3D전체
내용 : 이름, 타입, 변환 행렬, 
*/

class CEntity
{
private:
	
	std::string		m_strName;
	eMESH_NUM		Mesh_num;
	eTEXTURE_NUM	Texture_num;
	CMesh*			m_pMesh;
	eRENDER_TYPE	m_eRenderType;
	D3DXVECTOR3		m_vPos;
	D3DXMATRIX		m_matWorld;
	float			m_fAngle[AT_MAX];
	D3DXMATRIX		m_matScale;
	D3DXMATRIX		m_matRot[AT_MAX];
	float			m_fScale[AT_MAX];
	bool			m_bVisiable;
	eSHADER_KEY	m_eShader;
	string			m_strTechKey;
	vector<UINT>	m_vecPass;

public:
	void Initialize();
	void Update();
	void Render();
	void Input();

public:
	void RotationY();

//Setter
public:
	void SetRenderType(const eRENDER_TYPE& eRender);
	void PushMesh(CMesh* pMesh);
	void SetName(const string& strName);
	void SetPos(const D3DXVECTOR3& vPos);
	void SetScale(const float& fScaleX, const float& fScaleY, const float& fScaleZ);
	void SetVisiable();
	void SetTechKey(const string& strTechKey);
	void SetPass(const UINT& uPass);
	void SetShader(const eSHADER_KEY& pShader);

//Getter
public:
	const eRENDER_TYPE& GetRenderType() const;
	const CMesh*		GetMesh() const;
	const string&		GetName() const;
	const D3DXVECTOR3&	GetPos() const;
	const eSHADER_KEY&		GetShader() const;
	const vector<UINT>&			GetPassList()	const;
	const string&		GetTechKey() const;

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

