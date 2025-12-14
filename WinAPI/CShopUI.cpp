#include "pch.h"
#include "CShopUI.h"
#include "CShopItemUI.h"
#include "CCosmosSword.h"
#include "CGatlingGun.h"
#include "CLala.h"
CShopUI::CShopUI() : m_bMouseOn(false)
{

}

CShopUI::~CShopUI()
{
	Release();
}

void CShopUI::Initialize()
{
	m_iFrameWidth = 122;
	m_iFrameHeight = 188;
	m_tInfo.fCX = m_iFrameWidth * 3;
	m_tInfo.fCY = m_iFrameHeight * 3;
	m_tInfo.fX = m_tInfo.fCX * 0.5f;
	m_tInfo.fY = m_tInfo.fCY * 0.5f;
	__super::Update_Rect();

	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/Shop/DungeonShopBase.bmp", L"DungeonShopBase");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/Shop/ShopItem.bmp", L"ShopItem");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/Shop/ShopItem_Selected.bmp", L"ShopItem_Selected");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/FoodShop/RestaurantMenuSell.bmp", L"RestaurantMenuSell");

	float offsetX = 90.f * 2;
	float offsetY = 69;

	for (size_t i = 0; i < 3; ++i)
	{
		CUI* pShopItemUI = new CShopItemUI;
		pShopItemUI->Set_Pos(m_tRect.left + offsetX, m_tRect.top + offsetY * (i+1) + 70);
		AddChildUI(pShopItemUI);
		pShopItemUI->Initialize();
	}
	//0~3번
	if (GET(CSceneMgr)->GetCurSceneID() == SCENE_TEST)
	{
		dynamic_cast<CShopItemUI*>(m_vecChildUI[0])->SetItem(new CCosmosSword);
		dynamic_cast<CShopItemUI*>(m_vecChildUI[1])->SetItem(new CGatlingGun);
		dynamic_cast<CShopItemUI*>(m_vecChildUI[2])->SetItem(new CLala);
		//ItemVec[0] = dynamic_cast<CShopItemUI*>(m_vecChildUI[0])->GetItem()->Clone();
		//ItemVec[1] = dynamic_cast<CShopItemUI*>(m_vecChildUI[1])->GetItem()->Clone();
	}

	for (auto& pChild : m_vecChildUI)
	{
		pChild->Initialize();
	}
}

int CShopUI::Update()
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
	for (auto& pChild : m_vecChildUI)
	{
		pChild->Update();
	}
	Clicked();
	return 0;
}

void CShopUI::Late_Update()
{
	for (auto& pChild : m_vecChildUI)
	{
		pChild->Late_Update();
	}
}

void CShopUI::Render(HDC hDC)
{
	if (!m_bIsOpen)
		return;
	HDC hMemDC = GET(CResourceMgr)->Find_Bmp(L"DungeonShopBase");
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

void CShopUI::Release()
{
	for (auto& pChild : m_vecChildUI)
	{
		Safe_Delete(pChild);
	}
	m_vecChildUI.clear();
}

void CShopUI::Clicked()
{
	if (m_bMouseOn &&
		GET(CMouse)->Get_State() == CMouse::MouseState::PICKITEM && GET(CKeyMgr)->Key_Down(VK_LBUTTON))
	{
		GET(CPlayerMgr)->SetGold(GET(CPlayerMgr)->GetGold() + GET(CMouse)->Get_Item()->GetShopPrice());
		//마우스에게 아이템 정보 해제
		GET(CMouse)->Set_State(CMouse::MouseState::EMPTY);
		GET(CMouse)->Delete_Item();
		GET(CSoundMgr)->PlaySoundW(L"sell.wav", CHANNELID::SOUND_EFFECT, 1.f);
	}
}