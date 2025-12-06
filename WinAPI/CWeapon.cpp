#include "pch.h"
#include "CWeapon.h"
#include "CResourceMgr.h"
#include "CCamera.h"
#include "CMouse.h"

CWeapon::CWeapon() : m_fDamage(0.f), m_iMaxAttackCount(0), m_iCurAttackCount(0)
, isEquiped(false), m_fAngle(0.f)
{
    ZeroMemory(&m_tAttackRect, sizeof(RECT));
}

CWeapon::CWeapon(CObj* pOwner) : m_fOffsetX(0.f), m_fOffsetY(0.f) , m_fAngle(0.f) , m_fDamage(0.f)
, isEquiped(false)
{
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
    __super::Update_Rect();

    Move_Frame();

    POINT mousePt = GET(CMouse)->Get_Point();
    Vec2 mousePos = GET(CCamera)->GetRealPos(mousePt);

    float	fWidth(0.f), fHeight(0.f), fDiagonal(0.f);


    fWidth = (float)mousePos.fX - m_tInfo.fX;
    fHeight = (float)mousePos.fY - m_tInfo.fY;

    fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);
    if (fDiagonal <= 30.f)
        return 0;

    m_fAngle = acosf(fWidth / fDiagonal);

    if (mousePos.fY > m_tInfo.fY)
        m_fAngle = 2.f * PI - m_fAngle;


    m_tInfo.fX = GET(CPlayerMgr)->GetPlayer()->Get_Info()->fX + (m_fOffsetX * cosf(m_fAngle));
    m_tInfo.fY = GET(CPlayerMgr)->GetPlayer()->Get_Info()->fY - (m_fOffsetY * sinf(m_fAngle));
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
}

void CWeapon::Update_AttackRect()
{
    m_tAttackRect.left = m_tAttackInfo.fX - m_tAttackInfo.fCX * 0.5f;
    m_tAttackRect.top = m_tAttackInfo.fY - m_tAttackInfo.fCY * 0.5f;
    m_tAttackRect.right = m_tAttackInfo.fX + m_tAttackInfo.fCX * 0.5f;
    m_tAttackRect.bottom = m_tAttackInfo.fY + m_tAttackInfo.fCY * 0.5f;
}


