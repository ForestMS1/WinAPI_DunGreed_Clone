#include "pch.h"
#include "CAbilityWrathBackGround.h"
#include "CAbilityWrathBtn.h"
CAbilityWrathBackGround::CAbilityWrathBackGround()
{
}

CAbilityWrathBackGround::~CAbilityWrathBackGround()
{
	Release();
}

void CAbilityWrathBackGround::Initialize()
{
	m_iFrameWidth = 62;
	m_iFrameHeight = 116;

	m_tInfo.fCX = m_iFrameWidth * 3;
	m_tInfo.fCY = m_iFrameHeight * 3;
	__super::Update_Rect();

	m_tFrame.iStart = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.iEnd = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();
	m_wsFrameKey = L"AbilityBackground_Wrath";
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/Ability/AbilityBackground_Wrath.bmp", L"AbilityBackground_Wrath");


	CUI* btn = new CAbilityWrathBtn;
	btn->Set_Pos(m_tRect.left + m_tInfo.fCX * 0.5 + 5, m_tRect.bottom - 30);
	AddChildUI(btn);
	for (auto& pChildUI : m_vecChildUI)
	{
		pChildUI->Initialize();
	}
	AddFontResource(TEXT("Aa카시오페아"));
	m_hFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0,
		HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("Aa카시오페아"));
}

int CAbilityWrathBackGround::Update()
{
	__super::Update_Rect();
	for (auto& pChildUI : m_vecChildUI)
	{
		pChildUI->Update();
	}
	return 0;
}

void CAbilityWrathBackGround::Late_Update()
{
	for (auto& pChildUI : m_vecChildUI)
	{
		pChildUI->Late_Update();
	}
}

void CAbilityWrathBackGround::Render(HDC hDC)
{
	HDC hMemDC = GET(CResourceMgr)->Find_Bmp(m_wsFrameKey);

	GdiTransparentBlt(
		hDC,
		m_tRect.left,
		m_tRect.top,
		m_tInfo.fCX,
		m_tInfo.fCY,
		hMemDC,
		m_iFrameWidth * m_tFrame.iStart,
		m_iFrameHeight * m_tFrame.iMotion,
		m_iFrameWidth,
		m_iFrameHeight,
		RGB(255, 0, 255)
	);

	for (auto& pChildUI : m_vecChildUI)
	{
		pChildUI->Render(hDC);
	}

	HFONT hOldFont = (HFONT)SelectObject(hDC, m_hFont);
	wstring text = L"체력";
	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(255, 255, 255));
	TextOut(hDC, m_tRect.left + 75, m_tRect.top + 120, text.c_str(), (int)text.size());
	text = to_wstring(GET(CPlayerMgr)->GetAddMaxHp()).append(L" + 최대체력");
	TextOut(hDC, m_tRect.left + 35, m_tRect.bottom - 120, text.c_str(), (int)text.size());
	SelectObject(hDC, hOldFont);
}

void CAbilityWrathBackGround::Release()
{
	if (m_hFont)
	{
		DeleteObject(m_hFont);
		m_hFont = NULL;
	}
	RemoveFontResource(TEXT("Aa카시오페아"));
}