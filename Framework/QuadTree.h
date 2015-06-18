#ifndef _CQuadTree_H_
#define _CQuadTree_H_

#include "define.h"
#include "Frustum.h"

/**
 * @brief QuadTree�� ���̽� Ŭ����
 *
 */ 
class CQuadTree
{
	/// ����Ʈ���� �����Ǵ� 4���� �ڳʰ��� ���� �����
	enum			CornerType { CORNER_BL, CORNER_BR, CORNER_TL, CORNER_TR };

	/// ����Ʈ���� �������Ұ��� ����
	enum			QuadLocation { FRUSTUM_OUT = 0,				/// �������ҿ��� �������
								   FRUSTUM_PARTIALLY_IN = 1,	/// �������ҿ� �κ�����
								   FRUSTUM_COMPLETELY_IN = 2,	/// �������ҿ� ��������
								   FRUSTUM_UNKNOWN = -1 };		/// �𸣰���(^^;)

private:
	CQuadTree*	m_pChild[4];		/// QuadTree�� 4���� �ڽĳ��

	int			m_nCenter;			/// QuadTree�� ������ ù��° ��
	int			m_nCorner[4];		/// QuadTree�� ������ �ι�° ��
									///    TopLeft(TL)      TopRight(TR)
									///              0------1
									///              |      |
									///              |      |
									///              2------3
									/// BottomLeft(BL)      BottomRight(BR)
	BOOL		m_bCulled;			/// �������ҿ��� �ø��� ����ΰ�?
	float		m_fRadius;			/// ��带 ���δ� ��豸(bounding sphere)�� ������
	
private:
	/// �ڽ� ��带 �߰��Ѵ�.
	CQuadTree*	_AddChild( int nCornerTL, int nCornerTR, int nCornerBL, int nCornerBR );

	/// 4���� �ڳʰ��� �����Ѵ�.
	BOOL		_SetCorners( int nCornerTL, int nCornerTR, int nCornerBL, int nCornerBR );

	/// Quadtree�� 4���� ���� Ʈ���� �κк���(subdivide)�Ѵ�.
	BOOL		_SubDivide();		// Quadtree�� subdivide�Ѵ�.

	/// ���� ��尡 ����� ������ ����ΰ�?
	BOOL		_IsVisible() { return ( m_nCorner[CORNER_TR] - m_nCorner[CORNER_TL] <= 1 ); }

	/// ����� �������� �ε����� �����Ѵ�.
	int			_GenTriIndex( int nTris, LPVOID pIndex );

	/// �޸𸮿��� ����Ʈ���� �����Ѵ�.
	void		_Destroy();

	/// �����尡 �������ҿ� ���ԵǴ°�?
	int			_IsInFrustum( VERTEXTERRAIN* pHeightMap, CFrustum* pFrustum );

	/// _IsInFrustum()�Լ��� ����� ���� �������� �ø� ����
	void		_FrustumCull( VERTEXTERRAIN* pHeightMap, CFrustum* pFrustum );
public:

				/// ���� ��Ʈ��� ������
				CQuadTree( int cx, int cy );

				/// ���� �ڽĳ�� ������
				CQuadTree( CQuadTree* pParent );

				/// �Ҹ���
				~CQuadTree();

	/// QuadTree�� �����Ѵ�.
	BOOL		Build( VERTEXTERRAIN* pHeightMap );

	///	�ﰢ���� �ε����� �����, ����� �ﰢ���� ������ ��ȯ�Ѵ�.
	int			GenerateIndex( LPVOID pIndex, VERTEXTERRAIN* pHeightMap, CFrustum* pFrustum );
};

#endif // _CQuadTree_H_
