#include "ThirdCam.h"
#include "KeyManager.h"

//typedef struct _tagCamera
//{
//      D3DXMATRIX matView;
//      D3DXMATRIX matProj;
//      D3DXVECTOR3 vPos;
//      D3DXVECTOR3 vLook;
//      D3DXVECTOR3 vUp;
//      D3DXVECTOR3 vRight;
//}CAMERA;

CThirdCam::CThirdCam(void)
        : CCamera()
{
}


CThirdCam::~CThirdCam(void)
{
        int a = 10;
}

void CThirdCam::Init()
{
        CCamera::Init();
}
void CThirdCam::Update()
{
        CCamera::Update();
}
void CThirdCam::Input()
{
        m_tCam.iDir = 0;
        m_tCam.iAngle = 0;
        const KEYINFO* pInfo = _SINGLE(CKeyManager)->GetKey("KEY_UP");
        if(!pInfo)
                return;
        if(pInfo->bPush || pInfo->bDown)
        {
                m_tCam.iDir = 1;
                Move();
        }

        pInfo = _SINGLE(CKeyManager)->GetKey("KEY_DOWN");
        if(pInfo->bPush || pInfo->bDown)
        {
                m_tCam.iDir = -1;
                Move();
        }

        pInfo = _SINGLE(CKeyManager)->GetKey("KEY_RIGHT");
        if(pInfo->bPush || pInfo->bDown)
        {
                m_tCam.iAngle = 1;
                Yaw();
        }

        pInfo = _SINGLE(CKeyManager)->GetKey("KEY_LEFT");
        if(pInfo->bPush || pInfo->bDown)
        {
                m_tCam.iAngle = -1;
                Yaw();
        }

}

void CThirdCam::Yaw()
{
        D3DXMATRIX matRot;
        D3DXMatrixRotationAxis(&matRot, &m_tCam.vUp, D3DX_PI * 0.01f * m_tCam.iAngle);

        D3DXVec3TransformCoord(&m_tCam.vRight, &m_tCam.vRight, &matRot);
        D3DXVec3TransformCoord(&m_tCam.vLook, &m_tCam.vLook, &matRot);
}
void CThirdCam::Pitch()
{
        D3DXMATRIX matRot;
        D3DXMatrixRotationAxis(&matRot, &m_tCam.vRight, D3DX_PI * 0.01f * m_tCam.iAngle);

        D3DXVec3TransformCoord(&m_tCam.vUp, &m_tCam.vUp, &matRot);
        D3DXVec3TransformCoord(&m_tCam.vLook, &m_tCam.vLook, &matRot);
}
void CThirdCam::Roll()
{
        D3DXMATRIX matRot;
        D3DXMatrixRotationAxis(&matRot, &m_tCam.vLook, D3DX_PI * 0.01f * m_tCam.iAngle);

        D3DXVec3TransformCoord(&m_tCam.vRight, &m_tCam.vRight, &matRot);
        D3DXVec3TransformCoord(&m_tCam.vUp, &m_tCam.vUp, &matRot);
}
void CThirdCam::Move()
{
        D3DXVECTOR3 vDir;
        D3DXVec3Cross(&vDir, &m_tCam.vRight, &D3DXVECTOR3(0.f, 1.f, 0.f));
        D3DXVec3Normalize(&vDir, &vDir);
        m_tCam.vPos += D3DXVECTOR3(vDir.x, 0.f, vDir.z) * 0.05f * m_tCam.iDir;
        //m_tCam.vPos += m_tCam.vLook * 0.01f * m_tCam.iDir;
}
