
#include "Entity.h"
#include "Mesh.h"
#include "ObjectManager.h"
#include "KeyManager.h"
#include "Device.h"

CEntity::CEntity(void)
	: m_pMesh(NULL)
	, m_strName("")
	, m_eRenderType(RTYPE_NONE) 
{
	memset(&m_vPos, 0, sizeof(D3DXVECTOR3));
}


CEntity::~CEntity(void)
{
}

void CEntity::Initialize()
{
	memset(&m_vPos, 0, sizeof(D3DXVECTOR3));
	D3DXMatrixIdentity(&m_matWorld);
	memset(m_fAngle, 0, sizeof(float) * AT_MAX);
	
	D3DXMatrixIdentity(&m_matScale);
	
	for(int i = 0; i < AT_MAX; ++i)
	{
		D3DXMatrixIdentity(&m_matRot[i]);
		m_fScale[i] = 1.f;
	}
}

void CEntity::Input()
{
	const KEYINFO* pInfo = _SINGLE(CKeyManager)->GetKey("KEY_Entity_RotY-");
	if(pInfo->bPush || pInfo->bDown)
	{
		m_fAngle[AT_Y] += D3DX_PI * 0.01f;
		RotationY();
	}

	pInfo = _SINGLE(CKeyManager)->GetKey("KEY_Entity_RotY+");
	if(pInfo->bPush || pInfo->bDown)
	{
		m_fAngle[AT_Y] -= D3DX_PI * 0.01f;
		RotationY();
	}
	
}

void CEntity::SetScale(const float& fScaleX, const float& fScaleY, const float& fScaleZ)
{
	m_fScale[AT_X] = fScaleX;
	m_fScale[AT_Y] = fScaleY;
	m_fScale[AT_Z] = fScaleZ;

	for(int i = 0 ; i < AT_MAX; ++i)
		m_matScale(i, i) = m_fScale[i];
}

void CEntity::RotationY()
{
	D3DXMatrixRotationY(&m_matRot[AT_Y], m_fAngle[AT_Y]); 
}

void CEntity::Update()
{
	if(m_pMesh)
		_SINGLE(CObjectManager)->Push_RenderList(this);
}

void CEntity::Render()
{
	_SINGLE(CDevice)->GetDevice()->SetTransform(D3DTS_WORLD, &m_matWorld);
	m_pMesh->Render();
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