#include "pch.h"
#include "CTileOptionBtn.h"
#include "CResourceMgr.h"
#include "CCamera.h"
#include "CKeyMgr.h"
#include "CMouse.h"
CTileOptionBtn::CTileOptionBtn(float fX, float fY) : m_iOption(0), m_bMouseOn(false)
{
	m_tInfo.fX = fX;
	m_tInfo.fY = fY;
	m_tInfo.fCX = TILECX;
	m_tInfo.fCY = TILECX;
}

CTileOptionBtn::~CTileOptionBtn()
{
	Release();
}

void CTileOptionBtn::Initialize()
{
	__super::Update_Rect();

	m_iOption = (m_tRect.left - (m_pParentUI->Get_Rect()->left)) / TILECX;
}

int CTileOptionBtn::Update()
{
	__super::Update_Rect();
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);


	if (PtInRect(&m_tRect, pt))
	{
		m_bMouseOn = true;
		if (GET(CKeyMgr)->Key_Down(VK_LBUTTON))
		{
			//TODO : 옵션 값을 넘겨준다.
			GET(CMouse)->Set_Option(m_iOption);
		}
	}
	else
		m_bMouseOn = false;
	return 0;
}

void CTileOptionBtn::Late_Update()
{
	

}

void CTileOptionBtn::Render(HDC hDC)
{
	HDC hMemDC = GET(CResourceMgr)->Find_Bmp(L"MapTileOption");
	//GET(CCamera)

	GdiTransparentBlt(
		hDC,
		(int)(m_tRect.left),							// 복사 받을 공간의 LEFT	
		(int)(m_tRect.top),								// 복사 받을 공간의 TOP
		m_tInfo.fCX,											// 복사 받을 공간의 가로 
		m_tInfo.fCY,											// 복사 받을 공간의 세로 
		hMemDC,											// 복사 할 DC
		m_iOption * BMPTILECX,											// 원본이미지 left
		0,											// 원본이미지 top
		BMPTILECX,											// 원본이미지 가로
		BMPTILECX,											// 원본이미지 세로
		RGB(255, 0, 255)
	);

	if (m_bMouseOn)
	{
		HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
		hPen = (HPEN)SelectObject(hDC, hPen);
		MoveToEx(hDC, m_tRect.left, m_tRect.top, nullptr);
		LineTo(hDC, m_tRect.right, m_tRect.top);
		LineTo(hDC, m_tRect.right, m_tRect.bottom);
		LineTo(hDC, m_tRect.left, m_tRect.bottom);
		LineTo(hDC, m_tRect.left, m_tRect.top);
		hPen = (HPEN)SelectObject(hDC, hPen);
		DeleteObject(hPen);
	}
	//Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CTileOptionBtn::Release()
{
}
