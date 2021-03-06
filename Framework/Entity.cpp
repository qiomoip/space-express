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
#include "TerrainMesh.h"

CEntity::CEntity(void)
	: m_pMesh(NULL)
	, m_strName("")
	, m_eRenderType(RTYPE_NONE) 
	, m_bVisiable(true)
	, m_eShader(SHADER_NONE)
	, m_strTechKey("")
	, m_bTransformUpdate(false)
	, m_fMoveSpeed(0.0f)
	, m_SphereMesh(NULL)
	, m_eMeshNum(MN_NULL)
	, m_eView(VIEW_PERSPECTIVE)
	, m_bDrawSphere(true)
{
	m_vecPass.reserve(10);
	memset(&m_vPos, 0, sizeof(D3DXVECTOR3));
	memset(m_AxisRot, 0, sizeof(D3DXQUATERNION));
	memset(m_fAngle, 0, sizeof(float) * AT_MAX);
	memset(m_vWorldAxis, 0, sizeof(D3DXVECTOR3) * AT_MAX);
	memset(m_vLocalAxis, 0, sizeof(D3DXVECTOR3) * AT_MAX);

	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matRot);
	D3DXMatrixIdentity(&m_matScale);
	D3DXMatrixIdentity(&m_matTrans);
	D3DXMatrixIdentity(&m_matScale);

	memset(&m_vMove, 0, sizeof(D3DXVECTOR3));
}


CEntity::~CEntity(void)
{
	Safe_Release(m_SphereMesh);
	std::wstring str;
	str.c_str();
}

void CEntity::Initialize()
{
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
	//m_fMoveSpeed = 7.0 * (double)_SINGLE(CDebug)->GetDeltaTime();
}

bool CEntity::Collision()
{
	list<CEntity*>*	RenderList = _SINGLE(CObjectManager)->GetRenderList();

	//두 엔티티 벡터 차
	D3DXVECTOR3 vLenth = D3DXVECTOR3(0,0,0);
	//노말 벡터
	D3DXVECTOR3 vNormal = D3DXVECTOR3(0,0,0);
	//타겟의 위치
	D3DXVECTOR3 vTarPos = D3DXVECTOR3(0,0,0);
	//충돌지점
	D3DXVECTOR3 vCol = D3DXVECTOR3(0.f, 0.f, 0.f); 
	//엔티티 크기
	float fSize = GetSize();
	float fTarSize = 0.f;
	//두 엔티티간의 길이
	float len  = 0.f;
	//엔티티의 메시
	eMESH_TYPE _eTarMesh_type = MT_NULL;
	const CMesh* _pTarMesh = NULL;
	//int i = RTYPE_ENTITY;
	for(list<CEntity*>::iterator iter = RenderList[RTYPE_ENTITY].begin();
		iter != RenderList[RTYPE_ENTITY].end(); ++iter)
	{
		//체크하려는 객체와 같은 객체라면 넘어가라
		if( (*iter)->GetName() == m_strName )
			continue;
		//대상 오브젝트의 위치
		vTarPos = (*iter)->GetPos();
		//이동 예정인 위치와 대상 오브젝트의 차벡터
		vLenth = (m_vPos + m_vMove) - vTarPos;
		//두 엔티티간의 거리
		len = D3DXVec3Length(&vLenth );
		//타겟의 사이즈 
		fTarSize = (*iter)->GetSize();
		//타겟의 메시정보
		_pTarMesh = (*iter)->GetMesh();
		//타겟의 충돌 타입
		_eTarMesh_type = _pTarMesh->GetColliderType();

#ifdef _DEBUG
			_SINGLE(CDebug)->ResetLine();
#endif
		//충돌체크
		if(  _eTarMesh_type == MT_STATIC && //구 충돌 
			(fSize + fTarSize) >= len) 
		{

			if( !ComputeNormalVector( (*iter)->GetCollider(), 
				vNormal, vCol, (*iter)) )
				continue;
			m_vPos += vNormal * m_fMoveSpeed/* * _SINGLE(CDebug)->GetDeltaTime()*/;
			m_vPos.y = 0.f;

#ifdef _DEBUG
			//법선
			_SINGLE(CDebug)->AddLine( 
				vCol, vCol + vNormal * 30.f, COLOR_ORANGE);
			//이동벡터
			_SINGLE(CDebug)->AddLine( m_vPos, m_vPos + m_vMove * 300.f, COLOR_PURPLE );
			
#endif
			//벡터의 길이도 연산에 중요한 요소기 때문에 정규화 하지 않는다.
			//D3DXVec3Normalize( &vNormal, &vNormal);
			//D3DXVec3Normalize( &m_vMove, &m_vMove);
			m_vMove -= D3DXVec3Dot( &m_vMove, &vNormal ) * vNormal ;
			//슬라이딩 벡터를 계산했으면 이 벡터를 기준으로 다시 충돌 체크
			iter = RenderList[RTYPE_ENTITY].begin();
			int static cnt = 0;
			if( cnt++ >= 10)
				break;
				
#ifdef _DEBUG
			//슬라이딩 벡터
			_SINGLE(CDebug)->AddLine( m_vPos, m_vPos + m_vMove * 3000.f, COLOR_CYAN);
#endif
		}
		//박스 충돌
		else if( _eTarMesh_type == MT_BOX &&
			fSize + fTarSize > len )
		{
			
			LPD3DXMESH pMesh = _pTarMesh->GetMesh();
			BOXSIZE size = ((CBoxMesh*)_pTarMesh)->GetMinMax();

			if( !ComputeNormalVector( pMesh, 
				vNormal, vCol, (*iter)) )
				continue;

#ifdef _DEBUG
			//법선
			_SINGLE(CDebug)->AddLine( 
				vCol, vCol + vNormal * 30.f, COLOR_ORANGE);
			//이동벡터
			_SINGLE(CDebug)->AddLine( m_vPos, m_vPos + m_vMove * 300.f, COLOR_PURPLE );
#endif
			//사각형이기 때문에 추가적인 충돌체크
			size.vMax += vTarPos;
			size.vMin += vTarPos;

#ifdef _DEBUG
			_SINGLE(CDebug)->AddPosMark( size.vMax, COLOR_MAGENTA );
			_SINGLE(CDebug)->AddPosMark( size.vMin, COLOR_MAGENTA );
#endif
			D3DXVECTOR3 vPrePos = m_vPos + m_vMove;

			if (vCol.x < size.vMin.x - fSize || 
				vCol.x > size.vMax.x + fSize ||
				vCol.z < size.vMin.z - fSize || 
				vCol.z > size.vMax.z + fSize )
				continue;
			m_vPos += vNormal * m_fMoveSpeed/* * _SINGLE(CDebug)->GetDeltaTime()*/;
			
			m_vMove -= D3DXVec3Dot( &m_vMove, &vNormal ) * vNormal ;
			m_vPos.y = 0.f;
		}

	}
	//충돌 안했으면 고고
	//m_vMove.y = 0.f;
#ifdef _DEBUG
	/*m_vMove *= _SINGLE(CDebug)->GetDeltaTime();*/
#endif
	D3DXVec3Normalize( &m_vMove, &m_vMove);
	m_vPos += m_vMove * m_fMoveSpeed;

	//지형 위로 캐릭터 얹기
	CEntity* pTerrain = _SINGLE(CObjectManager)->FindObject("MainTerrain");
	if(!pTerrain)
		return false;

	CTerrainMesh* pTerrainMesh = (CTerrainMesh*)pTerrain->GetMesh();
	
	if(!pTerrainMesh)
		return false;

	m_vPos.y = pTerrainMesh->GetHeight(m_vPos.x, m_vPos.z);

	return false;
}

