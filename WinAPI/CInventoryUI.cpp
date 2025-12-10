#include "pch.h"
#include "CInventoryUI.h"
#include "CCell.h"
#include "CEquipSlotOn.h"
#include "CGatlingGun.h"
#include "CCosmosSword.h"

CInventoryUI::CInventoryUI()
{
	m_pPlayer = nullptr;
}

CInventoryUI::CInventoryUI(CObj* pPlayer)
{
	m_pPlayer = pPlayer;
}

CInventoryUI::~CInventoryUI()
{
	Release();
}

void CInventoryUI::Initialize()
{
	m_tInfo.fCX = 369.f;
	m_tInfo.fCY = 564.f;
	m_tInfo.fX = WINCX - m_tInfo.fCX * 0.5f;
	m_tInfo.fY = m_tInfo.fCY * 0.5f;
	__super::Update_Rect();

	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/Inventory/InventoryBase.bmp", L"InventoryBase");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/Inventory/accessory.bmp", L"accessory");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/Inventory/Cell.bmp", L"Cell");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/Inventory/Cell_On.bmp", L"Cell_On");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/Inventory/EquipSlot1On.bmp", L"EquipSlot1On");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/Inventory/EquipSlot2On.bmp", L"EquipSlot2On");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/Inventory/InventoryExit.bmp", L"InventoryExit");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/Inventory/defense.bmp", L"defense");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/Inventory/hp.bmp", L"hp");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/Inventory/power.bmp", L"power");

	float offsetX = 57.f;
	float offsetY = 310.f;
	vector<CItem*>& ItemVec = GET(CPlayerMgr)->GetItemVec();
	for (size_t i = 0; i < 3; ++i)
	{
		for (size_t j = 0; j < 5; ++j)
		{
			CUI* pCell = new CCell(5 * i + j);
			pCell->Set_Pos(m_tRect.left + (57 + 10) * j + offsetX, m_tRect.top + (57 + 10) * i + offsetY);
			AddChildUI(pCell);
			pCell->Initialize();

			if (ItemVec[5 * i + j] == nullptr)
				dynamic_cast<CCell*>(m_vecChildUI[5 * i + j])->SetItem(nullptr);
			else
				dynamic_cast<CCell*>(m_vecChildUI[5 * i + j])->SetItem(ItemVec[5 * i + j]->Clone());

		}
	}
	//0~14¹øÀº ÅÛÄ­
	if (GET(CSceneMgr)->GetCurSceneID() == SCENE_TEST)
	{
		dynamic_cast<CCell*>(m_vecChildUI[0])->SetItem(new CCosmosSword);
		dynamic_cast<CCell*>(m_vecChildUI[1])->SetItem(new CGatlingGun);
		ItemVec[0] = dynamic_cast<CCell*>(m_vecChildUI[0])->GetItem()->Clone();
		ItemVec[1] = dynamic_cast<CCell*>(m_vecChildUI[1])->GetItem()->Clone();
	}

	CUI* pESlot = new CEquipSlotOn;
	pESlot->Set_Pos(m_tRect.left + 110, m_tRect.top + 127);
	AddChildUI(pESlot);

	for (auto& pChild : m_vecChildUI)
	{
		pChild->Initialize();
	}
}

int CInventoryUI::Update()
{
	for (auto& pChild : m_vecChildUI)
	{
		pChild->Update();
	}
	Key_Input();
	return 0;
}

void CInventoryUI::Late_Update()
{
	for (auto& pChild : m_vecChildUI)
	{
		pChild->Late_Update();
	}
}

void CInventoryUI::Render(HDC hDC)
{
	if (!m_bIsOpen)
		return;
	HDC hMemDC = GET(CResourceMgr)->Find_Bmp(L"InventoryBase");
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
	for (auto& pChild : m_vecChildUI)
	{
		pChild->Render(hDC);
	}
}

void CInventoryUI::Release()
{
	for (auto& pChild : m_vecChildUI)
	{
		Safe_Delete(pChild);
	}
	m_vecChildUI.clear();
}

void CInventoryUI::Key_Input()
{
	if (GET(CKeyMgr)->Key_Down('Z'))
	{
		GET(CSoundMgr)->PlaySoundW(L"Inventory_open.wav", SOUND_EFFECT, 1.0f);
		if (m_bIsOpen)
			Close();
		else
			Open();
	}
}