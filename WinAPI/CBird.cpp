#include "pch.h"
#include "CBird.h"

int CBird::m_iIdx = 0;

CBird::CBird()
{
	m_eRender = GAMEOBJECT;
}

CBird::~CBird()
{
}

void CBird::Initialize()
{
	m_fSpeed = 3.f;

	m_iFrameWidth = 48;
	m_iFrameHeight = 32;
	m_tInfo.fCX = m_iFrameWidth;
	m_tInfo.fCY = m_iFrameHeight;
	m_tFrame.iStart = m_iIdx;
	m_tFrame.iEnd = 7;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();
	__super::Update_Rect();
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Bird.bmp", L"Bird");
	m_iIdx++;
	if (m_iIdx > 7)
	{
		m_iIdx = m_tFrame.iStart;
	}
}

int CBird::Update()
{
	m_tInfo.fX += m_fSpeed;

	if (m_tInfo.fX > WINCX + 150)
	{
		m_tInfo.fX -= WINCX + 150;
	}
	Move_Frame();
	__super::Update_Rect();
	return 0;
}

void CBird::Late_Update()
{
}

void CBird::Render(HDC hDC)
{
	HDC hMemDC = GET(CResourceMgr)->Find_Bmp(L"Bird");
	GdiTransparentBlt(
		hDC,
		m_tRect.left,
		m_tRect.top,
		m_tInfo.fCX,
		m_tInfo.fCY,
		hMemDC,
		m_iFrameWidth * m_tFrame.iStart,
		m_iFrameHeight * m_tFrame.iMotion,
		m_iFrameWidth,
		m_iFrameHeight,
		RGB(255, 0, 255)
	);
}

void CBird::Release()
{
}
