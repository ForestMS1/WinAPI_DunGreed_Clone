#include "pch.h"
#include "CShopItemUI.h"

CShopItemUI::CShopItemUI() : m_bMouseOn(false), m_pItem(nullptr)
{
}

CShopItemUI::~CShopItemUI()
{
	Release();
}

void CShopItemUI::Initialize()
{
	m_iFrameWidth = 107;
	m_iFrameHeight = 23;
	m_tInfo.fCX = m_iFrameWidth * 3;
	m_tInfo.fCY = m_iFrameHeight * 3;
	__super::Update_Rect();


	if (m_pItem != nullptr)
	{
		m_pItem->Initialize();
		int offsetX = 11 * 3;
		int offsetY = 11 * 3;
		m_pItem->Set_Pos(m_tRect.left + offsetX, m_tRect.top + offsetY);
	}

	AddFontResource(TEXT("Aa카시오페아"));
	m_hFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0,
		HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("Aa카시오페아"));
}

int CShopItemUI::Update()
{
	__super::Update_Rect();

	if (!m_bIsOpen)
		return 0;

	if (PtInRect(&m_tRect, GET(CMouse)->Get_Point()))
	{
		m_bMouseOn = true;
	}
	else
	{
		m_bMouseOn = false;
	}

	if (m_pItem != nullptr)
	{
		int offsetX = 11 * 3;
		int offsetY = 11 * 3;
		m_pItem->Set_Pos(m_tRect.left + offsetX, m_tRect.top + offsetY);
	}

	Clicked();
	return 0;
}

void CShopItemUI::Late_Update()
{

}

void CShopItemUI::Render(HDC hDC)
{
	m_wsFrameKey = L"";
	if (m_bMouseOn)
		m_wsFrameKey = L"ShopItem_Selected";
	else
		m_wsFrameKey = L"ShopItem";

	HDC hMemDC = GET(CResourceMgr)->Find_Bmp(m_wsFrameKey);

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
	//아이템 출력
	if (m_pItem != nullptr)
	{
		HDC hItemDC = GET(CResourceMgr)->Find_Bmp(m_pItem->Get_FrameKey());
		GdiTransparentBlt(
			hDC,
			m_tRect.left + 10,
			m_tRect.top,
			m_pItem->Get_FrameWidth(),
			m_pItem->Get_FrameHeight(),
			hItemDC,
			0,
			0,
			m_pItem->Get_FrameWidth(),
			m_pItem->Get_FrameHeight(),
			RGB(255, 0, 255)
		);

		HFONT hOldFont = (HFONT)SelectObject(hDC, m_hFont);
		wstring text = m_pItem->GetItemName();
		SetBkMode(hDC, TRANSPARENT);
		SetTextColor(hDC, RGB(255, 255, 255));
		TextOut(hDC, m_tRect.left + 75, m_tRect.top + 10, text.c_str(), (int)text.size());
		text = to_wstring(m_pItem->GetShopPrice());
		TextOut(hDC, m_tRect.left + 230, m_tRect.top + 35, text.c_str(), (int)text.size());
		SelectObject(hDC, hOldFont);
	}
}

void CShopItemUI::Release()
{
	Safe_Delete(m_pItem);
	if (m_hFont)
	{
		DeleteObject(m_hFont);
		m_hFont = NULL;
	}
	RemoveFontResource(TEXT("Aa카시오페아"));
}

void CShopItemUI::Clicked()
{

	if (GET(CMouse)->Get_State() == CMouse::MouseState::EMPTY && m_bMouseOn && GET(CKeyMgr)->Key_Down(VK_LBUTTON))
	{
		//마우스에게 아이템 정보 전달
		if (m_pItem != nullptr)
		{
			if (GET(CPlayerMgr)->GetGold() >= m_pItem->GetShopPrice())
			{
				GET(CMouse)->PickItem(m_pItem->Clone());
				GET(CPlayerMgr)->SetGold(GET(CPlayerMgr)->GetGold() - m_pItem->GetShopPrice());
				GET(CSoundMgr)->PlaySoundW(L"GetItem.wav", SOUND_EFFECT, 1.f);
			}
		}
		//vector<CItem*>& ItemVec = GET(CPlayerMgr)->GetItemVec();
		
		//Safe_Delete(m_pItem);
	}
}
