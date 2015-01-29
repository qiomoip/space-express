#pragma once

#include "Singleton.h"

class CMesh;


class CResourceManager : public CSingleton<CResourceManager>
{
private:

	friend CSingleton;

	CResourceManager(void);
	~CResourceManager(void);

	map<string, CMesh*>*			m_mapMesh;
	
	//LPD3DXBUFFER					m_pD3DXMtrlBuffer ;

	LPTSTR							m_tResourceStr;

public:

	void							Init();

	void							CleanUp();

	void							Load(const eMESH_TYPE& eMeshType, const string& strMeshKey, const LPTSTR szMeshName);

	CMesh*							LoadMesh(const eMESH_TYPE& eMeshType, const string& strMeshKey, const LPTSTR _meshName = NULL);

	HRESULT							LoadTexture(CMesh* pMeshInfo);

	LPSTR							GetResourcePath(const LPSTR _str_);
	TCHAR*							GetResourcePathT(const LPTSTR _str_);

	const map<string, CMesh*>*		GetMeshList() const;

};

