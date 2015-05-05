
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
	//��ƼƼ ũ��
	float size = GetSize();
	//�� ��ƼƼ���� ����
	float len  = 0.f;
	
	static int cnt = 0;
	//int i = RTYPE_ENTITY;
	for(list<CEntity*>::iterator iter = RenderList[RTYPE_ENTITY].begin();
		iter != RenderList[RTYPE_ENTITY].end(); ++iter)
	{
		//üũ�Ϸ��� ��ü�� ���� ��ü��� �Ѿ��
		if( (*iter)->GetName() == m_strName )
			continue;
		//�̵� ������ ��ġ�� ������Ʈ�� ������
		vLenth = (m_vPos + m_vMove) - (*iter)->GetPos();
		//������ ���� ���
		len = D3DXVec3Length(&vLenth );
		//�浹üũ
		if( size + (*iter)->GetSize() >= len ) 
		{
			BOOL isHit = false;
			DWORD dwFaceIndex = 0;
			float fDist = 0;
			LPD3DXBUFFER ppAllhit;
			DWORD pCountOfHits;
			//LPD3DXMESH pMesh = ((CStaticMesh*)(*iter)->GetMesh())->GetMesh();
			_SINGLE(CDevice)->GetDevice()->SetFVF( m_SphereMesh->GetFVF() );

			if( S_OK != D3DXIntersect( 
					m_SphereMesh,
					&m_vPos, &m_vMove, &isHit, &dwFaceIndex , NULL,
					NULL, &fDist, &ppAllhit, &pCountOfHits ) )
				assert(false);
			LPDIRECT3DVERTEXBUFFER9 pVB; 
			LPDIRECT3DINDEXBUFFER9 pIB; 

			m_SphereMesh->GetVertexBuffer(&pVB); 
			m_SphereMesh->GetIndexBuffer( &pIB ); 

			WORD* pIndices; 
			D3DVERTEX* pVertices; 

			pIB->Lock( 0, 0, (void**)&pIndices, 0 ); 
			pVB->Lock( 0, 0,(void**)&pVertices, 0); 

			D3DXVECTOR3 v0 = pVertices[pIndices[3*dwFaceIndex+0]].vPos; 
			D3DXVECTOR3 v1 = pVertices[pIndices[3*dwFaceIndex+1]].vPos; 
			D3DXVECTOR3 v2 = pVertices[pIndices[3*dwFaceIndex+2]].vPos; 

			D3DXVECTOR3 u = v1 - v0; 
			D3DXVECTOR3 v = v2 - v0; 

			D3DXVECTOR3 out; 

			D3DXVec3Cross( &out, &u, &v ); 
			D3DXVec3Normalize( &out, &out ); 
			//out *= m_fMoveSpeed;
			pVB->Unlock(); 
			pIB->Unlock(); 
			Safe_Release(pVB); 
			Safe_Release(pIB); 
			out.y = 0.f;

			//vLenth���͸� ���� ����ó�� ����ϴ� ����
			vLenth = m_vPos - (*iter)->GetPos();
			
			D3DXVec3Normalize( &vLenth, &vLenth);
			D3DXVec3Normalize( &m_vMove, &m_vMove);

			//�����̵� ���� ����(vLenth�� ���� ���ͷ� ����)
			m_vMove -= D3DXVec3Dot( &m_vMove, &vLenth) * vLenth;
			//������ ������ ������ ���̸� �̵��ӵ��� ����.
			D3DXVec3Normalize( &m_vMove, &m_vMove);
			m_vMove *= m_fMoveSpeed;
			
			//�����̵� ���͸� ��������� �� ���͸� �������� �ٽ� �浹 üũ
			iter = RenderList[RTYPE_ENTITY].begin();
			//�浹������ �����̵� ���� ���
			//return true;
			_SINGLE(CDebug)->AddLog(6, _T("�浹���� %d�� ����"), ++cnt);
			
		}
	}
	cnt = 0;
	//�浹 �������� ���
	m_vPos += m_vMove;

	return false;
}

void CEntity::InitSphereMesh()
{
	D3DXCreateSphere( _SINGLE(CDevice)->GetDevice(), 
		GetSize(), (UINT)8, (UINT)8, &m_SphereMesh, NULL);
}

void CEntity::DrawSphere(/*D3DXVECTOR3 _vPos, float _size*/)
{
	m_SphereMesh->DrawSubset(0);
}

void CEntity::Rotation()
{
	D3DXQuaternionRotationYawPitchRoll(&m_AxisRot, m_fAngle[AT_X], m_fAngle[AT_Y], m_fAngle[AT_Z]);
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
	m_SphereMesh->DrawSubset(0);
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
	return m_pMesh->GetSize();
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
