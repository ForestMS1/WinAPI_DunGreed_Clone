#include "pch.h"
#include "CXmasTextUI.h"
#include "CPresent.h"
CXmasTextUI::CXmasTextUI() : m_TextIdx(0), m_bCompleteGift(false)
{

}

CXmasTextUI::~CXmasTextUI()
{
	Release();
}

void CXmasTextUI::Initialize()
{
	m_tInfo.fCX = WINCX;
	m_tInfo.fCY = WINCY;
	m_tInfo.fX = WINCX >> 1;
	m_tInfo.fY = WINCY >> 1;
	__super::Update_Rect();

	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/BossIntro.bmp", L"TextBox");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/NPC/SantaStand.bmp", L"SantaStand");

	for (auto& pChild : m_vecChildUI)
	{
		pChild->Initialize();
	}

	AddFontResource(TEXT("Aa카시오페아"));
	m_hFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0,
		HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("Aa카시오페아"));

	m_vecText.push_back(L"안녕 나는 산타야! 선물을 주러 가야하는데 마녀가 길을 막고있어");
	m_vecText.push_back(L"마녀를 무찔러준다면 내가 확실히 보답해주지.");
	m_vecText.push_back(L"마녀와 가위바위보를 해서 지거나 비기면 체력이 깎이니 조심하라고!");
	m_vecText.push_back(L"마녀와 가위바위보를 대비한 선물을 준비했으니 챙겨가도록 해.");
}

int CXmasTextUI::Update()
{
	for (auto& pChild : m_vecChildUI)
	{
		pChild->Update();
	}
	Key_Input();
	return 0;
}

void CXmasTextUI::Late_Update()
{
	for (auto& pChild : m_vecChildUI)
	{
		pChild->Late_Update();
	}
}

void CXmasTextUI::Render(HDC hDC)
{
	if (!m_bIsOpen)
		return;

	HDC hSantaDC = GET(CResourceMgr)->Find_Bmp(L"SantaStand");
	GdiTransparentBlt(
		hDC,
		0,
		320,
		200,
		200,
		hSantaDC,
		0,
		0,
		2084,
		2084,
		RGB(255, 0, 255)
	);

	HDC hMemDC = GET(CResourceMgr)->Find_Bmp(L"TextBox");
	GdiTransparentBlt(
		hDC,
		m_tRect.left,
		m_tRect.top,
		m_tInfo.fCX,
		m_tInfo.fCY,
		hMemDC,
		0,
		0,
		100,
		100,
		RGB(255, 0, 255)
	);
	for (auto& pChild : m_vecChildUI)
	{
		pChild->Render(hDC);
	}

	HFONT hOldFont = (HFONT)SelectObject(hDC, m_hFont);
	wstring text = m_vecText[m_TextIdx];
	SetBkMode(hDC, TRANSPARENT);
	SetTextColor(hDC, RGB(255, 255, 255));
	TextOut(hDC, 0 + 150, WINCY - 100, text.c_str(), (int)text.size());
	SelectObject(hDC, hOldFont);
}

void CXmasTextUI::Release()
{
	for (auto& pChild : m_vecChildUI)
	{
		Safe_Delete(pChild);
	}
	m_vecChildUI.clear();

	if (m_hFont)
	{
		DeleteObject(m_hFont);
		m_hFont = NULL;
	}
	RemoveFontResource(TEXT("Aa카시오페아"));
}

void CXmasTextUI::Key_Input()
{
	if (!m_bIsOpen)
		return;
	if (GET(CKeyMgr)->Key_Down(VK_LBUTTON))
	{
		m_TextIdx++;
		if (m_TextIdx >= m_vecText.size())
		{
			m_bIsOpen = false;
			GET(CUIMgr)->Find_UI(L"PlayerUI")->Open();
			m_TextIdx = 0;
			GET(CSoundMgr)->StopAll();
			GET(CSoundMgr)->PlayBGM(L"2.IceField.wav", 1.f);
			//텍스트를 끝내면 선물 생성
			if (!m_bCompleteGift)
			{
				CObj* pLifeTresure = CAbstractFactory<CPresent>::Create(1650, 820);
				GET(CObjMgr)->AddObject(OBJ_NPC, pLifeTresure);
				m_bCompleteGift = true;
			}
		}
	}
}