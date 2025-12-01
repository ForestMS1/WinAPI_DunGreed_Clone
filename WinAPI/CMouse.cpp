#include "pch.h"
#include "CMouse.h"
#include "CResourceMgr.h"
#include "CKeyMgr.h"
#include "CCamera.h"
CMouse* CMouse::m_pInstance = nullptr;

CMouse::CMouse() : m_iOption(0)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
}
CMouse::~CMouse()
{

}

void CMouse::Initialize()
{
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/Cursor/ShootingCursor.bmp", L"ShootingCursor");
	ShowCursor(false);
}
void CMouse::Update()
{
	GetCursorPos(&m_ptInfo);
	ScreenToClient(g_hWnd, &m_ptInfo);

	m_tInfo.fX = (float)m_ptInfo.x;
	m_tInfo.fY = (float)m_ptInfo.y;

	m_tRect.left = m_tInfo.fX - m_tInfo.fCX * 0.5f;
	m_tRect.top = m_tInfo.fY - m_tInfo.fCY * 0.5f;
	m_tRect.right = m_tInfo.fX + m_tInfo.fCX * 0.5f;
	m_tRect.bottom = m_tInfo.fY + m_tInfo.fCY * 0.5f;
}
void CMouse::Late_Update()
{
#ifdef _DEBUG
	if (GET(CKeyMgr)->Key_Pressing(VK_RETURN))
	{
		Vec2 rp = GET(CCamera)->GetRealPos(Vec2(m_tInfo.fX, m_tInfo.fY));
		Vec2 renderPos = GET(CCamera)->GetRenderPos(Vec2(m_tInfo.fX, m_tInfo.fY));
		cout << "마우스 실제 위치 : " << rp.fX << "\t" << rp.fY << endl;
		cout << "마우스 렌더 위치 : " << renderPos.fX << "\t" << renderPos.fY << endl;
	}
#endif // _DEBUG
}
void CMouse::Render(HDC hDC)
{
	HDC hMemDC = GET(CResourceMgr)->Find_Bmp(L"ShootingCursor");

	GdiTransparentBlt(
		hDC,
		m_tRect.left,
		m_tRect.top,
		m_tInfo.fCX,
		m_tInfo.fCY,
		hMemDC,
		0,
		0,
		63,
		63,
		RGB(255, 0, 255)
	);
}
void CMouse::Release()
{

}