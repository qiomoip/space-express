
#include "Entity.h"
#include "Mesh.h"
#include "ObjectManager.h"
#include "KeyManager.h"
#include "Device.h"
#include "Shader.h"
#include "ShaderManager.h"
#include "CameraManager.h"
#include "ObjectManager.h"
#include "Camera.h"
#include "Frustum.h"
#include "Debug.h"
#include "StaticMesh.h"
#include "BoxMesh.h"

CEntity::CEntity(void)
	: m_pMesh(NULL)
	, m_strName("")
	, m_eRenderType(RTYPE_NONE) 
	, m_bVisiable(true)
	, m_eShader(SHADER_NONE)
	, m_strTechKey("")
	, m_bTransformUpdate(false)
	, m_fMoveSpeed(0.01f)
	, m_SphereMesh(NULL)
{
	m_vecPass.reserve(10);
	memset(&m_vPos, 0, sizeof(D3DXVECTOR3));
}


CEntity::~CEntity(void)
{
	Safe_Release(m_SphereMesh);
	std::wstring str;
	str.c_str();
}

void CEntity::Initialize()
{
	memset(&m_vPos, 0, sizeof(D3DXVECTOR3));
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matRot);
	D3DXMatrixIdentity(&m_matScale);
	D3DXMatrixIdentity(&m_matTrans);
	memset(m_fAngle, 0, sizeof(float) * AT_MAX);

	D3DXMatrixIdentity(&m_matScale);

	memset(m_AxisRot, 0, sizeof(D3DXQUATERNION));

	for(int i = 0; i < AT_MAX; ++i)
	{
		m_fScale[i] = 1.f;
	}

	m_vLocalAxis[AT_X] = D3DXVECTOR3(1.f, 0.f, 0.f);
	m_vLocalAxis[AT_Y] = D3DXVECTOR3(0.f, 1.f, 0.f);
	m_vLocalAxis[AT_Z] = D3DXVECTOR3(0.f, 0.f, 1.f);

	memcpy(m_vWorldAxis, m_vLocalAxis, sizeof(D3DXVECTOR3) * AT_MAX);
}

void CEntity::Input()
{

}

