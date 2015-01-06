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
	D3DXVECTOR2 vTex;
}VERTEXTERRAIN;

#define VTXTERRAINFVF	D3DFVF_XYZ | D3DFVF_TEX1

/*
Index Format
*/

typedef struct _tagIndex
{

}INDEX;

#define INDEXFVF	

/*
Data Info
*/

typedef struct _tagTerrainInfo
{
	
	int			m_iRow;
	int			m_iCol;
	int			m_iVtxNum;
	int			m_iCellSpacing;	//셀 간의 간격
	float		m_fHeightScale;	//높이 배율을 조정하는 값
}TERRAININFO;

