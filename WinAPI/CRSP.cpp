#include "pch.h"
#include "CRSP.h"

CRSP::CRSP(CObj* pOwner) : m_pOwner(pOwner), m_bStop(false)
{
}

CRSP::~CRSP()
{
    Release();
}

void CRSP::Initialize()
{
    float offsetY = m_pOwner->Get_Info()->fCY;
    m_iFrameWidth = 44;
    m_iFrameHeight = 45;
    m_tInfo.fCX = m_iFrameWidth * 2;
    m_tInfo.fCY = m_iFrameHeight * 2;
    m_tInfo.fX = m_pOwner->Get_Info()->fX;
    m_tInfo.fY = m_pOwner->Get_Info()->fY - offsetY;
    __super::Update_Rect();
    m_bIsOpen = false;

    m_tFrame.iStart = 0;
    m_tFrame.iMotion = 0;
    m_tFrame.iEnd = 2;
    m_tFrame.dwSpeed = 100;
    m_tFrame.dwTime = GetTickCount();

    GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/NifleHeim/RSP.bmp", L"RSP");
}

int CRSP::Update()
{

   // float offsetY = m_pOwner->Get_Info()->fCY;
   // m_tInfo.fX = m_pOwner->Get_Info()->fX;
   // m_tInfo.fY = m_pOwner->Get_Info()->fY - offsetY;
   // __super::Update_Rect();


    if(!m_bStop && !m_pOwner->IsDead())
        Move_Frame();

    return 0;
}

void CRSP::Late_Update()
{
}

void CRSP::Render(HDC hDC)
{
    if (!m_bIsOpen)
        return;
    int scrollX = GET(CCamera)->Get_ScrollX();
    int scrollY = GET(CCamera)->Get_ScrollY();
    HDC hMemDC = GET(CResourceMgr)->Find_Bmp(L"RSP");

    GdiTransparentBlt(
        hDC,
        m_tRect.left - scrollX,
        m_tRect.top - scrollY,
        m_tInfo.fCX,
        m_tInfo.fCY,
        hMemDC,
        m_iFrameWidth * m_tFrame.iStart,
        m_iFrameHeight * m_tFrame.iMotion,
        m_iFrameWidth,
        m_iFrameHeight,
        RGB(255, 0, 255)
    );
}

void CRSP::Release()
{
}
