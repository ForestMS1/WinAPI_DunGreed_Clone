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
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/Logo.bmp", L"Logo");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/Bird.bmp", L"Bird");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/BackGround/Sky.bmp", L"Sky");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/BackGround/Cloud2.bmp", L"Cloud2");

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
	HDC hSkyDC = CResourceMgr::Get_Instance()->Find_Bmp(L"Sky");
	GdiTransparentBlt(
		hDC,
		0,
		0,
		WINCX,
		WINCY,
		hSkyDC,
		0,
		0,
		WINCX,
		WINCY,
		RGB(0, 0, 0)
	);
}

void CLogo::Release()
{
	CObjMgr::Get_Instance()->DeleteLayerObj(OBJ_PLAYER);
}
