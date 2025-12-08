#include "pch.h"
#include "CEnemyHpBarUI.h"

CEnemyHpBarUI::CEnemyHpBarUI(CObj* pOwner) : m_pOwner(pOwner)
{
}

CEnemyHpBarUI::~CEnemyHpBarUI()
{
	Release();
}

void CEnemyHpBarUI::Initialize()
{
    float offsetY = m_pOwner->Get_Info()->fCY * 0.5f;
    m_iFrameWidth = 74;
    m_iFrameHeight = 20;
    m_tInfo.fCX = 37;
    m_tInfo.fCY = 10;
    m_tInfo.fX = m_pOwner->Get_Info()->fX;
    m_tInfo.fY = m_pOwner->Get_Info()->fY + offsetY;
    __super::Update_Rect();
    m_bIsOpen = true;

    m_fMaxHp = m_pOwner->Get_MaxHp();
    m_fCurHp = m_pOwner->Get_CurHp();

    GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/MonsterHP/MonsterHpBar.bmp", L"MonsterHpBar");
    GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/MonsterHP/MonsterLifeGauge.bmp", L"MonsterLifeGauge");
}

int CEnemyHpBarUI::Update()
{
    m_fCurHp = m_pOwner->Get_CurHp();

	return 0;
}

void CEnemyHpBarUI::Late_Update()
{
}

void CEnemyHpBarUI::Render(HDC hDC)
{
    int scrollX = GET(CCamera)->Get_ScrollX();
    int scrollY = GET(CCamera)->Get_ScrollY();
    HDC hBackDC = GET(CResourceMgr)->Find_Bmp(L"MonsterHpBar");

    GdiTransparentBlt(
        hDC,
        m_tRect.left - scrollX,
        m_tRect.top - scrollY,
        m_tInfo.fCX,
        m_tInfo.fCY,
        hBackDC,
        0,
        0,
        m_iFrameWidth,
        m_iFrameHeight,
        RGB(255, 0, 255)
        );

    HDC hLifeDC = GET(CResourceMgr)->Find_Bmp(L"MonsterLifeGauge");

    GdiTransparentBlt(
        hDC,
        m_tRect.left - scrollX,
        m_tRect.top - scrollY,
        m_tInfo.fCX * (m_fCurHp / m_fMaxHp),
        m_tInfo.fCY,
        hLifeDC,
        0,
        0,
        66 * (m_fCurHp / m_fMaxHp),
        12,
        RGB(255, 0, 255)
    );
}

void CEnemyHpBarUI::Release()
{
}
