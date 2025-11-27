#include "pch.h"
#include "CMapTileUI.h"
#include "CCamera.h"
#include "CResourceMgr.h"

CMapTileUI::CMapTileUI()
{
}

CMapTileUI::~CMapTileUI()
{
}

void CMapTileUI::Initialize()
{
	m_tInfo.fX = WINCX - 300.f;
	m_tInfo.fY = WINCY - 400.f;
	m_tInfo.fCX = 300.f;
	m_tInfo.fCY = 400.f;
}

void CMapTileUI::Update()
{
	if (!m_bIsOpen) return;

	Vec2 pos = Vec2(m_tInfo.fX, m_tInfo.fY);

	//m_tInfo.fX = GET(CCamera)->GetRenderPos(Vec2(pos.fX, pos.fY)).fX;
	//m_tInfo.fY = GET(CCamera)->GetRenderPos(Vec2(pos.fX, pos.fY)).fY;

	__super::Update_Rect();
	return ;
}

void CMapTileUI::Late_Update()
{
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
		(int)(m_tRect.left - GET(CCamera)->GetDiff().fX),				// 복사 받을 공간의 LEFT	
		(int)(m_tRect.top - GET(CCamera)->GetDiff().fY),				// 복사 받을 공간의 TOP
		m_tInfo.fCX,												// 복사 받을 공간의 가로 
		m_tInfo.fCY,												// 복사 받을 공간의 세로 
		hMemDC,														// 복사 할 DC
		0,														// 원본이미지 left
		0,														// 원본이미지 top
		frameWidth,													// 원본이미지 가로
		frameHeight,												// 원본이미지 세로
		RGB(255, 0, 255)
	);
}

void CMapTileUI::Release()
{
}
