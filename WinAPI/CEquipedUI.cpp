#include "pch.h"
#include "CEquipedUI.h"

CEquipedUI::CEquipedUI()
{
}

CEquipedUI::~CEquipedUI()
{
    Release();
}

void CEquipedUI::Initialize()
{
    float offset = 30.f;
    m_tInfo.fCX = 102.f;
    m_tInfo.fCY = 72.f;
    m_tInfo.fX = WINCX - (m_tInfo.fCX * 0.5f + offset);
    m_tInfo.fY = WINCY - (m_tInfo.fCY * 0.5f + offset);
    __super::Update_Rect();
    m_bIsOpen = true;
    GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/Inventory/EquippedWeaponBase.bmp", L"EquippedWeaponBase");

}

int CEquipedUI::Update()
{
    //TODO : 플레이어가 장착한 무기가 무엇인지 가지고오기
    return 0;
}

void CEquipedUI::Late_Update()
{
}

void CEquipedUI::Render(HDC hDC)
{
    HDC hBackDC = GET(CResourceMgr)->Find_Bmp(L"EquippedWeaponBase");
    GdiTransparentBlt(
        hDC,
        m_tRect.left,
        m_tRect.top,
        m_tInfo.fCX,
        m_tInfo.fCY,
        hBackDC,
        0,
        0,
        102,
        72,
        RGB(255, 0, 255)
    );
}

void CEquipedUI::Release()
{
}
