#include "define.h"
#include "QuadTree.h"
//#include "ZFLog.h"

// ���� ��Ʈ��� ������
CQuadTree::CQuadTree( int cx, int cy )
{
	int		i;
	m_nCenter = 0;
	for( i = 0 ; i < 4 ; i++ )
	{
		m_pChild[i] = NULL;
	}

	// ��Ʈ����� 4�� �ڳʰ� ����
	m_nCorner[CORNER_BL]	= 0;
	m_nCorner[CORNER_BR]	= cx - 1;
	m_nCorner[CORNER_TL]	= cx * ( cy - 1 );
	m_nCorner[CORNER_TR]	= cx * cy - 1;
	m_nCenter				= ( m_nCorner[CORNER_TL] + m_nCorner[CORNER_TR] + 
								m_nCorner[CORNER_BL] + m_nCorner[CORNER_BR] ) / 4;

	m_fRadius = 0.0f;
	m_bCulled = FALSE;
	m_fRadius = 0.0f;
}

// ���� �ڽĳ�� ������
CQuadTree::CQuadTree( CQuadTree* pParent )
{
	int		i;
	m_nCenter = 0;
	for( i = 0 ; i < 4 ; i++ )
	{
		m_pChild[i] = NULL;
		m_nCorner[i] = 0;
	}

	m_bCulled = FALSE;
	m_fRadius = 0.0f;
}

// �Ҹ���
CQuadTree::~CQuadTree()
{
	_Destroy();
}

// �޸𸮿��� ����Ʈ���� �����Ѵ�.
void	CQuadTree::_Destroy()
{
	// �ڽ� ������ �Ҹ� ��Ų��.
	for( int i = 0 ; i < 4 ; i++ ) 
		Safe_Delete( m_pChild[i] );
}


// 4���� �ڳʰ��� �����Ѵ�.
BOOL	CQuadTree::_SetCorners( int nCornerTL, int nCornerTR, int nCornerBL, int nCornerBR )
{
	m_nCorner[CORNER_TL] = nCornerTL;
	m_nCorner[CORNER_TR] = nCornerTR;
	m_nCorner[CORNER_BL] = nCornerBL;
	m_nCorner[CORNER_BR] = nCornerBR;
	m_nCenter			 = ( m_nCorner[CORNER_TL] + m_nCorner[CORNER_TR] + 
							 m_nCorner[CORNER_BL] + m_nCorner[CORNER_BR] ) / 4;
	return TRUE;
}


// �ڽ� ��带 �߰��Ѵ�.
CQuadTree*	CQuadTree::_AddChild( int nCornerTL, int nCornerTR, int nCornerBL, int nCornerBR )
{
	CQuadTree*	pChild;

	pChild = new CQuadTree( this );
	pChild->_SetCorners( nCornerTL, nCornerTR, nCornerBL, nCornerBR );

	return pChild;
}

