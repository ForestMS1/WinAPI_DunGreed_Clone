#include "pch.h"
#include "CMapTileUI.h"
#include "CCamera.h"
#include "CResourceMgr.h"
#include "CTileBtn.h"
#include "CKeyMgr.h"
CMapTileUI::CMapTileUI() : m_iCurTileX(0), m_iCurTileY(0)
,m_iScrollX(0)
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
	m_tInfo.fX = WINCX>>1;
	m_tInfo.fY = WINCY>>1;
	m_tInfo.fCX = 512.f;
	m_tInfo.fCY = 512.f;

	for (int i = 0; i < 32; ++i)
	{
		for (int j = 0; j < 32; ++j)
		{
			AddChildUI(new CTileBtn);
		}
	}

	for (auto& pChildUI : m_vecChildUI)
	{
		pChildUI->Initialize();
	}
}

void CMapTileUI::Update()
{
	if (!m_bIsOpen) return;

	Vec2 pos = Vec2(m_tInfo.fX, m_tInfo.fY);

	__super::Update_Rect();

	Key_Input();


	for (auto& pChildUI : m_vecChildUI)
	{
		pChildUI->Update();
	}
	
	return ;
}

void CMapTileUI::Late_Update()
{
	//float xRatio = m_tInfo.fCX / WINCX;
	//float yRatio = m_tInfo.fCY / WINCY;

	//m_CurTileInfo.fCX = TILECX * xRatio;
	//m_CurTileInfo.fCY = TILECY * yRatio;
	//m_CurTileInfo.fX = m_tInfo.fX + m_CurTileInfo.fCX * 0.5f + m_iCurTileX * m_CurTileInfo.fCX;
	//m_CurTileInfo.fY = m_tInfo.fY + m_CurTileInfo.fCY * 0.5f + m_iCurTileY * m_CurTileInfo.fCY;

	//m_CurTileRect.left = m_tRect.left - m_CurTileInfo.fCX * 0.5f;
	//m_CurTileRect.top = m_tRect.top - m_CurTileInfo.fCY * 0.5f;
	//m_CurTileRect.right = m_tRect.left + m_CurTileInfo.fCX * 0.5f;
	//m_CurTileRect.top = m_tRect.top + m_CurTileInfo.fCY * 0.5f;

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


	GdiTransparentBlt(
		hDC,
		(int)(m_tRect.left),				// 복사 받을 공간의 LEFT	
		(int)(m_tRect.top),				// 복사 받을 공간의 TOP
		m_tInfo.fCX,													// 복사 받을 공간의 가로 
		m_tInfo.fCY,												// 복사 받을 공간의 세로 
		hMemDC,														// 복사 할 DC
		SrcX,											// 원본이미지 left
		0,														// 원본이미지 top
		frameWidth,								// 원본이미지 가로
		frameHeight,											// 원본이미지 세로
		RGB(255, 0, 255)
	);

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
