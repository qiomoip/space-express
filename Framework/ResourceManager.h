#pragma once

#include "Singleton.h"


class CResourceManager : public CSingleton<CResourceManager>
{
private:

	friend CSingleton;

	CResourceManager(void);
	~CResourceManager(void);

	vector<MESH_INFO*>*				m_MeshArray;
	
	LPD3DXBUFFER					m_pD3DXMtrlBuffer ;

	LPTSTR							m_tResourceStr;

public:

	void							Init();

	void							CleanUp();

	void							Load();

	MESH_INFO*						LoadMesh(const eMESH_TYPE& eMeshType, const LPTSTR _meshName = NULL);

	HRESULT							LoadTexture(MESH_INFO* pMeshInfo);

	LPSTR							GetResourcePath(const LPSTR _str_);
	TCHAR*							GetResourcePathT(const LPTSTR _str_);

	vector<MESH_INFO*>*				GetMeshArray();

};

