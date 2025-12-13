#include "pch.h"
#include "CPlayerDashBar.h"
#include "CPlayer.h"

CPlayerDashBar::CPlayerDashBar() : m_iMaxDashCount(0), m_iCurDashCount(0), m_fCurDashGage(0.f)
{
}

CPlayerDashBar::~CPlayerDashBar()
{
}

void CPlayerDashBar::Initialize()
{
    m_iMaxDashCount = dynamic_cast<CPlayer*>(GET(CPlayerMgr)->GetPlayer())->GetMaxDashCount();
    m_iCurDashCount = dynamic_cast<CPlayer*>(GET(CPlayerMgr)->GetPlayer())->GetCurDashCount();


    float offset = 50.f;
    m_tInfo.fCX = 44.f * m_iMaxDashCount;
    m_tInfo.fCY = 32.f;
    m_tInfo.fX = 23.f + offset;
    m_tInfo.fY = 90;
    __super::Update_Rect();
    m_bIsOpen = true;
    GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/PlayerHP/DashStart.bmp", L"DashStart");
    GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/PlayerHP/DashEnd.bmp", L"DashEnd");
    GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/PlayerHP/DashCount.bmp", L"DashCount");
    GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/PlayerHP/DashMid.bmp", L"DashMid");
}

int CPlayerDashBar::Update()
{
    m_iMaxDashCount = dynamic_cast<CPlayer*>(GET(CPlayerMgr)->GetPlayer())->GetMaxDashCount();
    m_iCurDashCount = dynamic_cast<CPlayer*>(GET(CPlayerMgr)->GetPlayer())->GetCurDashCount();

	return 0;
}

void CPlayerDashBar::Late_Update()
{
}

void CPlayerDashBar::Render(HDC hDC)
{
    HDC hBackDC = GET(CResourceMgr)->Find_Bmp(L"DashStart");
    GdiTransparentBlt(
        hDC,
        m_tRect.left,
        m_tRect.top,
        44,
        32,
        hBackDC,
        0,
        0,
        44,
        32,
        RGB(255, 0, 255)
    );
    float offset = 44;
    for (size_t i = 1; i < m_iMaxDashCount - 1; ++i)
    {
        HDC hBackEndDC = GET(CResourceMgr)->Find_Bmp(L"DashMid");
        if (i != 1)
            offset = 35;
        GdiTransparentBlt(
            hDC,
            m_tRect.left + offset * i,
            m_tRect.top,
            35,
            32,
            hBackEndDC,
            0,
            0,
            35,
            32,
            RGB(255, 0, 255)
        );
    }

    HDC hBackEndDC = GET(CResourceMgr)->Find_Bmp(L"DashEnd");
    GdiTransparentBlt(
        hDC,
        m_tRect.left + 44 + 35 * (m_iMaxDashCount - 2),
        m_tRect.top,
        46,
        32,
        hBackEndDC,
        0,
        0,
        48,
        32,
        RGB(255, 0, 255)
    );

    float offsetX = 8;
    float offsetY = 8;
    for (size_t i = 0; i < m_iCurDashCount; ++i)
    {
        HDC hCountDC = GET(CResourceMgr)->Find_Bmp(L"DashCount");
        GdiTransparentBlt(
            hDC,
            m_tRect.left + (36 * i) + offsetX,
            m_tRect.top + offsetY,
            36,
            16,
            hCountDC,
            0,
            0,
            36,
            16,
            RGB(255, 0, 255)
        );
    }
}

void CPlayerDashBar::Release()
{
}
