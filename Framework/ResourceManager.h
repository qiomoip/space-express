#pragma once

#include "Singleton.h"

class CMesh;
class CTexture;

class CResourceManager : public CSingleton<CResourceManager>
{
private:

	friend CSingleton;

	CResourceManager(void);
	~CResourceManager(void);

	map<eMESH_NUM, CMesh*>*			m_mapMesh;
	map<string, CTexture*>			m_mapTexture;
	
	//LPD3DXBUFFER					m_pD3DXMtrlBuffer ;

public:

	void							Init();

	void							CleanUp();

	CMesh*							Load(const eMESH_TYPE& eMeshType, const eMESH_NUM& eMeshNum, const LPTSTR szMeshName);

	CMesh*							LoadMesh(const eMESH_TYPE& eMeshType, const eMESH_NUM& eMeshNum, const LPTSTR _meshName = NULL);

	CTexture*						LoadTexture(const string& strTextureKey, const LPTSTR _texname);

	LPSTR							GetResourcePath(const LPSTR _str_);
	TCHAR*							GetResourcePathT(const LPTSTR _str_);

	const map<eMESH_NUM, CMesh*>*		GetMeshList() const;

	void							RenderInstancingData();
};

