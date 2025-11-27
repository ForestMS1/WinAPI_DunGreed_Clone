#include "pch.h"
#include "CTile.h"
#include "CResourceMgr.h"
#include "CCamera.h"

CTile::CTile() : m_iOption(0)
{
	ZeroMemory(&m_tTileInfo, sizeof(TILEINFO));
}

CTile::~CTile()
{
	Release();
}

void CTile::Initialize()
{
	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECY;
}

int CTile::Update()
{
	__super::Update_Rect();
	return 0;
}

void CTile::Late_Update()
{
}

void CTile::Render(HDC hDC)
{
	HDC hMemDC = GET(CResourceMgr)->Find_Bmp(L"MapTile");

	int frameWidth = BMPTILECX;
	int frameHeight = BMPTILECX;

	int SrcX = frameWidth * m_tTileInfo.iDrawIDX;
	int SrcY = frameHeight * m_tTileInfo.iDrawIDY;


	GdiTransparentBlt(
		hDC,
		(int)(m_tRect.left	- GET(CCamera)->GetDiff().fX),				// 복사 받을 공간의 LEFT	
		(int)(m_tRect.top	- GET(CCamera)->GetDiff().fY),				// 복사 받을 공간의 TOP
		TILECX,												// 복사 받을 공간의 가로 
		TILECY,												// 복사 받을 공간의 세로 
		hMemDC,														// 복사 할 DC
		SrcX,														// 원본이미지 left
		SrcY,														// 원본이미지 top
		frameWidth,													// 원본이미지 가로
		frameHeight,												// 원본이미지 세로
		RGB(255, 0, 255)
	);
}

void CTile::Release()
{
}
