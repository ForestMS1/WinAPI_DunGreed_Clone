#include "pch.h"
#include "CWeapon.h"
#include "CResourceMgr.h"
#include "CCamera.h"
#include "CMouse.h"

CWeapon::CWeapon()
{
    m_pOwner = nullptr;
}

CWeapon::CWeapon(CObj* pOwner) : m_fOffsetX(0.f), m_fOffsetY(0.f) , m_fAngle(0.f)
{
    m_pOwner = pOwner;
}
CWeapon::~CWeapon()
{
    Release();
}

void CWeapon::Initialize()
{
    m_eRender = GAMEOBJECT;
}

int CWeapon::Update()
{
    POINT mousePt = GET(CMouse)->Get_Point();
    Vec2 mousePos = GET(CCamera)->GetRealPos(mousePt);

    float	fWidth(0.f), fHeight(0.f), fDiagonal(0.f);


    fWidth = (float)mousePos.fX - m_tInfo.fX;
    fHeight = (float)mousePos.fY - m_tInfo.fY;

    fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

    m_fAngle = acosf(fWidth / fDiagonal);

    if (mousePos.fY > m_tInfo.fY)
        m_fAngle = 2.f * PI - m_fAngle;


    m_tInfo.fX = m_pOwner->Get_Info()->fX + (m_fOffsetX * cosf(m_fAngle));
    m_tInfo.fY = m_pOwner->Get_Info()->fY - (m_fOffsetY * sinf(m_fAngle));


    __super::Update_Rect();





    Move_Frame();
    return 0;
}

void CWeapon::Late_Update()
{

}

void CWeapon::Render(HDC hDC)
{
    if (g_bDebugMod)
        Rectangle(hDC, m_tRect.left - GET(CCamera)->Get_ScrollX(),
            m_tRect.top - GET(CCamera)->Get_ScrollY(),
            m_tRect.right - GET(CCamera)->Get_ScrollX(),
            m_tRect.bottom - GET(CCamera)->Get_ScrollY());
}

void CWeapon::Release()
{
    m_pOwner = nullptr;
}
