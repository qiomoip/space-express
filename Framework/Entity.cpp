
#include "Entity.h"
#include "Mesh.h"
#include "ObjectManager.h"

CEntity::CEntity(void)
	: m_pMesh(NULL)
	, m_strName("")
	, m_eRenderType(RTYPE_NONE) 
{
}


CEntity::~CEntity(void)
{
}

void CEntity::Initialize()
{

}

void CEntity::Update()
{
	if(m_pMesh)
		_SINGLE(CObjectManager)->Push_RenderList(this);
}

void CEntity::Render()
{
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