#include "pch.h"
#include "CAbilityUI.h"
#include "CShopItemUI.h"
#include "CCosmosSword.h"
#include "CGatlingGun.h"
#include "CAbilityGreedBackGround.h"
#include "CAbilityWrathBackGround.h"
#include "CAbilityPatienceBackGround.h"
CAbilityUI::CAbilityUI() : m_bMouseOn(false)
{
	m_eRender = UI;
}

CAbilityUI::~CAbilityUI()
{
	Release();
}

void CAbilityUI::Initialize()
{
	m_iFrameWidth = WINCX;
	m_iFrameHeight = WINCY;
	m_tInfo.fCX = m_iFrameWidth;
	m_tInfo.fCY = m_iFrameHeight;
	m_tInfo.fX = WINCX >> 1;
	m_tInfo.fY = WINCY >> 1;
	__super::Update_Rect();

	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/Ability/AbilityTitle.bmp", L"AbilityTitle");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/Ability/AbilityTextBar.bmp", L"AbilityTextBar");



	CUI* pAbilityUI = new CAbilityGreedBackGround;
	pAbilityUI->Set_Pos(m_tRect.left + 150, m_tRect.top + 300);
	AddChildUI(pAbilityUI);


	pAbilityUI = new CAbilityWrathBackGround;
	pAbilityUI->Set_Pos(m_tRect.left + 400, m_tRect.top + 300);
	AddChildUI(pAbilityUI);

	pAbilityUI = new CAbilityPatienceBackGround;
	pAbilityUI->Set_Pos(m_tRect.left + 650, m_tRect.top + 300);
	AddChildUI(pAbilityUI);


	for (auto& pChild : m_vecChildUI)
	{
		pChild->Initialize();
	}
}

int CAbilityUI::Update()
{
	if (!m_bIsOpen)
		return 0;
	__super::Update_Rect();
	for (auto& pChild : m_vecChildUI)
	{
		pChild->Update();
	}

	return 0;
}

void CAbilityUI::Late_Update()
{
	if (!m_bIsOpen)
		return;
	for (auto& pChild : m_vecChildUI)
	{
		pChild->Late_Update();
	}
}

void CAbilityUI::Render(HDC hDC)
{
	if (!m_bIsOpen)
		return;
	HDC hMemDC = GET(CResourceMgr)->Find_Bmp(L"AbilityTitle");
	GdiTransparentBlt(
		hDC,
		m_tRect.left,
		m_tRect.top,
		WINCX,
		32 * 3,
		hMemDC,
		0,
		0,
		320,
		32,
		RGB(255, 0, 255)
	);
	for (auto& pChild : m_vecChildUI)
	{
		pChild->Render(hDC);
	}
}

void CAbilityUI::Release()
{
	for (auto& pChild : m_vecChildUI)
	{
		Safe_Delete(pChild);
	}
	m_vecChildUI.clear();
}

void CAbilityUI::Clicked()
{

}