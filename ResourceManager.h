#pragma once

#include "Singleton.h"


class CResourceManager : public CSingleton<CResourceManager>
{
private:

	friend CSingleton;

	CResourceManager(void);
	~CResourceManager(void);

	vector<MESH_INFO*>*				m_MeshArray;

	MESH_INFO*						m_pMesh ;
	
	LPD3DXBUFFER					m_pD3DXMtrlBuffer ;

	LPTSTR							m_tResourceStr;

public:

	void							Init();

	void							CleanUp();

	void							Load();

	HRESULT								LoadMesh(LPTSTR _meshName);

	int								LoadTexture(LPTSTR _meshName);

	LPSTR							GetResourcePath( LPSTR _str_);
	TCHAR*							GetResourcePathT( LPTSTR _str_);

	vector<MESH_INFO*>*				GetMeshArray();

};

