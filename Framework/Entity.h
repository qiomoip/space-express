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
protected:
	std::string		m_strName;
	CMesh*			m_pMesh;
	eRENDER_TYPE	m_eRenderType;
	//위치
	D3DXVECTOR3		m_vPos;
	//월드 축
	D3DXVECTOR3		m_vWorldAxis[AT_MAX];
	//로컬 축
	D3DXVECTOR3		m_vLocalAxis[AT_MAX];
	//회전 행렬
	D3DXMATRIX		m_matRot;
	//이동 행렬
	D3DXMATRIX		m_matTrans;
	//월드 행렬
	D3DXMATRIX		m_matWorld;
	//회전각
	float			m_fAngle[AT_MAX];
	//크기변환 행렬
	D3DXMATRIX		m_matScale;
	//??
	D3DXQUATERNION	m_AxisRot;
	//크기 값
	float			m_fScale[AT_MAX];
	//그리기 여부 판정
	bool			m_bVisiable;
	//쉐이더 키 (default: none, all : default)
	eSHADER_KEY		m_eShader;
	//테크닉 키
	string			m_strTechKey;
	//패스 리스트
	vector<UINT>	m_vecPass;
	//회전, 이동 여부 (변환)
	bool			m_bTransformUpdate;

	//이동속도
	float			m_fMoveSpeed;
	//이동벡터(슬라이딩 벡터 연산에 사용)
	D3DXVECTOR3		m_vMove;
	
	//경계구 메시
	LPD3DXMESH		m_SphereMesh;

public:
	virtual void Initialize();
	virtual void Update();
	void Render();
	virtual void Input();
	bool Collision();
	//경계구 생성.
	VOID			InitSphereMesh();
	//경계구 그리기
	void DrawSphere(/*D3DXVECTOR3, float*/);
public:
	//회전
	void Rotation();
	//이동
	void Move();

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