bool CEntity::Collision()
{
	list<CEntity*>*	RenderList = _SINGLE(CObjectManager)->GetRenderList();

	//�� ��ƼƼ ���� ��
	D3DXVECTOR3 vLenth = D3DXVECTOR3(0,0,0);
	//�븻 ����
	D3DXVECTOR3 vNormal = D3DXVECTOR3(0,0,0);
	//Ÿ���� ��ġ
	D3DXVECTOR3 vTarPos = D3DXVECTOR3(0,0,0);

	//�浹����
	D3DXVECTOR3 pCol = D3DXVECTOR3(0.f, 0.f, 0.f); 
	//��ƼƼ ũ��
	float fSize = GetSize();
	float fTarSize = 0.f;
	//�� ��ƼƼ���� ����
	float len  = 0.f;
	//��ƼƼ�� �޽�
	eMESH_TYPE _eTarMesh_type = MT_NULL;
	
	//int i = RTYPE_ENTITY;
	for(list<CEntity*>::iterator iter = RenderList[RTYPE_ENTITY].begin();
		iter != RenderList[RTYPE_ENTITY].end(); ++iter)
	{
		//üũ�Ϸ��� ��ü�� ���� ��ü��� �Ѿ��
		if( (*iter)->GetName() == m_strName )
			continue;
		vTarPos = (*iter)->GetPos();
		//�̵� ������ ��ġ�� ������Ʈ�� ������
		vLenth = (m_vPos + m_vMove) - vTarPos;
		//��ƼƼ���� �Ÿ�
		len = D3DXVec3Length(&vLenth );
		//Ÿ���� ������ 
		fTarSize = (*iter)->GetSize();
		//Ÿ���� �޽�����
		const CMesh* _pTarMesh = (*iter)->GetMesh();
		//Ÿ���� �浹 Ÿ��
		_eTarMesh_type = _pTarMesh->GetColliderType();

		//�浹üũ
		if(  _eTarMesh_type == MT_STATIC && //�� �浹 
			2.f * (fSize + fTarSize) >= len) 
		{
#ifdef _DEBUG
			_SINGLE(CDebug)->ResetLine();
#endif
			if( !ComputeNormalVector( (*iter)->GetCollider(), 
				vNormal, pCol, (*iter)) )
				continue;
			m_vPos += vNormal * m_fMoveSpeed;
			m_vPos.y = 0.f;
#ifdef _DEBUG
			//����
			_SINGLE(CDebug)->AddLine( 
				pCol, pCol + vNormal * 30.f, COLOR_ORANGE);
			//�̵�����
			_SINGLE(CDebug)->AddLine( m_vPos, m_vPos + m_vMove * 300.f, COLOR_PURPLE );
			
#endif
			//������ ���̵� ���꿡 �߿��� ��ұ� ������ ����ȭ ���� �ʴ´�.
			//D3DXVec3Normalize( &vNormal, &vNormal);
			//D3DXVec3Normalize( &m_vMove, &m_vMove);
			
			m_vMove -= D3DXVec3Dot( &m_vMove, &vNormal ) * vNormal ;
			//m_vMove *= 0.9f;
			//�����̵� ���͸� ��������� �� ���͸� �������� �ٽ� �浹 üũ
							
			iter = RenderList[RTYPE_ENTITY].begin();

#ifdef _DEBUG
			//�����̵� ����
			_SINGLE(CDebug)->AddLine( m_vPos, m_vPos + m_vMove * 300.f, COLOR_BLACK);
			float length = D3DXVec3Length( &m_vMove );
			int a = 0;
			TCHAR slide[255] ;
			_SINGLE(CDebug)->VectorToString(slide, m_vMove);
			_SINGLE(CDebug)->AddLog(-1, slide);
#endif
		}
		//�ڽ� �浹
		else if( _eTarMesh_type == MT_BOX &&
			fSize + fTarSize > len )
		{
			LPD3DXMESH pMesh = _pTarMesh->GetMesh();
			BOXSIZE size = ((CBoxMesh*)_pTarMesh)->GetMinMax();
			size.vMax *= fTarSize ;
			size.vMin *= fTarSize ;

			size.vMax += vTarPos;
			size.vMin += vTarPos;

			float a, b;
			b = 0.2f;
			a = 0.1f;

			D3DXVECTOR3 vPrePos = m_vPos + m_vMove;
			if (vPrePos.x < size.vMin.x - fSize || 
				vPrePos.x > size.vMax.x + fSize ||
				vPrePos.z < size.vMin.z - fSize || 
				vPrePos.z > size.vMax.z + fSize )
				continue;
			else 
				m_vMove = D3DXVECTOR3(0,0,0);
			/*
			//�븻 ���� ���ϱ�
			ComputeNormalVector( 
				pMesh, vNormal, pCol, (*iter));
					
			//LPDIRECT3DVERTEXBUFFER9 pVB; 
			//LPDIRECT3DINDEXBUFFER9 pIB; 
			//pMesh->GetVertexBuffer(&pVB); 
			//pMesh->GetIndexBuffer( &pIB ); 
			//WORD* pIndices; 
			//D3DVERTEX* pVertices; 
			//pIB->Lock( 0, 0, (void**)&pIndices, 0 ); 
			//pVB->Lock( 0, 0,(void**)&pVertices, 0); 
			//D3DXVECTOR3 v0 = pVertices[pIndices[3*dwFaceIndex+0]].vPos; 
			//D3DXVECTOR3 v1 = pVertices[pIndices[3*dwFaceIndex+1]].vPos; 
			//D3DXVECTOR3 v2 = pVertices[pIndices[3*dwFaceIndex+2]].vPos; 
			//D3DXVECTOR3 u = v1 - v0 ; 
			//D3DXVECTOR3 v = v2 - v0; 
			//D3DXVECTOR3 out; 
			//D3DXVec3Cross( &out, &u, &v ); 
			//D3DXVec3Normalize( &out, &out ); 
			////out *= m_fMoveSpeed;
			//pVB->Unlock(); 
			//pIB->Unlock(); 
			//Safe_Release(pVB); 
			//Safe_Release(pIB); 
			
			//�浹 üũ�� ���� 4���� ��
			D3DXPLANE plane[4];
			D3DXVECTOR3 vtx[8];
			memset(vtx, 0, sizeof(vtx[0]) * 8 );
			memset(plane, 0 , sizeof(plane[0]) * 4 );

			vtx[0] = size.vMin;
			vtx[1] = size.vMin;
			vtx[1].z = size.vMax.z;
			vtx[2] = size.vMin;
			vtx[2].x = size.vMax.x;
			vtx[3] = size.vMax;
			vtx[3].y = size.vMin.y;
			vtx[4] = size.vMin;
			vtx[4].y = size.vMax.y;
			vtx[5] = size.vMax;
			vtx[5].x = size.vMin.x;
			vtx[6] = size.vMax;
			vtx[6].z = size.vMin.z;
			vtx[7] = size.vMax;

			for(int i = 0; i < 8; ++i)
				vtx[i] += vTarPos;
			//�׸��� ������ �ð����.
			D3DXPlaneFromPoints(&plane[0], &vtx[2], &vtx[4], &vtx[0]);//����
			D3DXPlaneFromPoints(&plane[1], &vtx[3], &vtx[7], &vtx[2]);//����
			D3DXPlaneFromPoints(&plane[2], &vtx[4], &vtx[1], &vtx[0]);//����
			D3DXPlaneFromPoints(&plane[3], &vtx[1], &vtx[7], &vtx[3]);//�޸�
			float fDist = 0.f;
			int inCount = 0;
			bool isInBox = true;
			for( int i  = 0; i< 4; ++i)
			{
				fDist = D3DXPlaneDotCoord( &plane[i], &(pCol + vTarPos) );

				if( fDist > fSize )
				{
					isInBox = false ;//�浹 �ƴ�
					break;
				}
				else
					isInBox = true;

			}
			//�̵�����
			_SINGLE(CDebug)->AddLine( m_vPos, m_vPos + m_vMove * 3000.f, COLOR_PURPLE );
			_SINGLE(CDebug)->AddLine( 
				pCol, pCol + vNormal * 3000.f, COLOR_ORANGE);
			//�浹;
			if( isInBox )
				m_vMove -= D3DXVec3Dot( &m_vMove, &vNormal ) * vNormal ;
			//�����̵� ����
			_SINGLE(CDebug)->AddLine( m_vPos, m_vPos + m_vMove * 3000.f, COLOR_BLACK);
			*/
		}

	}
	//�浹 �������� ���
	m_vMove.y = 0.f;
	m_vPos += m_vMove;

	return false;
}

