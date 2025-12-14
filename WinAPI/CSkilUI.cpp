#include "pch.h"
#include "CSkilUI.h"

CSkilUI::CSkilUI()
{
}

CSkilUI::~CSkilUI()
{
    Release();
}

void CSkilUI::Initialize()
{
    float offsetX = 60.f;
    float offsetY = 30.f;
    m_tInfo.fCX = 56;
    m_tInfo.fCY = 56;
    m_tInfo.fX = 620;
    m_tInfo.fY = 575;
    __super::Update_Rect();
    m_bIsOpen = false;
    GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/Item/Skill.bmp", L"SkillIcon");
    GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Item/Skil/Skill_CosmosSwordAuror.bmp", L"Skill_CosmosSwordAuror");
}

int CSkilUI::Update()
{
    __super::Update_Rect();
    //TODO : 플레이어가 장착한 무기가 무엇인지 가지고오기
    return 0;
}

void CSkilUI::Late_Update()
{
}

void CSkilUI::Render(HDC hDC)
{
    if (!m_bIsOpen)
        return;
    HDC hBackDC = GET(CResourceMgr)->Find_Bmp(L"SkillIcon");
    GdiTransparentBlt(
        hDC,
        m_tRect.left,
        m_tRect.top,
        m_tInfo.fCX,
        m_tInfo.fCY,
        hBackDC,
        0,
        0,
        56,
        56,
        RGB(255, 0, 255)
    );

    //CItem* pItem = nullptr;
    //if (GET(CPlayerMgr)->IsFirstSet())
    //    pItem = GET(CPlayerMgr)->GetEquip(L"Weapon1");
    //else
    //    pItem = GET(CPlayerMgr)->GetEquip(L"Weapon2");
    //if (pItem == nullptr)
    //    return;
    //HDC hItemDC = GET(CResourceMgr)->Find_Bmp(pItem->Get_FrameKey());
    //int offsetX(0);
    //if (pItem->Get_FrameWidth() < m_tInfo.fCX * 0.5f)
    //    offsetX = 30;
    //GdiTransparentBlt(
    //    hDC,
    //    m_tRect.left + 15 + offsetX,
    //    m_tRect.top + 10,
    //    pItem->Get_FrameWidth(),
    //    pItem->Get_FrameHeight(),
    //    hItemDC,
    //    0,
    //    0,
    //    pItem->Get_FrameWidth(),
    //    pItem->Get_FrameHeight(),
    //    RGB(255, 0, 255)
    //);

    HDC hSkillDC = GET(CResourceMgr)->Find_Bmp(L"Skill_CosmosSwordAuror");
    GdiTransparentBlt(
        hDC,
        m_tInfo.fX - 19,
        m_tInfo.fY - 19,
        19,
        19,
        hSkillDC,
        0,
        0,
        19,
        19,
        RGB(255, 0, 255)
    );
}

void CSkilUI::Release()
{
}
