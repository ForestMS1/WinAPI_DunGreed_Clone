#include "pch.h"
#include "CPaper.h"
#include "CRSPMgr.h"
#include "CRSP.h"
CPaper::CPaper() : m_bMouseOn(false)
{
}
CPaper::~CPaper()
{
	Release();
}

void CPaper::Initialize()
{
	m_iFrameWidth = 44;
	m_iFrameHeight = 45;
	m_tInfo.fCX = m_iFrameWidth * 2;
	m_tInfo.fCY = m_iFrameHeight * 2;
	m_tInfo.fX = m_pParentUI->Get_Info()->fX + m_tInfo.fCX * 2;
	m_tInfo.fY = m_pParentUI->Get_Info()->fY;
	__super::Update_Rect();

	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/NifleHeim/RSP.bmp", L"RSP");
}

int CPaper::Update()
{
	__super::Update_Rect();
	if (PtInRect(&m_tRect, GET(CMouse)->Get_Point()))
	{
		m_bMouseOn = true;
	}
	else
	{
		m_bMouseOn = false;
	}

	Clicked();
	return 0;
}

void CPaper::Late_Update()
{

}

void CPaper::Render(HDC hDC)
{

	HDC hMemDC = GET(CResourceMgr)->Find_Bmp(L"RSP");

	GdiTransparentBlt(
		hDC,
		m_tRect.left,
		m_tRect.top,
		m_tInfo.fCX,
		m_tInfo.fCY,
		hMemDC,
		92,
		0,
		m_iFrameWidth,
		m_iFrameHeight,
		RGB(255, 0, 255)
	);
}

void CPaper::Release()
{

}

void CPaper::Clicked()
{
	if (m_bMouseOn)
	{
		if (GET(CKeyMgr)->Key_Down(VK_LBUTTON))
		{
			GET(CRSPMgr)->SetPlayerSelect(CRSPMgr::PAPER);

			if(dynamic_cast<CRSP*>(GET(CUIMgr)->Find_UI(L"RSP")) != nullptr)
				dynamic_cast<CRSP*>(GET(CUIMgr)->Find_UI(L"RSP"))->SetStop();
		}
	}
}
