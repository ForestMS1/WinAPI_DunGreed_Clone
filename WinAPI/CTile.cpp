#include "pch.h"
#include "CTile.h"
#include "CResourceMgr.h"
#include "CCamera.h"
#include "CLineMgr.h"

CTile::CTile() : m_iOption(ERASE)
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
	__super::Update_Rect();
	POINT ptLeft, ptRight;
	ptLeft.x = m_tRect.left;
	ptRight.x = m_tRect.right;
	switch (m_iOption)
	{
	case BLOCKED_UPHILL:
		ptLeft.y = m_tRect.bottom;
		ptRight.y = m_tRect.top;
		m_pLine = new CLine(ptLeft, ptRight);
		GET(CLineMgr)->Add_Line(dynamic_cast<CLine*>(m_pLine));
		break;
	case BLOCKED_DOWNHILL:
		ptLeft.y = m_tRect.top;
		ptRight.y = m_tRect.bottom;
		m_pLine = new CLine(ptLeft, ptRight);
		GET(CLineMgr)->Add_Line(dynamic_cast<CLine*>(m_pLine));
		break;
	case SPACIOUS:
		ptLeft.y = m_tRect.top;
		ptRight.y = m_tRect.top;
		m_pLine = new CLine(ptLeft, ptRight);
		GET(CLineMgr)->Add_Line(dynamic_cast<CLine*>(m_pLine));
		break;
	case SPACIOUS_UPHILL:
		ptLeft.y = m_tRect.bottom;
		ptRight.y = m_tRect.top;
		m_pLine = new CLine(ptLeft, ptRight);
		GET(CLineMgr)->Add_Line(dynamic_cast<CLine*>(m_pLine));
		break;
	case SPACIOUS_DOWNHILL:
		ptLeft.y = m_tRect.top;
		ptRight.y = m_tRect.bottom;
		m_pLine = new CLine(ptLeft, ptRight);
		GET(CLineMgr)->Add_Line(dynamic_cast<CLine*>(m_pLine));
		break;
	default:
		break;
	}
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
	//if (m_iOption == ERASE) return;
	HDC hMemDC = GET(CResourceMgr)->Find_Bmp(L"MapTileOld");

	int frameWidth = BMPTILECX;
	int frameHeight = BMPTILECX;

	int SrcX = frameWidth * m_tTileInfo.iDrawIDX;
	int SrcY = frameHeight * m_tTileInfo.iDrawIDY;

	if (m_iOption != ERASE)
	{
		GdiTransparentBlt(
			hDC,
			(int)(m_tRect.left - GET(CCamera)->GetDiff().fX),				// 복사 받을 공간의 LEFT	
			(int)(m_tRect.top - GET(CCamera)->GetDiff().fY),				// 복사 받을 공간의 TOP
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


	if (g_bDebugMod)
	{
		hMemDC = GET(CResourceMgr)->Find_Bmp(L"MapTileOption");

		GdiTransparentBlt(
			hDC,
			(int)(m_tRect.left - GET(CCamera)->GetDiff().fX),				// 복사 받을 공간의 LEFT	
			(int)(m_tRect.top - GET(CCamera)->GetDiff().fY),				// 복사 받을 공간의 TOP
			TILECX,												// 복사 받을 공간의 가로 
			TILECY,												// 복사 받을 공간의 세로 
			hMemDC,														// 복사 할 DC
			m_iOption * BMPTILECX,														// 원본이미지 left
			0,														// 원본이미지 top
			16,													// 원본이미지 가로
			16,												// 원본이미지 세로
			RGB(255, 0, 255)
		);
		if (m_iOption == ERASE)
			Rectangle(hDC, m_tRect.left - GET(CCamera)->GetDiff().fX, m_tRect.top - GET(CCamera)->GetDiff().fY, m_tRect.right - GET(CCamera)->GetDiff().fX, m_tRect.bottom - GET(CCamera)->GetDiff().fY);
	}
}

void CTile::Release()
{

}
