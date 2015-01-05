#pragma once

#include "Singleton.h"
#include "define.h"
#include "Entity.h"
#include "Mesh.h"
#include "Texture.h"

class CResourceManager : CSingleton<CResourceManager>
{
private:

	friend CSingleton;
	
	CResourceManager(void);
	~CResourceManager(void);

	vector<CMesh*>*				m_Mesh;
	vector<CTexture*>*			m_Texture;
public:

	
};

