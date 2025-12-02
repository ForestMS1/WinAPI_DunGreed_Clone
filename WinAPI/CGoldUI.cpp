#include "pch.h"
#include "CGoldUI.h"

CGoldUI::CGoldUI() : m_fCurGold(0.f)
{
}

CGoldUI::~CGoldUI()
{
}

void CGoldUI::Initialize()
{
    float offset = 30.f;
    m_tInfo.fCX = 34.f;
    m_tInfo.fCY = 28.f;
    m_tInfo.fX = (m_tInfo.fCX * 0.5f + offset);
    m_tInfo.fY = WINCY - (m_tInfo.fCY * 0.5f + offset + 30);
    __super::Update_Rect();
    m_bIsOpen = true;
    GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/WorldMap/ShopIcon.bmp", L"ShopIcon");
}

int CGoldUI::Update()
{
	//TODO : 플레이어가 소지한 골드 가져오기
	return 0;
}

void CGoldUI::Late_Update()
{
}

void CGoldUI::Render(HDC hDC)
{
    HDC hBackDC = GET(CResourceMgr)->Find_Bmp(L"ShopIcon");
    GdiTransparentBlt(
        hDC,
        m_tRect.left,
        m_tRect.top,
        m_tInfo.fCX,
        m_tInfo.fCY,
        hBackDC,
        0,
        0,
        17,
        14,
        RGB(255, 0, 255)
    );
}

void CGoldUI::Release()
{
}
