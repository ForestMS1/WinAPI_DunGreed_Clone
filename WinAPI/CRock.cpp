#include "pch.h"
#include "CRock.h"
#include "CRSPMgr.h"
#include "CRSP.h"

CRock::CRock() : m_bMouseOn(false)
{
}
CRock::~CRock()
{
	Release();
}

void CRock::Initialize()
{
	m_iFrameWidth = 44;
	m_iFrameHeight = 45;
	m_tInfo.fCX = m_iFrameWidth * 2;
	m_tInfo.fCY = m_iFrameHeight * 2;
	m_tInfo.fX = m_pParentUI->Get_Info()->fX - m_tInfo.fCX * 2;
	m_tInfo.fY = m_pParentUI->Get_Info()->fY;
	__super::Update_Rect();

	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/NifleHeim/RSP.bmp", L"RSP");
}

int CRock::Update()
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

void CRock::Late_Update()
{

}

void CRock::Render(HDC hDC)
{

	HDC hMemDC = GET(CResourceMgr)->Find_Bmp(L"RSP");

	GdiTransparentBlt(
		hDC,
		m_tRect.left,
		m_tRect.top,
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

void CRock::Release()
{

}

void CRock::Clicked()
{
	if (m_bMouseOn)
	{
		if (GET(CKeyMgr)->Key_Down(VK_LBUTTON))
		{
			GET(CRSPMgr)->SetPlayerSelect(CRSPMgr::ROCK);
			if (dynamic_cast<CRSP*>(GET(CUIMgr)->Find_UI(L"RSP")) != nullptr)
				dynamic_cast<CRSP*>(GET(CUIMgr)->Find_UI(L"RSP"))->SetStop();
		}
	}
}
