#include "pch.h"
#include "CLogo.h"
#include "CObjMgr.h"
#include "CPlayer.h"
#include "CResourceMgr.h"

CLogo::CLogo()
{
}

CLogo::~CLogo()
{
	Release();
}

void CLogo::Initialize()
{
	CObjMgr::Get_Instance()->AddObject(OBJ_PLAYER, new CPlayer);
	CResourceMgr::Get_Instance()->Insert_Bmp(L"../Resource/Logo/Logo.bmp", L"Logo");
	CResourceMgr::Get_Instance()->Insert_Png(L"../Resource/fireball_33x36_strip6.png", L"fireball");
	CObjMgr::Get_Instance()->Initialize();
}

void CLogo::Update()
{
	CObjMgr::Get_Instance()->Update();
}

void CLogo::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CLogo::Render(HDC hDC)
{
	HDC hMemDC = CResourceMgr::Get_Instance()->Find_Bmp(L"Logo");
	Image* pImg = CResourceMgr::Get_Instance()->Find_Png(L"fireball");

	int frameWidth = 33;
	int frameHeight = 36;
	int frameIdx = 0;

	int SrcX = frameWidth * frameIdx;
	int SrcY = 0;

	Rect rc( 200, 200, frameWidth, frameHeight );

	GdiTransparentBlt(hDC,			// 복사 받을 DC
		0,				// 복사 받을 공간의 LEFT	
		0,				// 복사 받을 공간의 TOP
		WINCX,			// 복사 받을 공간의 가로 
		WINCY,			// 복사 받을 공간의 세로 
		hMemDC,				// 복사 할 DC
		0,					// 복사할 이미지의 LEFT, TOP
		0,
		WINCX,		// 복사할 이미지의 가로, 세로
		WINCY,
		RGB(0, 0, 0));	// 제거할 색상
	Graphics grp(hDC);
	grp.DrawImage(pImg, rc, SrcX, SrcY, frameWidth, frameHeight, UnitPixel);


	//BitBlt(hDC,				// 복사 받을 DC
	//	0,						// 복사 받을 공간의 LEFT	
	//	0,						// 복사 받을 공간의 TOP
	//	WINCX,					// 복사 받을 공간의 가로 
	//	WINCY,					// 복사 받을 공간의 세로 
	//	g.GetHDC(),				// 복사 할 DC
	//	0,						// 복사할 이미지의 LEFT, TOP
	//	0,
	//	SRCCOPY);				// 그대로 복사
	CObjMgr::Get_Instance()->Render(hDC);
}

void CLogo::Release()
{
	CObjMgr::Get_Instance()->DeleteLayerObj(OBJ_PLAYER);
}