// Quadtree�� 4���� �ڽ� Ʈ���� �κк���(subdivide)�Ѵ�.
BOOL	CQuadTree::_SubDivide()
{
	int		nTopEdgeCenter;
	int		nBottomEdgeCenter;
	int		nLeftEdgeCenter;
	int		nRightEdgeCenter;
	int		nCentralPoint;

	// ��ܺ� ���
	nTopEdgeCenter		= ( m_nCorner[CORNER_TL] + m_nCorner[CORNER_TR] ) * 0.5f;
	// �ϴܺ� ��� 
	nBottomEdgeCenter	= ( m_nCorner[CORNER_BL] + m_nCorner[CORNER_BR] ) * 0.5f ;
	// ������ ���
	nLeftEdgeCenter		= ( m_nCorner[CORNER_TL] + m_nCorner[CORNER_BL] ) * 0.5f;
	// ������ ���
	nRightEdgeCenter	= ( m_nCorner[CORNER_TR] + m_nCorner[CORNER_BR] ) * 0.5f;
	// �Ѱ��
	nCentralPoint		= ( m_nCorner[CORNER_TL] + m_nCorner[CORNER_TR] + 
							m_nCorner[CORNER_BL] + m_nCorner[CORNER_BR] ) * 0.25f;

	// ���̻� ������ �Ұ����Ѱ�? �׷��ٸ� SubDivide() ����
	if( (m_nCorner[CORNER_TR] - m_nCorner[CORNER_TL]) <= 1 )
	{
		return FALSE;
	}

	// 4���� �ڽĳ�� �߰�
	m_pChild[CORNER_TL] = _AddChild( m_nCorner[CORNER_TL], nTopEdgeCenter, nLeftEdgeCenter, nCentralPoint );
	m_pChild[CORNER_TR] = _AddChild( nTopEdgeCenter, m_nCorner[CORNER_TR], nCentralPoint, nRightEdgeCenter );
	m_pChild[CORNER_BL] = _AddChild( nLeftEdgeCenter, nCentralPoint, m_nCorner[CORNER_BL], nBottomEdgeCenter );
	m_pChild[CORNER_BR] = _AddChild( nCentralPoint, nRightEdgeCenter, nBottomEdgeCenter, m_nCorner[CORNER_BR] );
	
	return TRUE;
}

// ����� �������� �ε����� �����Ѵ�.
int		CQuadTree::_GenTriIndex( int nTris, LPVOID pIndex )
{
	// �ø��� ����� �׳� ����
	if( m_bCulled )
	{
		m_bCulled = FALSE;
		return nTris;
	}

	// ���� ��尡 ��µǾ�� �ϴ°�?
	if( _IsVisible() )
	{
//#ifdef _USE_INDEX16
		LPWORD p = ((LPWORD)pIndex) + nTris * 3;
//#else
		//LPDWORD p = ((LPDWORD)pIndex) + nTris * 3;
//#endif
		*p++ = m_nCorner[CORNER_TL];
		*p++ = m_nCorner[CORNER_TR];
		*p++ = m_nCorner[CORNER_BR];
		nTris++;
		*p++ = m_nCorner[CORNER_TL];
		*p++ = m_nCorner[CORNER_BR];
		*p++ = m_nCorner[CORNER_BL];
		nTris++;

		//INDEX* p = ((INDEX*)pIndex) + nTris;
		//p[nTris]._0 = m_nCorner[CORNER_TL];
		//p[nTris]._1 = m_nCorner[CORNER_TR];
		//p[nTris]._2 = m_nCorner[CORNER_BR];
	
		//nTris++;
		//p[nTris]._0 = m_nCorner[CORNER_TL];
		//p[nTris]._1 = m_nCorner[CORNER_BR];
		//p[nTris]._2 = m_nCorner[CORNER_BL];
		//nTris++;

		return nTris;
	}

	// �ڽ� ���� �˻�
	if( m_pChild[CORNER_BL] ) nTris = m_pChild[CORNER_BL]->_GenTriIndex( nTris, pIndex );
	if( m_pChild[CORNER_BR] ) nTris = m_pChild[CORNER_BR]->_GenTriIndex( nTris, pIndex );
	if( m_pChild[CORNER_TL] ) nTris = m_pChild[CORNER_TL]->_GenTriIndex( nTris, pIndex );
	if( m_pChild[CORNER_TR] ) nTris = m_pChild[CORNER_TR]->_GenTriIndex( nTris, pIndex );

	return nTris;
}

