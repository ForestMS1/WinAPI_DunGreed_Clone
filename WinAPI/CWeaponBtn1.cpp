#include "pch.h"
#include "CWeaponBtn1.h"

CWeaponBtn1::CWeaponBtn1() : m_pEquipedItem(nullptr)
{
}

CWeaponBtn1::CWeaponBtn1(CUI* pParentUI) : m_pEquipedItem(nullptr)
{
    m_pParentUI = pParentUI;
}

CWeaponBtn1::~CWeaponBtn1()
{
}

void CWeaponBtn1::Initialize()
{
    m_tInfo.fCX = 57.f;
    m_tInfo.fCY = 57.f;
	m_tInfo.fX = m_pParentUI->Get_Rect()->left + 38;
	m_tInfo.fY = m_pParentUI->Get_Rect()->top + 53;
}

int CWeaponBtn1::Update()
{
	CUI::Update();
	__super::Update_Rect();
	if (PtInRect(&m_tRect, GET(CMouse)->Get_Point()))
	{
		m_bMouseOn = true;
	}
	else
	{
		m_bMouseOn = false;
	}
	Cliked();

    return 0;
}

void CWeaponBtn1::Late_Update()
{
	CUI::Late_Update();
}

void CWeaponBtn1::Render(HDC hDC)
{
	CUI::Render(hDC);

	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	if (m_pEquipedItem != nullptr)
	{
		HDC hItemDC = GET(CResourceMgr)->Find_Bmp(m_pEquipedItem->Get_FrameKey());
		GdiTransparentBlt(
			hDC,
			m_tRect.left,
			m_tRect.top,
			m_tInfo.fCX,
			m_tInfo.fCY,
			hItemDC,
			0,
			0,
			m_pEquipedItem->Get_FrameWidth(),
			m_pEquipedItem->Get_FrameHeight(),
			RGB(255, 0, 255)
		);
	}
}

void CWeaponBtn1::Release()
{
}

void CWeaponBtn1::Cliked()
{
	if (!m_bIsOpen)
	{
		return;
	}

	if (GET(CMouse)->Get_State() == CMouse::MouseState::EMPTY && m_bMouseOn && GET(CKeyMgr)->Key_Down(VK_LBUTTON))
	{
		//마우스에게 아이템 정보 전달
		GET(CMouse)->PickItem(m_pEquipedItem);

		m_pEquipedItem = nullptr;
	}
	if (m_bMouseOn && m_pEquipedItem == nullptr &&
		GET(CMouse)->Get_State() == CMouse::MouseState::PICKITEM && GET(CKeyMgr)->Key_Down(VK_LBUTTON))
	{
		//마우스에게 아이템 정보 해제
		m_pEquipedItem = GET(CMouse)->Get_Item();
		GET(CMouse)->Set_State(CMouse::MouseState::EMPTY);
		GET(CMouse)->Set_Item(nullptr);
	}

}