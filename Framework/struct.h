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
	float		fCellSpacing;	//�� ���� ����
	float		fHeightScale;	//���� ������ �����ϴ� ��
}TERRAININFO;

typedef struct _tagKey
{
	int			iKey;		//key�� �ƽ�Ű�ڵ�
	bool		bDown;		//��~~
	bool		bPush;		//1��
	bool		bUp;		//�����ٰ� ���� ��
}KEYINFO;

