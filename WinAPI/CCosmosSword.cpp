#include "pch.h"
#include "CCosmosSword.h"
#include "CResourceMgr.h"
#include "CCamera.h"

CCosmosSword::CCosmosSword(CObj* pOwner)
{
    m_pOwner = pOwner;
}
CCosmosSword::~CCosmosSword()
{

}

void CCosmosSword::Initialize()
{
    GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Item/Weapon/CosmosSword.bmp", L"CosmosSword");
    m_fOffsetX = m_pOwner->Get_Info()->fCX * 0.5f;
    m_fOffsetY = m_pOwner->Get_Info()->fCY * 0.5f;

    m_tInfo.fX = m_pOwner->Get_Info()->fX + m_fOffsetX;
    m_tInfo.fY = m_pOwner->Get_Info()->fY - m_fOffsetY;
    m_iFrameWidth = 27;
    m_iFrameHeight = 81;
    m_tInfo.fCX = m_iFrameWidth;
    m_tInfo.fCY = m_iFrameHeight;

    m_tFrame.iStart = 0;
    m_tFrame.iEnd = 11;
    m_tFrame.dwSpeed = 100;
    m_tFrame.iMotion = 0;
    m_tFrame.dwTime = GetTickCount();
}

int CCosmosSword::Update()
{
    CWeapon::Update();
	return 0;
}

void CCosmosSword::Late_Update()
{
    CWeapon::Late_Update();
}

void CCosmosSword::Render(HDC hDC)
{
    CWeapon::Render(hDC);

    HDC hMemDC = GET(CResourceMgr)->Find_Bmp(L"CosmosSword");

    int SrcX = m_iFrameWidth * m_tFrame.iStart;
    int SrcY = m_iFrameHeight * m_tFrame.iMotion;

    GdiTransparentBlt(
        hDC,
        m_tRect.left,
        m_tRect.top,
        m_tInfo.fCX,
        m_tInfo.fCY,
        hMemDC,
        SrcX,
        SrcY,
        m_iFrameWidth,
        m_iFrameHeight,
        RGB(255, 0, 255)
    );
}

void CCosmosSword::Release()
{
}
