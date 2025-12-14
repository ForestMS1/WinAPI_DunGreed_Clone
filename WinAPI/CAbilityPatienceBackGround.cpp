#include "pch.h"
#include "CAbilityPatienceBackGround.h"
#include "CAbilityPatienceBtn.h"
CAbilityPatienceBackGround::CAbilityPatienceBackGround()
{
}

CAbilityPatienceBackGround::~CAbilityPatienceBackGround()
{
	Release();
}

void CAbilityPatienceBackGround::Initialize()
{
	m_iFrameWidth = 58;
	m_iFrameHeight = 111;

	m_tInfo.fCX = m_iFrameWidth * 3;
	m_tInfo.fCY = m_iFrameHeight * 3;
	__super::Update_Rect();

	m_tFrame.iStart = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.iEnd = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();
	m_wsFrameKey = L"AbilityBackground_Patience";
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/Ability/AbilityBackground_Patience.bmp", L"AbilityBackground_Patience");


	CUI* btn = new CAbilityPatienceBtn;
	btn->Set_Pos(m_tRect.left + m_tInfo.fCX * 0.5, m_tRect.bottom - 30);
	AddChildUI(btn);
	for (auto& pChildUI : m_vecChildUI)
	{
		pChildUI->Initialize();
	}
	AddFontResource(TEXT("Aa카시오페아"));
	m_hFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0,
		HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("Aa카시오페아"));
}

int CAbilityPatienceBackGround::Update()
{
	__super::Update_Rect();
	for (auto& pChildUI : m_vecChildUI)
	{
		pChildUI->Update();
	}
	return 0;
}

void CAbilityPatienceBackGround::Late_Update()
{
	for (auto& pChildUI : m_vecChildUI)
	{
		pChildUI->Late_Update();
	}
}

void CAbilityPatienceBackGround::Render(HDC hDC)
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
	wstring text = L"민첩";
	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(255, 255, 255));
	TextOut(hDC, m_tRect.left + 75, m_tRect.top + 120, text.c_str(), (int)text.size());
	text = to_wstring(GET(CPlayerMgr)->GetAddMaxDashCount()).append(L" + 추가대쉬");
	TextOut(hDC, m_tRect.left + 35, m_tRect.bottom - 120, text.c_str(), (int)text.size());
	SelectObject(hDC, hOldFont);
}

void CAbilityPatienceBackGround::Release()
{
	if (m_hFont)
	{
		DeleteObject(m_hFont);
		m_hFont = NULL;
	}
	RemoveFontResource(TEXT("Aa카시오페아"));
}