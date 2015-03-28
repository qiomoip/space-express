
#include "Entity.h"
#include "Mesh.h"
#include "ObjectManager.h"
#include "KeyManager.h"
#include "Device.h"
#include "Shader.h"
#include "ShaderManager.h"
#include "CameraManager.h"
#include "Camera.h"

CEntity::CEntity(void)
	: m_pMesh(NULL)
	, m_strName("")
	, m_eRenderType(RTYPE_NONE) 
	, m_bVisiable(true)
	, m_eShader(SHADER_NONE)
	, m_strTechKey("")
	, Mesh_num(MN_NULL)
{
	m_vecPass.reserve(10);
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
	/*const KEYINFO* pInfo = _SINGLE(CKeyManager)->GetKey("KEY_Entity_RotY-");
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

	//pInfo = _SINGLE(CKeyManager)->GetKey("KEY_SPACE");
	//if(pInfo->bPush)
	//{
	//	SetVisiable();
	//}
	*/
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

void CEntity::RotationY()
{
	D3DXMatrixRotationY(&m_matRot[AT_Y], m_fAngle[AT_Y]); 
}

void CEntity::Update()
{
	if(m_pMesh && m_bVisiable)
		_SINGLE(CObjectManager)->Push_RenderList(this);
}

void CEntity::Render()
{
	//_SINGLE(CDevice)->GetDevice()->SetTransform(D3DTS_WORLD, &m_matWorld);
	const D3DXMATRIX* pMatProj = _SINGLE(CCameraManager)->GetCurCam()->GetMatProj();
	const D3DXMATRIX* pMatView = _SINGLE(CCameraManager)->GetCurCam()->GetMatView();
	D3DXMATRIX matWVP = m_matWorld * (*pMatView);

	CShader* pShader = _SINGLE(CShaderManager)->FindShader(m_eShader);
	pShader->SetMatrix("g_matWV", &matWVP);
	matWVP *= (*pMatProj);
	pShader->SetMatrix("g_matWVP", &matWVP);

	//각각의 패스에 대해 렌더
	for(unsigned int i = 0; i < m_vecPass.size(); ++i)
	{
		m_pMesh->Render(pShader, i);

	}
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