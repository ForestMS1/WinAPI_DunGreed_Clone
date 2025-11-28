#include "pch.h"
#include "CMapTileOptionUI.h"
#include "CTileOptionBtn.h"
#include "CResourceMgr.h"

CMapTileOptionUI::CMapTileOptionUI() : m_iScrollX(0), m_bMouseOn(false)
{
}

CMapTileOptionUI::~CMapTileOptionUI()
{
	Release();
}

void CMapTileOptionUI::Initialize()
{
	m_tInfo.fX = 128;
	m_tInfo.fY = WINCY - 16;
	m_tInfo.fCX = TILECX * 8;
	m_tInfo.fCY = TILECY;

	m_bIsOpen = true;

	__super::Update_Rect();

	for (int i = 0; i < m_tInfo.fCX / TILECX; ++i)
	{
		float fX = m_tRect.left + (TILECX * i) + (TILECX >> 1);
		AddChildUI(new CTileOptionBtn(fX, m_tInfo.fY));
	}

	for (auto& pChildUI : m_vecChildUI)
	{
		pChildUI->Initialize();
	}
}

int CMapTileOptionUI::Update()
{
	for (auto& pChildUI : m_vecChildUI)
	{
		pChildUI->Update();
	}
	__super::Update_Rect();

	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (PtInRect(&m_tRect, pt))
		m_bMouseOn = true;
	else
		m_bMouseOn = false;
	
	return 0;
}

void CMapTileOptionUI::Late_Update()
{
	for (auto& pChildUI : m_vecChildUI)
	{
		pChildUI->Late_Update();
	}
}

void CMapTileOptionUI::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	for (auto& pChildUI : m_vecChildUI)
	{
		pChildUI->Render(hDC);
	}
}

void CMapTileOptionUI::Release()
{
	for (auto& pChildUI : m_vecChildUI)
	{
		Safe_Delete(pChildUI);
	}
	m_vecChildUI.clear();
}
