#pragma once

#include "define.h"

class CMesh;
class CShader;

/*
��ƼƼ Ŭ����
�뵵 : 3D��ü
���� : �̸�, Ÿ��, ��ȯ ���, 
*/

class CEntity
{
public:
	eMESH_NUM		m_eMeshNum;
protected:
	std::string		m_strName;
	CMesh*			m_pMesh;
	eRENDER_TYPE	m_eRenderType;
	//��ġ
	D3DXVECTOR3		m_vPos;
	//���� ��
	D3DXVECTOR3		m_vWorldAxis[AT_MAX];
	//���� ��
	D3DXVECTOR3		m_vLocalAxis[AT_MAX];
	//ȸ�� ���
	D3DXMATRIX		m_matRot;
	//�̵� ���
	D3DXMATRIX		m_matTrans;
	//���� ���
	D3DXMATRIX		m_matWorld;
	//ȸ����
	float			m_fAngle[AT_MAX];
	//ũ�⺯ȯ ���
	D3DXMATRIX		m_matScale;
	//??
	D3DXQUATERNION	m_AxisRot;
	//ũ�� ��
	float			m_fScale[AT_MAX];
	//�׸��� ���� ����
	bool			m_bVisiable;
	//���̴� Ű (default: none, all : default)
	eSHADER_KEY		m_eShader;
	//��ũ�� Ű
	string			m_strTechKey;
	//�н� ����Ʈ
	vector<UINT>	m_vecPass;
	//ȸ��, �̵� ���� (��ȯ)
	bool			m_bTransformUpdate;

	//�̵��ӵ�
	float			m_fMoveSpeed;
	//�̵�����(�����̵� ���� ���꿡 ���)
	D3DXVECTOR3		m_vMove;
	
	//��豸 �޽�
	LPD3DXMESH		m_SphereMesh;

	//ī�޶��� �� Ÿ��
	eVIEW_TYPE		m_eView;
	bool			m_bDrawSphere;

public:
	virtual void Initialize();
	virtual void Update();
	void Render();
	virtual void Input();
	bool Collision();
	//��豸 ����.
	VOID			InitSphereMesh();
	////��豸 �׸���
	//void DrawSphere(/*D3DXVECTOR3, float*/);
	void DrawSphere(CShader* pShader);

	bool ComputeNormalVector(LPD3DXMESH, D3DXVECTOR3&, D3DXVECTOR3&, CEntity* );
public:
	//ȸ��
	void Rotation();
	//�̵�
	virtual void Move();

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
	void SetVisiable(bool);
	void SetRotation(const eAxis_TYPE& eAxis, const float& fAngle);
	void SetViewType(const eVIEW_TYPE& eView);
	void SetDrawSphere(const bool& bDraw);

//Getter
public:
	const eRENDER_TYPE& GetRenderType() const;
	const CMesh*		GetMesh() const;
	const string&		GetName() const;
	const D3DXVECTOR3&	GetPos() const;
	const eSHADER_KEY&		GetShader() const;
	const vector<UINT>&			GetPassList()	const;
	const string&		GetTechKey() const;
	/*const*/ float			GetSize() /*const*/;
	const D3DXMATRIX&	GetMatWorld() const;
	const D3DXMATRIX&	GetMatRotation() const;
	const D3DXQUATERNION& GetRotQuaternion() const;
	const float&		GetRotationAngle(const eAxis_TYPE& eAngle) const;
	const LPD3DXMESH	GetCollider() const;

public:
	CEntity(void);
	virtual ~CEntity(void);

	/*Entity(	std::string _name, 
			eEntity_Type _type, 
			D3DXVECTOR3 _pos, 
			eMesh_Num _mesh,
			eTexture_Num _texture);
	Entity(float posX, float posY, float posZ);*/
};
