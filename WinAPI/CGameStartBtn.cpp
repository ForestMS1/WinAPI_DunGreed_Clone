#include "pch.h"
#include "CGameStartBtn.h"

CGameStartBtn::CGameStartBtn() : m_bMouseOn(false)
{
}

CGameStartBtn::~CGameStartBtn()
{
}

void CGameStartBtn::Initialize()
{
	m_tFrame.iStart = 0;
	m_tFrame.iMotion = 1;
	m_tFrame.iEnd = 0;
	m_tFrame.dwSpeed = 0;
	m_tFrame.dwTime = GetTickCount();

	m_tInfo.fX = WINCX >> 1;
	m_tInfo.fY = (WINCY >> 1) + 100;
	m_tInfo.fCX = 158;
	m_tInfo.fCY = 47.f;
	__super::Update_Rect();

	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/Buttons/GameStart.bmp", L"GameStart");
}

int CGameStartBtn::Update()
{

	return 0;
}

void CGameStartBtn::Late_Update()
{
	Vec2 vc = GET(CCamera)->GetRenderPos(GET(CMouse)->Get_Point());
	POINT pt = { (int)vc.fX , (int)vc.fY };
	if (PtInRect(&m_tRect, pt))
	{
		m_bMouseOn = true;
		if (GET(CKeyMgr)->Key_Down(VK_LBUTTON))
		{
			GET(CSceneMgr)->ChangeScene(L"Belial");
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

void CGameStartBtn::Render(HDC hDC)
{
	HDC hMemDC = GET(CResourceMgr)->Find_Bmp(L"GameStart");
	GdiTransparentBlt(
		hDC,
		m_tRect.left,
		m_tRect.top,
		m_tInfo.fCX,
		m_tInfo.fCY,
		hMemDC,
		0,
		47 * m_tFrame.iMotion,
		158,
		47,
		RGB(255, 0, 255)
	);
}

void CGameStartBtn::Release()
{
}
