
#include "Entity.h"
#include "Mesh.h"
#include "ObjectManager.h"

CEntity::CEntity(void)
	: m_pMesh(NULL)
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

const eRENDER_TYPE& CEntity::GetRenderType() const
{
	return m_eRenderType;
}

const CMesh* CEntity::GetMesh() const
{
	return m_pMesh;
}