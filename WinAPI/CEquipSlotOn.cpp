#include "pch.h"
#include "CEquipSlotOn.h"

CEquipSlotOn::CEquipSlotOn() : m_bMouseOn(false), m_bClicked(false)
, m_pWeaponBtn1(nullptr)
{
	
}

CEquipSlotOn::CEquipSlotOn(CUI* pParentUI) : m_bMouseOn(false), m_bClicked(false)
, m_pWeaponBtn1(nullptr)
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

	CUI* pESlot = new CWeaponBtn1;
	AddChildUI(pESlot);
	for (auto& pChild : m_vecChildUI)
	{
		pChild->Initialize();
	}

	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/Inventory/EquipSlot1On.bmp", L"EquipSlot1On");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/Inventory/EquipSlot2On.bmp", L"EquipSlot2On");
}

int CEquipSlotOn::Update()
{
	CUI::Update();
	__super::Update_Rect();

	for (auto& pChild : m_vecChildUI)
	{
		pChild->Update();
	}
	return 0;
}

void CEquipSlotOn::Late_Update()
{
	CUI::Late_Update();
	for (auto& pChild : m_vecChildUI)
	{
		pChild->Late_Update();
	}
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
	for (auto& pChild : m_vecChildUI)
	{
		pChild->Render(hDC);
	}
}

void CEquipSlotOn::Release()
{
	for (auto& pChild : m_vecChildUI)
	{
		Safe_Delete(pChild);
	}
	m_vecChildUI.clear();
}

