#include "pch.h"
#include "CWeaponBtn2.h"
#include "CWeapon.h"
#include "CGatlingGun.h"

CWeaponBtn2::CWeaponBtn2() : m_pEquipedItem(nullptr)
{
}

CWeaponBtn2::CWeaponBtn2(CUI* pParentUI) : m_pEquipedItem(nullptr)
{
	m_pParentUI = pParentUI;
}

CWeaponBtn2::~CWeaponBtn2()
{
	Release();
}

void CWeaponBtn2::Initialize()
{
	m_tInfo.fCX = 57.f;
	m_tInfo.fCY = 57.f;
	m_tInfo.fX = m_pParentUI->Get_Rect()->left + 200;
	m_tInfo.fY = m_pParentUI->Get_Rect()->top + 53;
	if (GET(CPlayerMgr)->GetEquip(L"Weapon2") != nullptr)
		m_pEquipedItem = GET(CPlayerMgr)->GetEquip(L"Weapon2")->Clone();
}

int CWeaponBtn2::Update()
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

void CWeaponBtn2::Late_Update()
{
	CUI::Late_Update();
}

void CWeaponBtn2::Render(HDC hDC)
{
	CUI::Render(hDC);
	if (m_pEquipedItem != nullptr)
	{
		HDC hItemDC = GET(CResourceMgr)->Find_Bmp(m_pEquipedItem->Get_FrameKey());
		int offsetX(0);
		if (m_pEquipedItem->Get_FrameWidth() < m_tInfo.fCX * 0.5f)
			offsetX = 20;

		GdiTransparentBlt(
			hDC,
			m_tRect.left + offsetX,
			m_tRect.top,
			m_pEquipedItem->Get_FrameWidth(),
			m_pEquipedItem->Get_FrameHeight(),
			hItemDC,
			0,
			0,
			m_pEquipedItem->Get_FrameWidth(),
			m_pEquipedItem->Get_FrameHeight(),
			RGB(255, 0, 255)
		);
	}
}

void CWeaponBtn2::Release()
{
	Safe_Delete(m_pEquipedItem);
}

void CWeaponBtn2::Cliked()
{
	if (!m_bIsOpen)
	{
		return;
	}

	if (GET(CMouse)->Get_State() == CMouse::MouseState::EMPTY && m_bMouseOn && GET(CKeyMgr)->Key_Down(VK_LBUTTON))
	{
		//마우스에게 아이템 정보 전달
		if (m_pEquipedItem != nullptr)
			GET(CMouse)->PickItem(m_pEquipedItem->Clone());
		Safe_Delete(m_pEquipedItem);
		GET(CPlayerMgr)->EquipWeapon(nullptr, L"Weapon2");
	}
	if (m_bMouseOn && m_pEquipedItem == nullptr &&
		GET(CMouse)->Get_State() == CMouse::MouseState::PICKITEM && GET(CKeyMgr)->Key_Down(VK_LBUTTON))
	{
		//마우스에게 아이템 정보 해제
		Safe_Delete(m_pEquipedItem);
		m_pEquipedItem = GET(CMouse)->Get_Item()->Clone();
		GET(CPlayerMgr)->EquipWeapon(m_pEquipedItem->Clone(), L"Weapon2");
		GET(CMouse)->Set_State(CMouse::MouseState::EMPTY);
		GET(CMouse)->Delete_Item();
	}

}