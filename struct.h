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
	D3DXMATRIX matView;
	D3DXMATRIX matProj;
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

}MESH_INFO;


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



