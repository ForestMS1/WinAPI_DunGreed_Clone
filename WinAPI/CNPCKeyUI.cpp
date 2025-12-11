#include "pch.h"
#include "CNPCKeyUI.h"

CNPCKeyUI::CNPCKeyUI(CObj* pOwner) : m_pOwner(pOwner)
{
}

CNPCKeyUI::~CNPCKeyUI()
{
    Release();
}

void CNPCKeyUI::Initialize()
{
    float offsetY = m_pOwner->Get_Info()->fCY;
    m_iFrameWidth = 13;
    m_iFrameHeight = 14;
    m_tInfo.fCX = m_iFrameWidth * 3;
    m_tInfo.fCY = m_iFrameHeight * 3;
    m_tInfo.fX = m_pOwner->Get_Info()->fX;
    m_tInfo.fY = m_pOwner->Get_Info()->fY - offsetY;
    __super::Update_Rect();
    m_bIsOpen = false;

    GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/KeyBoard/KeyBoard_F.bmp", L"KeyBoard_F");
}

int CNPCKeyUI::Update()
{

    return 0;
}

void CNPCKeyUI::Late_Update()
{
}

void CNPCKeyUI::Render(HDC hDC)
{
    int scrollX = GET(CCamera)->Get_ScrollX();
    int scrollY = GET(CCamera)->Get_ScrollY();
    HDC hMemDC = GET(CResourceMgr)->Find_Bmp(L"KeyBoard_F");

    GdiTransparentBlt(
        hDC,
        m_tRect.left - scrollX,
        m_tRect.top - scrollY,
        m_tInfo.fCX,
        m_tInfo.fCY,
        hMemDC,
        0,
        0,
        m_iFrameWidth,
        m_iFrameHeight,
        RGB(255, 0, 255)
    );
}

void CNPCKeyUI::Release()
{
}
