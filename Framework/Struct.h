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
   DWORD      dwColor;
}VERTEXCOLOR;

#define   VTXCOLORFVF   D3DFVF_XYZ | D3DFVF_DIFFUSE

typedef struct _tagTerrainVertex
{
   D3DXVECTOR3 vPos;
   D3DXVECTOR2 vTex;
}VERTEXTERRAIN;

#define VTXTERRAINFVF   D3DFVF_XYZ | D3DFVF_TEX1

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
   
   int			m_iRow;
   int			m_iCol;
   int			m_iVtxNum;
   int			m_iCellSpacing;   //셀 간의 간격
   float		m_fHeightScale;   //높이 배율을 조정하는 값
}TERRAININFO;

/*
Mesh Info
*/

typedef struct _tagMeshInfo
{
	LPD3DXMESH			pMesh ; // Our mesh object in sysmem
	D3DMATERIAL9*		pMaterials ; // Materials for our mesh
	DWORD				dwNumMaterials ;   // Number of mesh materials
}MESH_INFO;


typedef struct _tagTextureInfo
{
	LPDIRECT3DTEXTURE9*	pTextures ; // Textures for our mesh

}TEXTURE_INFO;



typedef struct _tagKeyInfo
{
	int		keyCode;
	bool	isPressed;

	_tagKeyInfo(int _keycode){
		keyCode = _keycode;
		isPressed = false;
	}
}KEY_INFO;