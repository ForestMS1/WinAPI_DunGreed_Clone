#include "pch.h"
#include "CBrokenCell.h"

CBrokenCell::CBrokenCell()
{
	m_eRender = EFFECT;
}

CBrokenCell::~CBrokenCell()
{
}

void CBrokenCell::Initialize()
{
	m_iFrameWidth = 73;
	m_iFrameHeight = 42;
	m_tInfo.fCX = m_iFrameWidth * 3;
	m_tInfo.fCY = m_iFrameHeight * 3;
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Dungeon/BrokenCell0.bmp", L"BrokenCell0");
}

int CBrokenCell::Update()
{
	__super::Update_Rect();
	return 0;
}

void CBrokenCell::Late_Update()
{
}

void CBrokenCell::Render(HDC hDC)
{
	int scrollX = GET(CCamera)->Get_ScrollX();
	int scrollY = GET(CCamera)->Get_ScrollY();
	HDC hBackDC = GET(CResourceMgr)->Find_Bmp(L"BrokenCell0");
	GdiTransparentBlt(
		hDC,
		m_tRect.left  - scrollX,
		m_tRect.right - scrollY,
		m_tInfo.fCX,
		m_tInfo.fCY,
		hBackDC,
		0,
		0,
		m_iFrameWidth,
		m_iFrameHeight,
		RGB(255, 0, 255)
	);
}

void CBrokenCell::Release()
{
}
