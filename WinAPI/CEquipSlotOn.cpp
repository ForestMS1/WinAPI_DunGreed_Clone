#include "pch.h"
#include "CEquipSlotOn.h"

CEquipSlotOn::CEquipSlotOn() : m_pEquipedItem(nullptr), m_bMouseOn(false), m_bClicked(false)
{
	
}

CEquipSlotOn::CEquipSlotOn(CUI* pParentUI) : m_pEquipedItem(nullptr), m_bMouseOn(false), m_bClicked(false)
{
	m_pParentUI = pParentUI;
}

CEquipSlotOn::~CEquipSlotOn()
{
	Release();
}

void CEquipSlotOn::Initialize()
{
	m_iFrameWidth = 141.f;
	m_iFrameHeight = 90.f;
	m_tInfo.fCX = m_iFrameWidth;
	m_tInfo.fCY = m_iFrameHeight;
	__super::Update_Rect();

	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/Inventory/EquipSlot1On.bmp", L"EquipSlot1On");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/Inventory/EquipSlot2On.bmp", L"EquipSlot2On");
}

int CEquipSlotOn::Update()
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
	return 0;
}

void CEquipSlotOn::Late_Update()
{
	CUI::Late_Update();
}

void CEquipSlotOn::Render(HDC hDC)
{
	CUI::Render(hDC);
	HDC hMemDC = GET(CResourceMgr)->Find_Bmp(L"EquipSlot1On");
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

void CEquipSlotOn::Release()
{
}

void CEquipSlotOn::Cliked()
{
	if (!m_bIsOpen)
	{
		//마우스에게 아이템 정보 해제
		GET(CMouse)->PutItem(m_pEquipedItem);

		m_bClicked = false;
		return;
	}

	if (!m_bClicked && m_bMouseOn && GET(CKeyMgr)->Key_Pressing(VK_LBUTTON))
	{
		if (m_pEquipedItem == nullptr)
		{
			if (GET(CMouse)->Get_State() != CMouse::MouseState::EMPTY)
			{
				GET(CMouse)->PutItem(m_pEquipedItem);
			}
		}
		else
		{
			m_bClicked = true;
			GET(CMouse)->PickItem(m_pEquipedItem);
			m_pEquipedItem = nullptr;
		}
	}
	else if (m_bClicked && GET(CKeyMgr)->Key_Pressing(VK_LBUTTON))
	{
		//마우스에게 아이템 정보 해제
		GET(CMouse)->PutItem(m_pEquipedItem);

		m_bClicked = false;
	}
}
