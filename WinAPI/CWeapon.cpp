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

}

int CWeapon::Update()
{
    POINT mousePt = GET(CMouse)->Get_Point();
    m_fAngle = atan2(m_tInfo.fY - mousePt.y, m_tInfo.fX - mousePt.x);


    m_tInfo.fX = m_pOwner->Get_Info()->fX - (m_fOffsetX * cosf(m_fAngle)) - GET(CCamera)->Get_ScrollX();
    m_tInfo.fY = m_pOwner->Get_Info()->fY - (m_fOffsetY * sinf(m_fAngle)) - GET(CCamera)->Get_ScrollY();
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
        Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CWeapon::Release()
{
    m_pOwner = nullptr;
}