void CEntity::InitSphereMesh()
{
	D3DXCreateSphere( _SINGLE(CDevice)->GetDevice(), 
		GetSize(), (UINT)16, (UINT)16, &m_SphereMesh, NULL);
}

void CEntity::DrawSphere(CShader* pShader)
{
	_SINGLE(CDevice)->GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	pShader->BeginPass(1);
	
	m_SphereMesh->DrawSubset(0);
	
	pShader->EndPass();

	_SINGLE(CDevice)->GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
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

	if ( !isHit || fDist > GetSize()  )
		return false;// 충돌이 안됬거나 거리가 멀다면 리턴;

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

	_vNormal.x = plane.a;
	_vNormal.y = plane.b;
	_vNormal.z = plane.c;
	
#ifdef _DEBUG
	//충돌지점 표시
	_SINGLE(CDebug)->AddPosMark( _vCol, COLOR_BLACK);
#endif
	
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
	//충돌체크(충돌체크후 슬라이딩 벡터 연산)
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
		if(m_pMesh->GetColliderType() == MT_UI)
		{
			SetVisiable(true);
			_SINGLE(CObjectManager)->Push_RenderList(this);
		}
		else if (_SINGLE(CFrustum)->isInFrustum( m_vPos, GetSize() ) )
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
			//축 세팅
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
	const D3DXMATRIX* pMatProj = _SINGLE(CCameraManager)->GetCurCam()->GetMatProj(m_eView);
	const D3DXMATRIX* pMatView = _SINGLE(CCameraManager)->GetCurCam()->GetMatView(m_eView);

	D3DXMATRIX matWVP = m_matWorld * (*pMatView);

	CShader* pShader = _SINGLE(CShaderManager)->FindShader(m_eShader);

	//if(m_eMeshNum == MN_ZOMBIE)
	//{
	//	m_vecPass.clear();
	//	m_vecPass.push_back(3);
	//}

	D3DXMATRIX matIden;
	D3DXMatrixIdentity(&matIden);

	pShader->SetMatrix("g_matView", pMatView);
	pShader->SetMatrix("g_matProj", pMatProj);

	pShader->SetMatrix("g_matWorld", &m_matWorld);
	
	pShader->SetMatrix("g_matIden", &matIden);

	pShader->SetMatrix("g_matWV", &matWVP);
	matWVP *= (*pMatProj);
	pShader->SetMatrix("g_matWVP", &matWVP);

	D3DMATERIAL9 tMaterial;
	tMaterial.Diffuse.a = 1.f;
	tMaterial.Diffuse.r = 1.f;
	tMaterial.Diffuse.g = 1.f;
	tMaterial.Diffuse.b = 1.f;

	tMaterial.Ambient = tMaterial.Diffuse;
	tMaterial.Specular = tMaterial.Diffuse;
	tMaterial.Power = 1.f;

	//각각의 패스에 대해 렌더
	for(unsigned int i = 0; i < m_vecPass.size(); ++i)
	{
		m_pMesh->Render(pShader, m_vecPass[i]);
	}

	pShader->SetValue("g_mtrlMesh", &tMaterial, sizeof(D3DMATERIAL9));

	if(m_bDrawSphere)
	{
		DrawSphere(pShader);
	}
/*
	_SINGLE(CDevice)->GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	
	pShader->BeginPass(1);
	
	m_SphereMesh->DrawSubset(0);
	
	pShader->EndPass();

	_SINGLE(CDevice)->GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);*/
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

void CEntity::SetViewType(const eVIEW_TYPE& eView)
{
	m_eView = eView;
}

void CEntity::SetDrawSphere(const bool& bDraw)
{
	m_bDrawSphere = bDraw;
}
