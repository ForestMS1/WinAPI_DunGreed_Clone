#include "pch.h"
#include "CMapTileUI.h"
#include "CCamera.h"
#include "CResourceMgr.h"
#include "CTileBtn.h"
#include "CKeyMgr.h"
CMapTileUI::CMapTileUI() : m_iScrollX(0)
{
}

CMapTileUI::~CMapTileUI()
{
	Release();
}

void CMapTileUI::Initialize()
{
	//m_tInfo.fX = WINCX - 150.f;
	//m_tInfo.fY = 200.f;
	//m_tInfo.fCX = 300.f;
	//m_tInfo.fCY = 400.f;

	m_tInfo.fX = WINCX>>1;
	m_tInfo.fY = WINCY>>1;
	m_tInfo.fCX = 1024;
	m_tInfo.fCY = 512;

	__super::Update_Rect();

	for (int i = 0; i < 32; ++i)
	{
		for (int j = 0; j < 64; ++j)
		{
			float fX = m_tRect.left + (BMPTILECX * j) + (BMPTILECX >> 1);
			float fY = m_tRect.top + (BMPTILECY * i) + (BMPTILECY >> 1);
			//float fX = m_tRect.left + (TILECX * j) + (TILECX >> 1);
			//float fY = m_tRect.top + (TILECY * i) + (TILECY >> 1);
			AddChildUI(new CTileBtn(fX, fY));
		}
	}

	for (auto& pChildUI : m_vecChildUI)
	{
		pChildUI->Initialize();
	}
}

int CMapTileUI::Update()
{
	if (!m_bIsOpen) return 0;

	Key_Input();


	for (auto& pChildUI : m_vecChildUI)
	{
		pChildUI->Update();
	}
	__super::Update_Rect();
	
	return 0;
}

void CMapTileUI::Late_Update()
{
	for (auto& pChildUI : m_vecChildUI)
	{
		pChildUI->Late_Update();
	}
}

void CMapTileUI::Render(HDC hDC)
{
	if (!m_bIsOpen) return;
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	HDC hMemDC = GET(CResourceMgr)->Find_Bmp(L"MapTile");

	int frameWidth = m_tInfo.fCX;		//512
	int frameHeight = m_tInfo.fCY;		//512 사진사이즈

	int SrcX = 0 + m_iScrollX;


	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
	//GdiTransparentBlt(
	//	hDC,
	//	(int)(m_tRect.left),									// 복사 받을 공간의 LEFT	
	//	(int)(m_tRect.top),										// 복사 받을 공간의 TOP
	//	m_tInfo.fCX,											// 복사 받을 공간의 가로 
	//	m_tInfo.fCY,											// 복사 받을 공간의 세로 
	//	hMemDC,													// 복사 할 DC
	//	SrcX,													// 원본이미지 left
	//	0,														// 원본이미지 top
	//	frameWidth,												// 원본이미지 가로
	//	frameHeight,											// 원본이미지 세로
	//	RGB(255, 0, 255)
	//);

	for (auto& pChildUI : m_vecChildUI)
	{
		pChildUI->Render(hDC);
	}
}

void CMapTileUI::Release()
{
	for (auto& pChildUI : m_vecChildUI)
	{
		Safe_Delete(pChildUI);
	}
	m_vecChildUI.clear();
}

void CMapTileUI::Key_Input()
{
	if (GET(CKeyMgr)->Key_Pressing('J'))
	{
		if (!(0 + m_iScrollX <= 1))
		{
			m_iScrollX -= 1;
		}
	}
	if (GET(CKeyMgr)->Key_Pressing('K'))
	{
		if (!(0 + m_iScrollX >= 512 - m_tInfo.fCX))
		{
			m_iScrollX += 1;
		}
	}
}
