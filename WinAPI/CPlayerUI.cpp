#include "pch.h"
#include "CPlayerUI.h"
#include "CPlayerHpBar.h"
#include "CEquipedUI.h"

CPlayerUI::CPlayerUI()
{
	m_pPlayer = nullptr;
}
CPlayerUI::CPlayerUI(CObj* pPlayer)
{
	m_pPlayer = pPlayer;
}

CPlayerUI::~CPlayerUI()
{
	Release();
}

void CPlayerUI::Initialize()
{
	m_tInfo.fCX = WINCX;
	m_tInfo.fCY = WINCY;
	m_tInfo.fX = WINCX >> 1;
	m_tInfo.fY = WINCY >> 1;

	m_bIsOpen = true;

	if (m_vecChildUI.empty())
	{
		AddChildUI(new CPlayerHpBar);
		AddChildUI(new CEquipedUI);
	}

	for (auto& pChildUI : m_vecChildUI)
	{
		pChildUI->Initialize();
	}
}

int CPlayerUI::Update()
{
	for (auto& pChildUI : m_vecChildUI)
	{
		pChildUI->Update();
	}
	return 0;
}

void CPlayerUI::Late_Update()
{
	for (auto& pChildUI : m_vecChildUI)
	{
		pChildUI->Late_Update();
	}
}

void CPlayerUI::Render(HDC hDC)
{
	if (!m_bIsOpen) return;

	for (auto& pChildUI : m_vecChildUI)
	{
		pChildUI->Render(hDC);
	}
}

void CPlayerUI::Release()
{
	for (auto& pChildUI : m_vecChildUI)
	{
		Safe_Delete(pChildUI);
	}
	m_vecChildUI.clear();
}
