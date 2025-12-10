#include "pch.h"
#include "CGoldUI.h"

CGoldUI::CGoldUI() : m_iCurGold(0.f)
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


    AddFontResource(TEXT("Aa카시오페아"));
    m_hFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0,
        HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("Aa카시오페아"));
}

int CGoldUI::Update()
{
	//TODO : 플레이어가 소지한 골드 가져오기
    m_iCurGold = GET(CPlayerMgr)->GetGold();
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

    HFONT hOldFont = (HFONT)SelectObject(hDC, m_hFont);
    wstring text = to_wstring((int)m_iCurGold);
    SetBkMode(hDC, TRANSPARENT);
    SetTextColor(hDC, RGB(255, 255, 255));
    TextOut(hDC, m_tRect.left + 40, m_tRect.top + 4, text.c_str(), (int)text.size());
    SelectObject(hDC, hOldFont);
}

void CGoldUI::Release()
{
    if (m_hFont)
    {
        DeleteObject(m_hFont);
        m_hFont = NULL;
    }
    RemoveFontResource(TEXT("Aa카시오페아"));
}
