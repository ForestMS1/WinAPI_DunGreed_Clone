#include "pch.h"
#include "CCell.h"

CCell::CCell() : m_bMouseOn(false)
{
}

CCell::CCell(CUI* pParentUI)
{
	m_pParentUI = pParentUI;
}

CCell::~CCell()
{
	Release();
}

void CCell::Initialize()
{
	m_tInfo.fCX = 57.f;
	m_tInfo.fCY = 57.f;
	__super::Update_Rect();
}

int CCell::Update()
{
	return 0;
}

void CCell::Late_Update()
{
	__super::Update_Rect();
	if (PtInRect(&m_tRect, GET(CMouse)->Get_Point()))
	{
		m_bMouseOn = true;
	}
	else
	{
		m_bMouseOn = false;
	}
}

void CCell::Render(HDC hDC)
{
	m_wsFrameKey = L"";
	if (m_bMouseOn)
		m_wsFrameKey = L"Cell_On";
	else
		m_wsFrameKey = L"Cell";

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
		m_tInfo.fCX,
		m_tInfo.fCY,
		RGB(255, 0, 255)
	);
}

void CCell::Release()
{
}
