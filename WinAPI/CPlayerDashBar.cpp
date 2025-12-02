#include "pch.h"
#include "CPlayerDashBar.h"

CPlayerDashBar::CPlayerDashBar() : m_iMaxDashCount(0), m_iCurDashCount(0), m_fCurDashGage(0.f)
{
}

CPlayerDashBar::~CPlayerDashBar()
{
}

void CPlayerDashBar::Initialize()
{
    float offset = 25.f;
    m_tInfo.fCX = 22.f;
    m_tInfo.fCY = 16.f;
    m_tInfo.fX = 23.f;
    m_tInfo.fY = 70;
    __super::Update_Rect();
    m_bIsOpen = true;
    GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/PlayerHP/DashStart.bmp", L"DashStart");
    GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/PlayerHP/DashEnd.bmp", L"DashEnd");
    GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/PlayerHP/DashCount.bmp", L"DashCount");
}

int CPlayerDashBar::Update()
{
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
        m_tInfo.fCX,
        m_tInfo.fCY,
        hBackDC,
        0,
        0,
        44,
        32,
        RGB(255, 0, 255)
    );

    HDC hBackEndDC = GET(CResourceMgr)->Find_Bmp(L"DashEnd");
    GdiTransparentBlt(
        hDC,
        m_tRect.left + m_tInfo.fCX,
        m_tRect.top,
        m_tInfo.fCX,
        m_tInfo.fCY,
        hBackEndDC,
        0,
        0,
        44,
        32,
        RGB(255, 0, 255)
    );
}

void CPlayerDashBar::Release()
{
}
