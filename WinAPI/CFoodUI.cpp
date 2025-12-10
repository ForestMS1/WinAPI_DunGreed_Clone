#include "pch.h"
#include "CFoodUI.h"

CFoodUI::CFoodUI() : m_fMaxSatiety(100.f), m_fCurSatiety(0.f)
{
}

CFoodUI::~CFoodUI()
{
	Release();
}

void CFoodUI::Initialize()
{
    float offset = 30.f;
    m_tInfo.fCX = 34.f;
    m_tInfo.fCY = 28.f;
    m_tInfo.fX = (m_tInfo.fCX * 0.5f + offset);
    m_tInfo.fY = WINCY - (m_tInfo.fCY * 0.5f + offset);
    __super::Update_Rect();
    m_bIsOpen = true;
    GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/WorldMap/Food.bmp", L"Food");


    AddFontResource(TEXT("Aa카시오페아"));
    m_hFont = CreateFont(20, 0, 0, 0, 0, 0, 0, 0,
        HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("Aa카시오페아"));
}

int CFoodUI::Update()
{
    //TODO : 현재 포만감 가져오고 폰트 띄우기
    m_fMaxSatiety = GET(CPlayerMgr)->GetMaxSatiety();
    m_fCurSatiety = GET(CPlayerMgr)->GetCurSatiety();
	return 0;
}

void CFoodUI::Late_Update()
{
}

void CFoodUI::Render(HDC hDC)
{
    HDC hBackDC = GET(CResourceMgr)->Find_Bmp(L"Food");
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
    wstring text = to_wstring((int)m_fCurSatiety).append(L"/").append(to_wstring((int)m_fMaxSatiety));
    SetBkMode(hDC, TRANSPARENT);
    SetTextColor(hDC, RGB(255, 255, 255));
    TextOut(hDC, m_tRect.left + 40, m_tRect.top + 4, text.c_str(), (int)text.size());
    SelectObject(hDC, hOldFont);
}

void CFoodUI::Release()
{
    if (m_hFont)
    {
        DeleteObject(m_hFont);
        m_hFont = NULL;
    }
    RemoveFontResource(TEXT("Aa카시오페아"));
}