void CEntity::InitSphereMesh()
{
	D3DXCreateSphere( _SINGLE(CDevice)->GetDevice(), 
		GetSize(), (UINT)16, (UINT)16, &m_SphereMesh, NULL);
}

void CEntity::DrawSphere(/*D3DXVECTOR3 _vPos, float _size*/)
{
	m_SphereMesh->DrawSubset(0);
}

bool CEntity::ComputeNormalVector(
	LPD3DXMESH _pMesh, D3DXVECTOR3& _vNormal, D3DXVECTOR3& _vCol, CEntity* target)
{
	BOOL isHit = false;
	DWORD dwFaceIndex = 0;
	float fDist = 0;
	LPD3DXBUFFER ppAllhit;
	DWORD pCountOfHits;
	
	D3DXVECTOR3 vPos = m_vPos - target->GetPos();
	D3DXVECTOR3 vtar = (-vPos);
	D3DXVec3Normalize( &vtar, &vtar);

	D3DXIntersect( _pMesh, &vPos, &vtar, &isHit, 
		&dwFaceIndex, NULL, NULL, &fDist, &ppAllhit, &pCountOfHits );

	if ( !isHit || fDist > GetSize() )
		return false;// �浹�� �ȉ�ų� �Ÿ��� �ִٸ� ����;

	LPDIRECT3DVERTEXBUFFER9 pVB; 
	LPDIRECT3DINDEXBUFFER9 pIB; 

	_pMesh->GetVertexBuffer(&pVB); 
	_pMesh->GetIndexBuffer( &pIB ); 

	WORD* pIndices; 
	D3DVERTEX* pVertices; 

	pIB->Lock( 0, 0, (void**)&pIndices, 0 ); 
	pVB->Lock( 0, 0,(void**)&pVertices, 0); 

	D3DXVECTOR3 v0 = pVertices[pIndices[3*dwFaceIndex+0]].vPos; 
	D3DXVECTOR3 v1 = pVertices[pIndices[3*dwFaceIndex+1]].vPos; 
	D3DXVECTOR3 v2 = pVertices[pIndices[3*dwFaceIndex+2]].vPos; 
	
	D3DXPLANE plane;
	
	D3DXPlaneFromPoints( &plane, &v0, &v1, &v2);
	
	_vCol = (v0 + v1 + v2)/3.f;
	_vCol += target->GetPos();
	/*D3DXVECTOR3 u = v0 - v1; 
	D3DXVECTOR3 v = v0 - v2; 
	D3DXVec3Normalize( &u, &u);
	D3DXVec3Normalize( &v, &v);
	D3DXVec3Cross( &_vNormal, &u, &v ); */

	_vNormal.x = plane.a;
	_vNormal.y = plane.b;
	_vNormal.z = plane.c;
	
#ifdef _DEBUG
	_SINGLE(CDebug)->AddLine( 
		target->GetPos(), target->GetPos() + _vNormal* 30.f, COLOR_WHITE);

	D3DXVECTOR3 Col1 = D3DXVECTOR3(3.f, 0, 0);
	D3DXVECTOR3 Col2 = D3DXVECTOR3(0, 0, 3.f);
	
	_SINGLE(CDebug)->AddLine( 
		_vCol+Col1, _vCol-Col1, COLOR_BLACK);
	_SINGLE(CDebug)->AddLine( 
		_vCol+Col2, _vCol-Col2, COLOR_BLACK);
#endif
	//D3DXVec3Normalize( &_vCol, &_vCol);
	D3DXVec3Normalize( &_vNormal , &_vNormal); 
	pVB->Unlock(); 
	pIB->Unlock(); 
	Safe_Release(pVB); 
	Safe_Release(pIB); 

	return true;
}


