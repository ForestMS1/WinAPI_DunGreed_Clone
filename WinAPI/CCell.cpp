#include "pch.h"
#include "CCell.h"
#include "CGatlingGun.h"

CCell::CCell() : m_bMouseOn(false), m_pItem(nullptr)
{
}

CCell::CCell(CUI* pParentUI) : m_bMouseOn(false), m_pItem(nullptr)
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

	//m_pItem = new CGatlingGun;
	if (m_pItem != nullptr)
	{
		m_pItem->Initialize();
		m_pItem->Set_Pos(m_tInfo.fX, m_tInfo.fY);
	}
}

int CCell::Update()
{
	if (!m_bIsOpen)
	{
		//마우스에게 아이템 정보 해제
		if (m_pItem == nullptr && GET(CMouse)->Get_Item() != nullptr)
		{
			Safe_Delete(m_pItem);
			m_pItem = GET(CMouse)->Get_Item()->Clone();
			GET(CMouse)->Set_State(CMouse::MouseState::EMPTY);
			GET(CMouse)->Delete_Item();
		}

		return 0;
	}


	__super::Update_Rect();
	if (PtInRect(&m_tRect, GET(CMouse)->Get_Point()))
	{
		m_bMouseOn = true;
	}
	else
	{
		m_bMouseOn = false;
	}

	if (m_pItem != nullptr)
	{
		m_pItem->Set_Pos(m_tInfo.fX, m_tInfo.fY);
	}

	Clicked();
	return 0;
}

void CCell::Late_Update()
{

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


	if(m_pItem != nullptr)
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
			57,
			57,
			RGB(255, 0, 255)
		);
	}
}

void CCell::Release()
{
	Safe_Delete(m_pItem);
}

void CCell::Clicked()
{

	if (GET(CMouse)->Get_State() == CMouse::MouseState::EMPTY && m_bMouseOn && GET(CKeyMgr)->Key_Down(VK_LBUTTON))
	{
		//마우스에게 아이템 정보 전달
		if(m_pItem != nullptr)
			GET(CMouse)->PickItem(m_pItem->Clone());

		Safe_Delete(m_pItem);
	}
	if (m_bMouseOn && m_pItem == nullptr &&
		GET(CMouse)->Get_State() == CMouse::MouseState::PICKITEM && GET(CKeyMgr)->Key_Down(VK_LBUTTON))
	{
		//마우스에게 아이템 정보 해제
		Safe_Delete(m_pItem);
		m_pItem = GET(CMouse)->Get_Item()->Clone();
		GET(CMouse)->Set_State(CMouse::MouseState::EMPTY);
		GET(CMouse)->Delete_Item();
	}
}
