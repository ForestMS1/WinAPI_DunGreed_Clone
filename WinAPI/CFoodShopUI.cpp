#include "pch.h"
#include "CFoodShopUI.h"
CFoodShopUI::CFoodShopUI() : m_bMouseOn(false)
{

}

CFoodShopUI::~CFoodShopUI()
{
	Release();
}

void CFoodShopUI::Initialize()
{

	m_tInfo.fCX = WINCX;
	m_tInfo.fCY = WINCY;
	m_tInfo.fX = WINCX >> 1;
	m_tInfo.fY = WINCY >> 1;
	__super::Update_Rect();

	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/FoodShop/Base_0.bmp", L"Base_0");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/FoodShop/Base_3.bmp", L"Base_3");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/FoodShop/GoldCoin.bmp", L"GoldCoin");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/FoodShop/Label.bmp", L"Label");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/FoodShop/RestaurantMenu.bmp", L"RestaurantMenu");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/FoodShop/RestaurantMenuSelected.bmp", L"RestaurantMenuSelected");
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
		//ItemVec[0] = dynamic_cast<CShopItemUI*>(m_vecChildUI[0])->GetItem()->Clone();
		//ItemVec[1] = dynamic_cast<CShopItemUI*>(m_vecChildUI[1])->GetItem()->Clone();
	}

	for (auto& pChild : m_vecChildUI)
	{
		pChild->Initialize();
	}
}

int CFoodShopUI::Update()
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

void CFoodShopUI::Late_Update()
{
	for (auto& pChild : m_vecChildUI)
	{
		pChild->Late_Update();
	}
}

void CFoodShopUI::Render(HDC hDC)
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

void CFoodShopUI::Release()
{
	for (auto& pChild : m_vecChildUI)
	{
		Safe_Delete(pChild);
	}
	m_vecChildUI.clear();
}

void CFoodShopUI::Clicked()
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