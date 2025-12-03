#include "pch.h"
#include "CBullet.h"

CBullet::CBullet() : m_fDamage(0.f), m_fAngle(0.f)
{
	m_eRender = BULLET;
}

CBullet::~CBullet()
{
	Release();
}

void CBullet::Initialize()
{
}

int CBullet::Update()
{
	__super::Update_Rect();
	Move_Frame();
	return 0;
}

void CBullet::Late_Update()
{
}

void CBullet::Render(HDC hDC)
{
	if (g_bDebugMod)
	{
		int ScrollX = GET(CCamera)->Get_ScrollX();
		int ScrollY = GET(CCamera)->Get_ScrollY();
		Rectangle(hDC, m_tRect.left - ScrollX, m_tRect.top - ScrollY, m_tRect.right - ScrollX, m_tRect.bottom - ScrollY);
	}
}

void CBullet::Release()
{
}
