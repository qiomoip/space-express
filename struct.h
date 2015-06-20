#pragma once

/*
struct
*/


/*
Vertex Format
*/
typedef struct _tagVertex
{
	D3DXVECTOR3 vPos;
	DWORD		dwColor;
}VERTEXCOLOR;

#define	VTXCOLORFVF	D3DFVF_XYZ | D3DFVF_DIFFUSE


typedef struct _tagSphereVertex
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vNormal;
}D3DVERTEX;

#define D3DVERTEXFVF	D3DFVF_XYZ | D3DFVF_NORMAL 

typedef struct _tagTerrainVertex
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vNormal;
	D3DXVECTOR2 vTex;
}VERTEXTERRAIN;

#define VTXTERRAINFVF	D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1

/*
Index Format
*/

typedef struct _tagIndex
{
	WORD _0, _1, _2;
	_tagIndex(WORD i, WORD j, WORD k)
	{
		_0 = i;
		_1 = j;
		_2 = k;
	}
}INDEX;


/*
Data Info
*/

typedef struct _tagTerrainInfo
{
	
	int			iRow;
	int			iCol;
	int			iVtxNum;
	float		fCellSpacing;	//셀 간의 간격
	float		fHeightScale;	//높이 배율을 조정하는 값
}TERRAININFO;

typedef struct _tagKey
{
	int			iKey;		//key의 아스키코드
	bool		bDown;		//꾹~~
	bool		bPush;		//1번
	bool		bUp;		//눌렀다가 뗐을 때
}KEYINFO;

typedef struct _tagCamera
{
	D3DXMATRIX matView[VIEW_MAX];
	D3DXMATRIX matProj[VIEW_MAX];
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vLook;
	D3DXVECTOR3 vUp;
	D3DXVECTOR3 vRight;
	int		iDir[AT_MAX];
	int		iAngle[AT_MAX];
	D3DXQUATERNION	qAngle;
	float	fSmoothRotate;
	float	fSmoothMove;
}CAMERA;

/*
Mesh Info
*/
typedef struct _tagMeshInfo
{
	LPTSTR				pName;
	LPD3DXMESH			pMesh ; // Our mesh object in sysmem
	D3DMATERIAL9*		pMaterials ; // Materials for our mesh
	//LPDIRECT3DTEXTURE9*	pTextures ; // Textures for our mesh
	DWORD				dwNumMaterials ;   // Number of mesh materials
	//메시 사이즈
	float				fSize;
}MESH_INFO;

typedef struct _tagTextureVertex
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR2 vTex;
}VTXTEXTURE;

#define VTXTEXTUREFVF	D3DFVF_XYZ | D3DFVF_TEX1

typedef struct _tagTextureInfo
{
	LPDIRECT3DTEXTURE9*	pTextures ; // Textures for our mesh

}TEXTURE_INFO;


// Filename을 TCHAR형으로 변경한 D3DXMATERIAL 메테리얼 구조체
typedef struct _tagD3dMaterial
{
	D3DMATERIAL9	MatD3D;
	LPTSTR			pTextureFilename;
}_TD3DXMATERIAL;

typedef struct _tagLightInfo
{
	D3DXVECTOR4		vDiffuse;
	D3DXVECTOR4		vEmbient;
	D3DXVECTOR4		vSpecular;
	float			fPower;
}LIGHTINFO, *PLIGHTINFO;



typedef struct _tagBoxSize
{
	D3DXVECTOR3 vMin;
	D3DXVECTOR3 vMax;
}BOXSIZE;

static D3DVERTEXELEMENT9	g_tTotalFmt[]	=
{
	{0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
	{0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
	{0, 24, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0},
	{0, 36, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
	{1, 0, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 1},
	{1, 16, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 2},
	{1, 32, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 3},
	{1, 48, D3DDECLTYPE_FLOAT4, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 4},
	D3DDECL_END()
};

typedef struct _tagInstancingData 
{
	D3DXVECTOR4	vRow1;
	D3DXVECTOR4	vRow2;
	D3DXVECTOR4	vRow3;
	D3DXVECTOR4	vRow4;
}InstancingData, *PInstancingData;

typedef struct _tagRay
{
	D3DXVECTOR3 vOrigin;
	D3DXVECTOR3 vDir;
	D3DXVECTOR3 vIntersectPos;
}RAY;

typedef struct _tagTimeInfo
{
	double m_CurrentTime;
	double m_DeltaTime ;
	double m_ElapsedTime ;
	double m_PreviousTime;

}TIME_INFO;