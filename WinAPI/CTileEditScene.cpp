#include "pch.h"
#include "CTileEditScene.h"
#include "CResourceMgr.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CTileMgr.h"
#include "CCamera.h"
#include "CKeyMgr.h"

CTileEditScene::CTileEditScene()
{

}

CTileEditScene::~CTileEditScene()
{
	Release();
}

void CTileEditScene::Initialize()
{
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/MapTool/MapTile.bmp", L"MapTile");
	GET(CTileMgr)->Initialize();

	// Camera 지정
	GET(CCamera)->SetLookAt(Vec2(WINCX >> 1, WINCY >> 1));
}

void CTileEditScene::Update()
{
	Key_Input();

	GET(CTileMgr)->Update();
	GET(CCamera)->Update();
}

void CTileEditScene::Late_Update()
{
	GET(CTileMgr)->Late_Update();
}

void CTileEditScene::Render(HDC hDC)
{
	Rectangle(hDC, 0, 0, WINCX, WINCY);
	
	GET(CTileMgr)->Render(hDC);
}

void CTileEditScene::Release()
{
}

void CTileEditScene::Key_Input()
{
	if (GET(CKeyMgr)->Key_Pressing(VK_LBUTTON))
	{
		POINT	pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x += GET(CCamera)->Get_ScrollX();
		pt.y += GET(CCamera)->Get_ScrollY();

		// TODO : MapTile 이미지 에서 클릭한 타일인덱스를 아래 Picking_Tile에 넘겨주면 됨.....
		GET(CTileMgr)->Picking_Tile(pt, 1, 0, 0);
	}
	if (GET(CKeyMgr)->Key_Pressing('W'))
	{
		GET(CCamera)->Set_ScrollY(-5.f);
	}
	if (GET(CKeyMgr)->Key_Pressing('A'))
	{
		GET(CCamera)->Set_ScrollX(-5.f);
	}
	if (GET(CKeyMgr)->Key_Pressing('S'))
	{
		GET(CCamera)->Set_ScrollY(5.f);
	}
	if (GET(CKeyMgr)->Key_Pressing('D'))
	{
		GET(CCamera)->Set_ScrollX(5.f);
	}
}