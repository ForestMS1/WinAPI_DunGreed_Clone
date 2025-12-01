#include "pch.h"
#include "CGoTileEditBtn.h"

CGoTileEditBtn::CGoTileEditBtn() : m_bMouseOn(false)
{
}

CGoTileEditBtn::~CGoTileEditBtn()
{
}

void CGoTileEditBtn::Initialize()
{
	m_tFrame.iStart = 0;
	m_tFrame.iMotion = 1;
	m_tFrame.iEnd = 0;
	m_tFrame.dwSpeed = 0;
	m_tFrame.dwTime = GetTickCount();

	m_tInfo.fX = WINCX >> 1;
	m_tInfo.fY = (WINCY >> 1) + 200;
	m_tInfo.fCX = 73.f;
	m_tInfo.fCY = 47.f;
	__super::Update_Rect();

	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/Buttons/MapTool.bmp", L"MapTool");
}

int CGoTileEditBtn::Update()
{

	return 0;
}

void CGoTileEditBtn::Late_Update()
{
	Vec2 vc = GET(CCamera)->GetRenderPos(GET(CMouse)->Get_Point());
	POINT pt = { (int)vc.fX , (int)vc.fY };
	if (PtInRect(&m_tRect, pt))
	{
		m_bMouseOn = true;
		if (GET(CKeyMgr)->Key_Down(VK_LBUTTON))
		{
			GET(CSceneMgr)->ChangeScene(L"TileEdit");
		}
	}
	else
	{
		m_bMouseOn = false;
	}

	if (m_bMouseOn)
		m_tFrame.iMotion = 0;
	else
		m_tFrame.iMotion = 1;
}

void CGoTileEditBtn::Render(HDC hDC)
{
	HDC hMemDC = GET(CResourceMgr)->Find_Bmp(L"MapTool");
	GdiTransparentBlt(
		hDC,
		m_tRect.left,
		m_tRect.top,
		m_tInfo.fCX,
		m_tInfo.fCY,
		hMemDC,
		0,
		47 * m_tFrame.iMotion,
		73,
		47,
		RGB(255,0,255)
		);
}

void CGoTileEditBtn::Release()
{
}
