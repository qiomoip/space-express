#pragma once

#include "Singleton.h"

class CResourceManager : public CSingleton<CResourceManager>
{
private:

	friend CSingleton;

	CResourceManager(void);
	~CResourceManager(void);

	vector<MESH_INFO*>*				m_MeshArray;

	vector<TEXTURE_INFO*>*			m_TextureArray;


public:

	void							Init();

	void							CleanUp();

	void							Load();
};

