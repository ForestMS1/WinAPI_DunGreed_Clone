#include "pch.h"
#include "CPlayerHpBar.h"
#include "CPlayerUI.h"
CPlayerHpBar::CPlayerHpBar()
{
}

CPlayerHpBar::~CPlayerHpBar()
{
    Release();
}

void CPlayerHpBar::Initialize()
{
    float offset = 10.f;
    m_tInfo.fCX = 227.f;
    m_tInfo.fCY = 48.f;
    m_tInfo.fX = m_tInfo.fCX * 0.5f + offset;
    m_tInfo.fY = m_tInfo.fCY * 0.5f + offset;
    __super::Update_Rect();
    m_bIsOpen = true;
    GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/PlayerHP/PlayerLifeBase.bmp", L"PlayerLifeBase");
    GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/PlayerHP/PlayerLifeBack.bmp", L"PlayerLifeBack");
    GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/PlayerHP/LifeBar.bmp", L"LifeBar");
    GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/PlayerHP/LifeWave.bmp", L"LifeWave");

    //LifeWave의 m_tFrame
    m_tFrame.iStart = 0;
    m_tFrame.iEnd = 6;
    m_tFrame.iMotion = 0;
    m_tFrame.dwSpeed = 50.f;
    m_tFrame.dwTime = GetTickCount();

    AddFontResource(TEXT("Aa카시오페아"));
    m_hFont = CreateFont(40, 0, 0, 0, 0, 0, 0, 0,
        HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("Aa카시오페아"));
}

int CPlayerHpBar::Update()
{
    //TODO : 플레이어의 체력을 받아와서 비례한 길이로 LifeBar 출력
    m_fMaxHp = GET(CPlayerMgr)->GetPlayer()->Get_MaxHp();
    m_fCurHp = GET(CPlayerMgr)->GetPlayer()->Get_CurHp();
    Move_Frame();

    return OBJ_NOEVENT;
}

void CPlayerHpBar::Late_Update()
{

}

void CPlayerHpBar::Render(HDC hDC)
{
    HDC hBackDC = GET(CResourceMgr)->Find_Bmp(L"PlayerLifeBack");
    GdiTransparentBlt(
        hDC,
        m_tRect.left,
        m_tRect.top,
        m_tInfo.fCX,
        m_tInfo.fCY,
        hBackDC,
        0,
        0,
        296,
        64,
        RGB(255, 0, 255)
    );


    if (m_fCurHp > 100.f)
    {
        HDC hHpDC = GET(CResourceMgr)->Find_Bmp(L"LifeBar");
        GdiTransparentBlt(
            hDC,
            m_tRect.left + 65,
            m_tRect.top,
            1.5 * 100,
            m_tInfo.fCY,
            hHpDC,
            0,
            0,
            196,
            40,
            RGB(255, 0, 255)
        );
        HDC hHpWaveDC = GET(CResourceMgr)->Find_Bmp(L"LifeWave");
        int SrcX = 24 * m_tFrame.iStart;
        GdiTransparentBlt(
            hDC,
            m_tRect.left + 65 + 1.5 * 100,
            m_tRect.top,
            12,
            m_tInfo.fCY,
            hHpWaveDC,
            SrcX,
            0,
            24,
            40,
            RGB(255, 0, 255)
        );
    }
    else
    {
        HDC hHpDC = GET(CResourceMgr)->Find_Bmp(L"LifeBar");
        GdiTransparentBlt(
            hDC,
            m_tRect.left + 65,
            m_tRect.top,
            1.5 * m_fMaxHp * (m_fCurHp / m_fMaxHp),
            m_tInfo.fCY,
            hHpDC,
            0,
            0,
            196,
            40,
            RGB(255, 0, 255)
        );
        HDC hHpWaveDC = GET(CResourceMgr)->Find_Bmp(L"LifeWave");
        int SrcX = 24 * m_tFrame.iStart;
        GdiTransparentBlt(
            hDC,
            m_tRect.left + 65 + 1.5 * m_fMaxHp * (m_fCurHp / m_fMaxHp),
            m_tRect.top,
            12,
            m_tInfo.fCY,
            hHpWaveDC,
            SrcX,
            0,
            24,
            40,
            RGB(255, 0, 255)
        );
    }
  
    HDC hMemDC = GET(CResourceMgr)->Find_Bmp(L"PlayerLifeBase");
    GdiTransparentBlt(
        hDC,
        m_tRect.left,
        m_tRect.top,
        m_tInfo.fCX,
        m_tInfo.fCY,
        hMemDC,
        0,
        0,
        296,
        64,
        RGB(255, 0, 255)
    );


    HFONT hOldFont = (HFONT)SelectObject(hDC, m_hFont);
    wstring text = to_wstring((int)m_fCurHp).append(L"/").append(to_wstring((int)m_fMaxHp));
    SetBkMode(hDC, TRANSPARENT);
    SetTextColor(hDC, RGB(255, 255, 255));
    TextOut(hDC, m_tRect.left + 90, m_tRect.top + 3, text.c_str(), (int)text.size());
    SelectObject(hDC, hOldFont);
}

void CPlayerHpBar::Release()
{
    if (m_hFont)
    {
        DeleteObject(m_hFont);
        m_hFont = NULL;
    }
    RemoveFontResource(TEXT("Aa카시오페아"));
}
