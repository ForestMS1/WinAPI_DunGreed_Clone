#include "pch.h"
#include "CMapTileUI.h"
#include "CCamera.h"
#include "CResourceMgr.h"

CMapTileUI::CMapTileUI() : m_iCurTileX(0), m_iCurTileY(0)
{
}

CMapTileUI::~CMapTileUI()
{
}

void CMapTileUI::Initialize()
{
	m_tInfo.fX = WINCX - 150.f;
	m_tInfo.fY = 200.f;
	m_tInfo.fCX = 300.f;
	m_tInfo.fCY = 400.f;
}

void CMapTileUI::Update()
{
	if (!m_bIsOpen) return;

	Vec2 pos = Vec2(m_tInfo.fX, m_tInfo.fY);

	__super::Update_Rect();
	
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
}

void CMapTileUI::Render(HDC hDC)
{
	if (!m_bIsOpen) return;
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);

	HDC hMemDC = GET(CResourceMgr)->Find_Bmp(L"MapTile");

	int frameWidth = 512;
	int frameHeight = 512;


	GdiTransparentBlt(
		hDC,
		(int)(m_tRect.left),				// 복사 받을 공간의 LEFT	
		(int)(m_tRect.top),				// 복사 받을 공간의 TOP
		m_tInfo.fCX,												// 복사 받을 공간의 가로 
		m_tInfo.fCY,												// 복사 받을 공간의 세로 
		hMemDC,														// 복사 할 DC
		0,														// 원본이미지 left
		0,														// 원본이미지 top
		frameWidth,													// 원본이미지 가로
		frameHeight,												// 원본이미지 세로
		RGB(255, 0, 255)
	);
	//Rectangle(hDC, m_CurTileRect.left, m_CurTileRect.top, m_CurTileRect.right, m_CurTileRect.bottom);
}

void CMapTileUI::Release()
{
}
