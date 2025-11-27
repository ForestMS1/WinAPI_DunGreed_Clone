#include "pch.h"
#include "CTileBtn.h"
#include "CResourceMgr.h"
CTileBtn::CTileBtn()
{
}

CTileBtn::~CTileBtn()
{
	Release();
}

void CTileBtn::Initialize()
{
}

void CTileBtn::Update()
{
}

void CTileBtn::Late_Update()
{
}

void CTileBtn::Render(HDC hDC)
{
	//HDC hMemDC = GET(CResourceMgr)->Find_Bmp(L"MapTile");

	//int frameWidth = m_tInfo.fCX;		//512
	//int frameHeight = m_tInfo.fCY;		//512 사진사이즈

	//int SrcX = 0 + m_iScrollX;


	//GdiTransparentBlt(
	//	hDC,
	//	(int)(m_tRect.left),				// 복사 받을 공간의 LEFT	
	//	(int)(m_tRect.top),				// 복사 받을 공간의 TOP
	//	m_tInfo.fCX,													// 복사 받을 공간의 가로 
	//	m_tInfo.fCY,												// 복사 받을 공간의 세로 
	//	hMemDC,														// 복사 할 DC
	//	SrcX,											// 원본이미지 left
	//	0,														// 원본이미지 top
	//	frameWidth,								// 원본이미지 가로
	//	frameHeight,											// 원본이미지 세로
	//	RGB(255, 0, 255)
	//);
}

void CTileBtn::Release()
{
}
