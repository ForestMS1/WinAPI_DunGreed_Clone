#include "pch.h"
#include "CTileBtn.h"
#include "CResourceMgr.h"
#include "CCamera.h"
#include "CKeyMgr.h"
#include "CMouse.h"
CTileBtn::CTileBtn(float fX, float fY) : m_iCurTileX(0), m_iCurTileY(0)
, m_bMouseOn(false)
{
	m_tInfo.fX = fX;
	m_tInfo.fY = fY;
	m_tInfo.fCX = BMPTILECX;
	m_tInfo.fCY = BMPTILECY;
}

CTileBtn::~CTileBtn()
{
	Release();
}

void CTileBtn::Initialize()
{
}

int CTileBtn::Update()
{
	__super::Update_Rect();
	m_iCurTileX = (m_tRect.left - m_pParentUI->Get_Rect()->left) / m_tInfo.fCX;
	m_iCurTileY = (m_tRect.top - m_pParentUI->Get_Rect()->top) / m_tInfo.fCY;

	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	//Vec2 realPos = GET(CCamera)->GetRealPos(Vec2(pt.x, pt.y));

	if (PtInRect(&m_tRect, pt))
	{
		m_bMouseOn = true;
		if (GET(CKeyMgr)->Key_Down(VK_LBUTTON) && m_pParentUI->IsOpen())
		{
			//TODO : 이미지 값을 넘겨준다.
			m_iCurTileX = (m_tRect.left - (m_pParentUI->Get_Rect()->left)) / m_tInfo.fCX;
			m_iCurTileY = (m_tRect.top - (m_pParentUI->Get_Rect()->top)) / m_tInfo.fCY;
			GET(CMouse)->Set_DrawID(m_iCurTileX, m_iCurTileY);
		}
	}
	else
		m_bMouseOn = false;
	return 0;
}

void CTileBtn::Late_Update()
{

}

void CTileBtn::Render(HDC hDC)
{
	HDC hMemDC = GET(CResourceMgr)->Find_Bmp(L"MapTileOld");
	int SrcX = (m_tRect.left - (m_pParentUI->Get_Rect()->left));
	int SrcY = (m_tRect.top - (m_pParentUI->Get_Rect()->top));
	//GET(CCamera)

	GdiTransparentBlt(
		hDC,
		(int)(m_tRect.left),							// 복사 받을 공간의 LEFT	
		(int)(m_tRect.top),								// 복사 받을 공간의 TOP
		m_tInfo.fCX,											// 복사 받을 공간의 가로 
		m_tInfo.fCY,											// 복사 받을 공간의 세로 
		hMemDC,											// 복사 할 DC
		SrcX,											// 원본이미지 left
		SrcY,											// 원본이미지 top
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
}

void CTileBtn::Release()
{
}
