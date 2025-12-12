#include "pch.h"
#include "CBelialUI.h"

CBelialUI::CBelialUI(CObj* pOwner) : m_pOwner(pOwner)
{
}

CBelialUI::~CBelialUI()
{
    Release();
}

void CBelialUI::Initialize()
{
    m_iFrameWidth = 125;
    m_iFrameHeight = 16;
    m_tInfo.fX = WINCX >> 1;
    m_tInfo.fY = WINCY - m_iFrameHeight * 5;
    m_tInfo.fCX = m_iFrameWidth * 3;
    m_tInfo.fCY = m_iFrameHeight * 3;
    __super::Update_Rect();
    m_bIsOpen = false;

    m_fMaxHp = m_pOwner->Get_MaxHp();
    m_fCurHp = m_pOwner->Get_CurHp();

    GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/MonsterHP/BossLifeBase.bmp", L"BossLifeBase");
    GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/MonsterHP/BossLifeBack.bmp", L"BossLifeBack");
    GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/MonsterHP/BossLifeGauge.bmp", L"BossLifeGauge");
    GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/MonsterHP/BossSkellPortrait.bmp", L"BossSkellPortrait");
}

int CBelialUI::Update()
{
    m_fCurHp = m_pOwner->Get_CurHp();
    __super::Update_Rect();

    return 0;
}

void CBelialUI::Late_Update()
{

}

void CBelialUI::Render(HDC hDC)
{
    if (!m_bIsOpen)
        return;
    HDC hBackDC = GET(CResourceMgr)->Find_Bmp(L"BossLifeBack");

    GdiTransparentBlt(
        hDC,
        m_tRect.left,
        m_tRect.top,
        m_tInfo.fCX,
        m_tInfo.fCY,
        hBackDC,
        0,
        0,
        m_iFrameWidth,
        m_iFrameHeight,
        RGB(255, 0, 255)
    );    

    HDC hPortraitDC = GET(CResourceMgr)->Find_Bmp(L"BossSkellPortrait");

    GdiTransparentBlt(
        hDC,
        m_tRect.left + 10,
        m_tRect.top + 10,
        17 * 3,
        10 * 3,
        hPortraitDC,
        0,
        0,
        17,
        10,
        RGB(255, 0, 255)
    );

    HDC hLifeGaugeDC = GET(CResourceMgr)->Find_Bmp(L"BossLifeGauge");

    GdiTransparentBlt(
        hDC,
        m_tRect.left + 60,
        m_tRect.top,
        m_tInfo.fCX * (m_fCurHp / m_fMaxHp) - 63,
        m_tInfo.fCY,
        hLifeGaugeDC,
        0,
        0,
        100,
        10,
        RGB(255, 0, 255)
    );

    HDC hLifeBaseDC = GET(CResourceMgr)->Find_Bmp(L"BossLifeBase");

    GdiTransparentBlt(
        hDC,
        m_tRect.left,
        m_tRect.top,
        m_tInfo.fCX,
        m_tInfo.fCY,
        hLifeBaseDC,
        0,
        0,
        m_iFrameWidth,
        m_iFrameHeight,
        RGB(255, 0, 255)
    );
}

void CBelialUI::Release()
{
}
