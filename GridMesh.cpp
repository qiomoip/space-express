#include "GridMesh.h"
#include "Device.h"
#include "CameraManager.h"
#include "Camera.h"
#include "ShaderManager.h"
#include "Shader.h"

CGridMesh::CGridMesh(void)
	: CMesh()
	, m_pGridVB(NULL)
	, m_pLineVB(NULL)
	, m_iCnt(0)
{
	memset(&m_tGridMaterial, 0, sizeof(D3DMATERIAL9));
}


CGridMesh::~CGridMesh(void)
{
	Destroy();
}

HRESULT CGridMesh::LoadResource(const LPTSTR szMeshName)
{
	if(FAILED(CreateVertexBuffer()))
	{
		return E_FAIL;
	}

	memset(&m_tGridMaterial, 0, sizeof(D3DMATERIAL9));
	m_tGridMaterial.Diffuse.a = 1.f;
	m_tGridMaterial.Diffuse.r = 1.f;
	m_tGridMaterial.Diffuse.g = 0.8f;
	m_tGridMaterial.Diffuse.b = 1.f;
	m_tGridMaterial.Power = 0.2f;
	m_tGridMaterial.Specular = m_tGridMaterial.Diffuse;
	m_tGridMaterial.Ambient = m_tGridMaterial.Diffuse;

	return S_OK;
}

void CGridMesh::Render(CShader* pShader, const UINT& uPass)
{
	//D3DXMATRIX matWorld;
	//D3DXMatrixIdentity(&matWorld);
	//_SINGLE(CDevice)->GetDevice()->SetTransform(D3DTS_WORLD, &matWorld);

	//const D3DXMATRIX* pMatProj = _SINGLE(CCameraManager)->GetCurCam()->GetMatProj();
	//const D3DXMATRIX* pMatView = _SINGLE(CCameraManager)->GetCurCam()->GetMatView();
	//D3DXMATRIX matWVP = (*pMatView) * (*pMatProj);

	//_SINGLE(CShaderManager)->BeginShader(SHADER_DEFAULT, "DefaultTech");

	//CShader* pShader = _SINGLE(CShaderManager)->FindShader(SHADER_DEFAULT);
	//
	//pShader->SetMatrix("g_matWVP", &matWVP);

	//pShader->BeginPass(PASS_NOTEXTURE);
	//
	//pShader->SetValue("g_mtrlMesh", &m_tGridMaterial, sizeof(D3DMATERIAL9));

	//m_pDevice->SetFVF(VTXCOLORFVF);
	//m_pDevice->SetMaterial(&m_tGridMaterial);
	//m_pDevice->SetStreamSource( 0, m_pGridVB, 0, sizeof( VERTEXCOLOR ) );
	//m_pDevice->DrawPrimitive(D3DPT_LINELIST, 0, m_iCnt/2);

	//m_pDevice->SetStreamSource( 0, m_pLineVB, 0, sizeof(VERTEXCOLOR) );
	//m_pDevice->SetFVF(VTXCOLORFVF);
	//m_pDevice->DrawPrimitive( D3DPT_LINELIST, 0, 3 );
	//
	//pShader->EndPass();

	//_SINGLE(CShaderManager)->EndShader(SHADER_DEFAULT);

	pShader->SetValue("g_mtrlMesh", &m_tGridMaterial, sizeof(D3DMATERIAL9));
	pShader->SetTexture("g_BaseTex", NULL);

	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);
	D3DXMATRIX matVP = _SINGLE(CCameraManager)->GetCurCam()->GetMatViewProj();
	
	mat *= matVP;

	pShader->SetMatrix("g_matWVP", &mat);

	pShader->BeginPass(uPass);

	_SINGLE(CDevice)->GetDevice()->SetFVF(VTXCOLORFVF);
	_SINGLE(CDevice)->GetDevice()->SetMaterial(&m_tGridMaterial);
	_SINGLE(CDevice)->GetDevice()->SetStreamSource( 0, m_pGridVB, 0, sizeof( VERTEXCOLOR ) );
	_SINGLE(CDevice)->GetDevice()->DrawPrimitive(D3DPT_LINELIST, 0, m_iCnt/2);

	pShader->EndPass();

	pShader->BeginPass(PASS_COLOR);

	_SINGLE(CDevice)->GetDevice()->SetStreamSource( 0, m_pLineVB, 0, sizeof(VERTEXCOLOR) );
	_SINGLE(CDevice)->GetDevice()->SetFVF(VTXCOLORFVF);
	_SINGLE(CDevice)->GetDevice()->DrawPrimitive( D3DPT_LINELIST, 0, 3 );

	pShader->EndPass();

	//_SINGLE(CShaderManager)->EndShader(SHADER_DEFAULT);
}