void CEntity::Rotation()
{
	D3DXQuaternionRotationYawPitchRoll(&m_AxisRot, m_fAngle[AT_Y], m_fAngle[AT_X], m_fAngle[AT_Z]);
	D3DXMatrixRotationQuaternion(&m_matRot, &m_AxisRot);
}

void CEntity::Move()
{
	//�浹üũ(�浹üũ�� �����̵� ���� ����)
	Collision();
}


void CEntity::SetScale(const float& fScaleX, const float& fScaleY, const float& fScaleZ)
{
	m_fScale[AT_X] = fScaleX;
	m_fScale[AT_Y] = fScaleY;
	m_fScale[AT_Z] = fScaleZ;

	for(int i = 0 ; i < AT_MAX; ++i)
		m_matScale(i, i) = m_fScale[i];
}

void CEntity::SetTechKey(const string& strTechKey)
{
	m_strTechKey = strTechKey;
}

void CEntity::SetPass(const UINT& uPass)
{
	m_vecPass.push_back(uPass);
}

void CEntity::SetShader(const eSHADER_KEY& pShader)
{
	m_eShader = pShader;
}

void CEntity::Update()
{
	if(m_pMesh )
	{
		if (_SINGLE(CFrustum)->isInFrustum( m_vPos, GetSize() ) )
		{
			SetVisiable(true);
			_SINGLE(CObjectManager)->Push_RenderList(this);
		}
		else 
			SetVisiable(false);
	}
	memcpy(&m_matTrans._41, &m_vPos, sizeof(D3DXVECTOR3));

	if(m_bTransformUpdate)
	{
		Rotation();
		Move();
		for(int i = 0; i < AT_MAX; ++i)
		{
			//�� ����
			D3DXVec3TransformNormal(&m_vWorldAxis[i], &m_vLocalAxis[i], &m_matRot);
			D3DXVec3Normalize(&m_vWorldAxis[i], &m_vWorldAxis[i]);
		}

		m_bTransformUpdate = false;
	}
}

