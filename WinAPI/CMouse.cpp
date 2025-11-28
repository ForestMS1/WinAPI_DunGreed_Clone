#include "pch.h"
#include "CMouse.h"

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
}
void CMouse::Update()
{
	GetCursorPos(&m_ptInfo);
	ScreenToClient(g_hWnd, &m_ptInfo);

	//Update_Rect();
}
void CMouse::Late_Update()
{

}
void CMouse::Render(HDC hDC)
{

}
void CMouse::Release()
{

}