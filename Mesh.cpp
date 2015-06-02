#include "Mesh.h"
#include "Device.h"


CMesh::CMesh(void)
	: m_arrayTexture(NULL)
	, m_ColType(MT_NULL)
{
}


CMesh::~CMesh(void)
{
	Destroy();
}

void CMesh::Destroy()
{
	Safe_Delete_Array(m_arrayTexture);
}