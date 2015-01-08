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

