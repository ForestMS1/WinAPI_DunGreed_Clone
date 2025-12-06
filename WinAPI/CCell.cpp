#include "pch.h"
#include "CCell.h"
#include "CGatlingGun.h"

CCell::CCell() : m_bMouseOn(false), m_bClicked(false)
{
}

CCell::CCell(CUI* pParentUI) : m_bMouseOn(false), m_bClicked(false)
{
	m_pParentUI = pParentUI;
}

CCell::~CCell()
{
	Release();
}

void CCell::Initialize()
{
	m_tInfo.fCX = 57.f;
	m_tInfo.fCY = 57.f;
	__super::Update_Rect();

	m_pItem = new CGatlingGun;
	m_pItem->Initialize();
	m_pItem->Set_Pos(m_tInfo.fX, m_tInfo.fY);
}

int CCell::Update()
{
	if (!m_bIsOpen)
		return 0;
	__super::Update_Rect();
	if (PtInRect(&m_tRect, GET(CMouse)->Get_Point()))
	{
		m_bMouseOn = true;
	}
	else
	{
		m_bMouseOn = false;
	}
	return 0;
}

void CCell::Late_Update()
{
	Clicked();
}

void CCell::Render(HDC hDC)
{
	m_wsFrameKey = L"";
	if (m_bMouseOn)
		m_wsFrameKey = L"Cell_On";
	else
		m_wsFrameKey = L"Cell";

	HDC hMemDC = GET(CResourceMgr)->Find_Bmp(m_wsFrameKey);

	GdiTransparentBlt(
		hDC,
		m_tRect.left,
		m_tRect.top,
		m_tInfo.fCX,
		m_tInfo.fCY,
		hMemDC,
		0,
		0,
		m_tInfo.fCX,
		m_tInfo.fCY,
		RGB(255, 0, 255)
	);

	if (m_bClicked)
	{
		// 마우스 클래스에서 렌더링 아이템 렌더링
	}
	else
	{
		HDC hItemDC = GET(CResourceMgr)->Find_Bmp(m_pItem->Get_FrameKey());

		GdiTransparentBlt(
			hDC,
			m_tRect.left,
			m_tRect.top,
			m_tInfo.fCX,
			m_tInfo.fCY,
			hItemDC,
			0,
			0,
			m_pItem->Get_FrameWidth(),
			m_pItem->Get_FrameHeight(),
			RGB(255, 0, 255)
		);
	}
}

void CCell::Release()
{
}

void CCell::Clicked()
{
	if (!m_bIsOpen)
	{
		//마우스에게 아이템 정보 해제
		GET(CMouse)->PutItem(m_pItem);

		m_bClicked = false;
		return;
	}

	if (!m_bClicked && m_bMouseOn && GET(CKeyMgr)->Key_Pressing(VK_LBUTTON))
	{
		//내 칸에는 템 렌더링 x

		//마우스에게 아이템 정보 전달
		GET(CMouse)->PickItem(m_pItem);

		//마우스 좌표에 아이템 렌더링
		m_bClicked = true;
	}
	else if (m_bClicked && GET(CKeyMgr)->Key_Pressing(VK_LBUTTON))
	{
		//마우스에게 아이템 정보 해제
		GET(CMouse)->PutItem(m_pItem);

		m_bClicked = false;
	}
}
