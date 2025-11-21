#include "pch.h"
#include "CMyBit.h"

CMyBit::CMyBit()
{
}

CMyBit::~CMyBit()
{
	Release();
}

void CMyBit::Load_Bmp(wstring FilePath)
{
	HDC hdc = GetDC(g_hWnd);

	m_hMemDC = CreateCompatibleDC(hdc);
	ReleaseDC(g_hWnd, hdc);

	m_hBit = (HBITMAP)LoadImage(NULL,
		FilePath.c_str(),
		IMAGE_BITMAP,
		0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	m_hOldBit = (HBITMAP)SelectObject(m_hMemDC, m_hBit);

}

void CMyBit::Release()
{
	SelectObject(m_hMemDC, m_hOldBit);
	DeleteObject(m_hBit);
	DeleteDC(m_hMemDC);
}
