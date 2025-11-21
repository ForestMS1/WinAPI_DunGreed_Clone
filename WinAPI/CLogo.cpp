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
	CResourceMgr::Get_Instance()->Insert_Image(L"../Resource/Logo/Logo.bmp", L"Logo");
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
	HDC hMemDC = CResourceMgr::Get_Instance()->Find_Image(L"Logo");

	//GdiTransparentBlt(hDC,			// 복사 받을 DC
	//	0,				// 복사 받을 공간의 LEFT	
	//	0,				// 복사 받을 공간의 TOP
	//	WINCX,			// 복사 받을 공간의 가로 
	//	WINCY,			// 복사 받을 공간의 세로 
	//	hMemDC,				// 복사 할 DC
	//	0,					// 복사할 이미지의 LEFT, TOP
	//	0,
	//	WINCX,		// 복사할 이미지의 가로, 세로
	//	WINCY,
	//	RGB(255, 255, 255));	// 제거할 색상
	BitBlt(hDC,				// 복사 받을 DC
		0,						// 복사 받을 공간의 LEFT	
		0,						// 복사 받을 공간의 TOP
		WINCX,					// 복사 받을 공간의 가로 
		WINCY,					// 복사 받을 공간의 세로 
		hMemDC,				// 복사 할 DC
		0,						// 복사할 이미지의 LEFT, TOP
		0,
		SRCCOPY);				// 그대로 복사
	CObjMgr::Get_Instance()->Render(hDC);
}

void CLogo::Release()
{
	CObjMgr::Get_Instance()->DeleteLayerObj(OBJ_PLAYER);
}