int CQuadTree::_IsInFrustum( VERTEXTERRAIN* pHeightMap, CFrustum* pFrustum )
{
	BOOL	b[4];
	BOOL	bInSphere;

	// ��豸�ȿ� �ִ°�?
//	if( m_fRadius == 0.0f ) g_pLog->Log( "Index:[%d], Radius:[%f]",m_nCenter, m_fRadius );
	bInSphere = pFrustum->isInFrustum( *(D3DXVECTOR3*)(pHeightMap+m_nCenter), m_fRadius );
	if( !bInSphere ) return FRUSTUM_OUT;	// ��豸 �ȿ� ������ �������� �������� �׽�Ʈ ����

	// ����Ʈ���� 4���� ��� �������� �׽�Ʈ
	b[0] = pFrustum->isIn( (D3DXVECTOR3*)(pHeightMap+m_nCorner[0]) );
	b[1] = pFrustum->isIn( (D3DXVECTOR3*)(pHeightMap+m_nCorner[1]) );
	b[2] = pFrustum->isIn( (D3DXVECTOR3*)(pHeightMap+m_nCorner[2]) );
	b[3] = pFrustum->isIn( (D3DXVECTOR3*)(pHeightMap+m_nCorner[3]) );

	// 4����� �������� �ȿ� ����
	if( (b[0] + b[1] + b[2] + b[3]) == 4 ) return FRUSTUM_COMPLETELY_IN;

	// �Ϻκ��� �������ҿ� �ִ� ���
	return FRUSTUM_PARTIALLY_IN;
}

// _IsInFrustum()�Լ��� ����� ���� �������� �ø� ����
void	CQuadTree::_FrustumCull( VERTEXTERRAIN* pHeightMap, CFrustum* pFrustum )
{
	int ret;

	ret = _IsInFrustum( pHeightMap, pFrustum );
	switch( ret )
	{
		case FRUSTUM_COMPLETELY_IN :	// �������ҿ� ��������, ������� �˻� �ʿ����
			m_bCulled = FALSE;
			return;
		case FRUSTUM_PARTIALLY_IN :		// �������ҿ� �Ϻ�����, ������� �˻� �ʿ���
			m_bCulled = FALSE;
			break;
		case FRUSTUM_OUT :				// �������ҿ��� �������, ������� �˻� �ʿ����
			m_bCulled = TRUE;
			return;
	}
	if( m_pChild[0] ) m_pChild[0]->_FrustumCull( pHeightMap, pFrustum );
	if( m_pChild[1] ) m_pChild[1]->_FrustumCull( pHeightMap, pFrustum );
	if( m_pChild[2] ) m_pChild[2]->_FrustumCull( pHeightMap, pFrustum );
	if( m_pChild[3] ) m_pChild[3]->_FrustumCull( pHeightMap, pFrustum );
}

// ����Ʈ���� �����.
BOOL	CQuadTree::Build( VERTEXTERRAIN* pHeightMap )
{
	if( _SubDivide() )
	{
		// ������ܰ�, ���� �ϴ��� �Ÿ��� ���Ѵ�.
		D3DXVECTOR3 v = *((D3DXVECTOR3*)(pHeightMap+m_nCorner[CORNER_TR])) - 
					    *((D3DXVECTOR3*)(pHeightMap+m_nCorner[CORNER_BL]));
		
		// v�� �Ÿ����� �� ��带 ���δ� ��豸�� �����̹Ƿ�, 
		// 2�� ������ �������� ���Ѵ�.
		m_fRadius	  = D3DXVec3Length( &v ) * 0.5f;
		m_pChild[CORNER_TL]->Build( pHeightMap );
		m_pChild[CORNER_TR]->Build( pHeightMap );
		m_pChild[CORNER_BL]->Build( pHeightMap );
		m_pChild[CORNER_BR]->Build( pHeightMap );
	}
	return TRUE;
}

//	�ﰢ���� �ε����� �����, ����� �ﰢ���� ������ ��ȯ�Ѵ�.
int		CQuadTree::GenerateIndex( LPVOID pIndex, VERTEXTERRAIN* pHeightMap, CFrustum* pFrustum )
{
	_FrustumCull( pHeightMap, pFrustum );
	return _GenTriIndex( 0, pIndex );
}

