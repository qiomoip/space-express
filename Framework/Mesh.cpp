#include "Mesh.h"
#include "Device.h"


CMesh::CMesh(void)
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