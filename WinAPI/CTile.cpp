#include "pch.h"
#include "CTile.h"
#include "CCamera.h"
#include "CResourceMgr.h"
CTile::CTile()
{

}

CTile::~CTile()
{
}

void CTile::Initialize()
{
	m_tInfo.fCX = TILESIZE;
	m_tInfo.fCY = TILESIZE;
}

int CTile::Update()
{
	return 0;
}

void CTile::Late_Update()
{
}

void CTile::Render(HDC hDC)
{
	HDC hMemDC = GET(CResourceMgr)->Find_Bmp(L"MapTile");

	Vec2 vRenderPos = GET(CCamera)->GetRenderPos(Get_Pos());

	int frameWidth = TILESIZE;
	int frameHeight = TILESIZE;

	int SrcX = frameWidth * m_tFrame.iStart;
	int SrcY = frameHeight * m_tFrame.iRow;


	GdiTransparentBlt(
		hDC,
		(int)(vRenderPos.fX),										// 복사 받을 공간의 LEFT	
		(int)(vRenderPos.fY),										// 복사 받을 공간의 TOP
		TILESIZE,												// 복사 받을 공간의 가로 
		TILESIZE,												// 복사 받을 공간의 세로 
		hMemDC,														// 복사 할 DC
		SrcX,															// 원본이미지 left
		SrcY,															// 원본이미지 top
		frameWidth,														// 원본이미지 가로
		frameHeight,														// 원본이미지 세로
		RGB(255, 0, 255)
	);

	//Rectangle(hDC, 
	//	(int)(vRenderPos.fX),
	//	(int)(vRenderPos.fY),
	//	(int)(vRenderPos.fX + m_tInfo.fCX), 
	//	(int)(vRenderPos.fY + m_tInfo.fCY));
}

void CTile::Release()
{
}