void CGridMesh::Destroy()
{
	Safe_Release(m_pGridVB);
	Safe_Release(m_pLineVB);
}

float CGridMesh::GetSize()
{
	return 256 * 1.4f;
}

HRESULT CGridMesh::CreateVertexBuffer()
{
	float x1 = -128;
	float x2 = 128;
	float y1 = -128;
	float y2 = 128;
	float stepX = 1.f;
	float stepY = 1.f;
	const DWORD gridColor = D3DCOLOR_XRGB(0, 0, 0);

	if(_SINGLE(CDevice)->GetDevice()->CreateVertexBuffer(
		128 * 128 * sizeof(VERTEXCOLOR),
		D3DUSAGE_WRITEONLY,	VTXTERRAINFVF, D3DPOOL_MANAGED, &m_pGridVB, 0))
	{
		return E_FAIL;
	}

	VERTEXCOLOR* tempVB = NULL;

	m_pGridVB->Lock(0, 0, (void**)&tempVB, 0);

	for ( float x = x1; x<=x2; x+= stepX )
	{
		tempVB[m_iCnt].vPos = D3DXVECTOR3(x, 0.f, y1);
		tempVB[m_iCnt].dwColor = gridColor;
		++m_iCnt;
		tempVB[m_iCnt].vPos = D3DXVECTOR3(x, 0.f, y2);
		tempVB[m_iCnt].dwColor = gridColor;
		++m_iCnt;
	}

	m_pGridVB->Unlock();

	for ( float y = y1; y<= y2; y+= stepY )
	{
		tempVB[m_iCnt].vPos = D3DXVECTOR3(x1, 0.f, y);
		tempVB[m_iCnt].dwColor = gridColor;
		++m_iCnt;
		tempVB[m_iCnt].vPos = D3DXVECTOR3(x2, 0.f, y);
		tempVB[m_iCnt].dwColor = gridColor;
		++m_iCnt;
	}

	if(_SINGLE(CDevice)->GetDevice()->CreateVertexBuffer(
		6 * sizeof(VERTEXCOLOR),
		D3DUSAGE_WRITEONLY,	VTXCOLORFVF, D3DPOOL_MANAGED, &m_pLineVB, 0))
	{
		return E_FAIL;
	}

	VERTEXCOLOR colorVtx[] = { {D3DXVECTOR3(0.f, 0.0f, 0.0f),  0xffff0000 }, // red = +x Axis
	{ D3DXVECTOR3(200.0f, 0.0f, 0.0f),  0xffff0000 },
	//{ D3DXVECTOR3(0.0f, -200.0f, 0.0f),  0xff00ff00 }, // green = +y Axis
	{ D3DXVECTOR3(0.0f, 0.f, 0.0f),  0xff00ff00 }, // green = +y Axis
	{ D3DXVECTOR3(0.0f, 200.0f, 0.0f),  0xff00ff00 },
	{ D3DXVECTOR3(0.0f, 0.0f, 200.0f),  0xff0000ff }, // blue = +z Axis
	//{ D3DXVECTOR3(0.0f, 0.0f, -200.0f),  0xff0000ff }};
	{ D3DXVECTOR3(0.0f, 0.0f, 0.f),  0xff0000ff }};

	void *pVertices = NULL;

	m_pLineVB->Lock( 0, sizeof(colorVtx), (void**)&pVertices, 0 );
	memcpy( pVertices, colorVtx, sizeof(colorVtx) );
	m_pLineVB->Unlock();

	return S_OK;
}