void CEntity::Render()
{
	//_SINGLE(CDevice)->GetDevice()->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_matWorld = m_matScale * m_matRot * m_matTrans;
	const D3DXMATRIX* pMatProj = _SINGLE(CCameraManager)->GetCurCam()->GetMatProj();
	const D3DXMATRIX* pMatView = _SINGLE(CCameraManager)->GetCurCam()->GetMatView();

	D3DXMATRIX matWVP = m_matWorld * (*pMatView);

	CShader* pShader = _SINGLE(CShaderManager)->FindShader(m_eShader);
	pShader->SetMatrix("g_matWV", &matWVP);
	matWVP *= (*pMatProj);
	pShader->SetMatrix("g_matWVP", &matWVP);

	//������ �н��� ���� ����
	for(unsigned int i = 0; i < m_vecPass.size(); ++i)
	{
		m_pMesh->Render(pShader, m_vecPass[i]);
	}
	_SINGLE(CDevice)->GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_SphereMesh->DrawSubset(0);
//	_SINGLE(CDevice)->GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

void CEntity::SetRenderType(const eRENDER_TYPE& eRender)
{
	m_eRenderType = eRender;
}

void CEntity::PushMesh(CMesh* pMesh)
{
	m_pMesh = pMesh;
}

void CEntity::SetName(const string& strName)
{
	m_strName = strName;
}

void CEntity::SetPos(const D3DXVECTOR3& vPos)
{
	m_vPos = vPos;
}

void CEntity::SetVisiable()
{
	m_bVisiable = !m_bVisiable;
}
void CEntity::SetVisiable(bool _visiable)
{
	m_bVisiable = _visiable;
}

void CEntity::SetRotation(const eAxis_TYPE& eAxis, const float& fAngle)
{
	m_fAngle[eAxis] = fAngle;

	m_bTransformUpdate = true;
}


const eRENDER_TYPE& CEntity::GetRenderType() const
{
	return m_eRenderType;
}

const CMesh* CEntity::GetMesh() const
{
	return m_pMesh;
}

const string&		CEntity::GetName() const
{
	return m_strName;
}

const D3DXVECTOR3&	CEntity::GetPos() const
{
	return m_vPos;
}

const eSHADER_KEY&		CEntity::GetShader() const
{
	return m_eShader;
}

const vector<UINT>&			CEntity::GetPassList()	const
{
	return m_vecPass;
}

const string&		CEntity::GetTechKey() const
{
	return m_strTechKey;
}

/*const */float	CEntity::GetSize() /*const*/
{
	float fMax = m_fScale[AT_X] > m_fScale[AT_Y] ? m_fScale[AT_X] : m_fScale[AT_Y];
	fMax = fMax > m_fScale[AT_Z] ? fMax : m_fScale[AT_Z];
	return m_pMesh->GetSize() * fMax;
}

const D3DXMATRIX&	CEntity::GetMatWorld() const
{
	return m_matWorld;
}

const D3DXMATRIX&	CEntity::GetMatRotation() const
{
	return m_matRot;
}

const D3DXQUATERNION& CEntity::GetRotQuaternion() const
{
	return m_AxisRot;
}

const float&		CEntity::GetRotationAngle(const eAxis_TYPE& eAngle) const
{
	return m_fAngle[eAngle];
}

const LPD3DXMESH CEntity::GetCollider() const
{
	return m_SphereMesh;
}
