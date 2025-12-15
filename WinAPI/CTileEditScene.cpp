#include "pch.h"
#include "CTileEditScene.h"
#include "CResourceMgr.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CTileMgr.h"
#include "CCamera.h"
#include "CKeyMgr.h"
#include "CMapTileUI.h"
#include "CTileBtn.h"
#include "CMouse.h"
#include "CMapTileOptionUI.h"
#include "CPlayer.h"
CTileEditScene::CTileEditScene() : m_iDrawIDX(0), m_iDrawIDY(0), m_iOption(1)
, m_pTileSelectUI(nullptr), m_pTileOptionSelectUI(nullptr)
{

}

CTileEditScene::~CTileEditScene()
{
	Release();
}

void CTileEditScene::Initialize()
{

	GET(CResourceMgr)->Insert_Png(L"../Resources/Images/Town/Villiaged2.png", L"Villiaged2");


	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Town/TownTinyVersion.bmp", L"Town");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Town/Cloud.bmp", L"Cloud");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Town/TownBG_Day.bmp", L"TownBG_Day");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Town/Tree0.bmp", L"Tree0");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Town/Tree1.bmp", L"Tree1");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Town/StreetLight_0.bmp", L"StreetLight_0");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Town/StreetLight_1.bmp", L"StreetLight_1");
	GET(CTileMgr)->Initialize();

	GET(CUIMgr)->Insert_UI(L"MapTileUI", new CMapTileUI);
	GET(CUIMgr)->Insert_UI(L"MapTileOptionUI", new CMapTileOptionUI);

	GET(CUIMgr)->Initialize();
	// Camera 지정
	GET(CCamera)->SetLookAt(Vec2(WINCX >> 1, WINCY >> 1));
}

void CTileEditScene::Update()
{
	GetCursorPos(&m_ptMouse);
	ScreenToClient(g_hWnd, &m_ptMouse);

	Key_Input();

	//GET(CLineMgr)->Update();
}

void CTileEditScene::Late_Update()
{

	m_iDrawIDX = GET(CMouse)->Get_DrawIDX();
	m_iDrawIDY = GET(CMouse)->Get_DrawIDY();
	m_iOption = GET(CMouse)->Get_Option();
}

void CTileEditScene::Render(HDC hDC)
{
	Rectangle(hDC, 0, 0, WINCX, WINCY);
	int scrollX = GET(CCamera)->Get_ScrollX();
	int scrollY = GET(CCamera)->Get_ScrollY();
	HDC hTownDC = GET(CResourceMgr)->Find_Bmp(L"Cloud");
	GdiTransparentBlt(
		hDC,
		0,
		0,
		WINCX,
		WINCY,
		hTownDC,
		0,
		0,
		960,
		540,
		RGB(255,0,255));

	HDC hTownBGDC = GET(CResourceMgr)->Find_Bmp(L"TownBG_Day");
	GdiTransparentBlt(
		hDC,
		0,
		0,
		WINCX,
		WINCY,
		hTownBGDC,
		0,
		0,
		320,
		142,
		RGB(255, 0, 255));

	HDC hMemDC = GET(CResourceMgr)->Find_Bmp(L"MapTileOld");

	int frameWidth = BMPTILECX;
	int frameHeight = BMPTILECX;

	int SrcX = frameWidth * m_iDrawIDX;
	int SrcY = frameHeight * m_iDrawIDY;

	//Image* img = GET(CResourceMgr)->Find_Png(L"Villiaged2");
	//Graphics graphics(hDC);
	//graphics.SetInterpolationMode(Gdiplus::InterpolationModeNearestNeighbor);
	//const int DEST_WIDTH = 2048 * 3;
	//const int DEST_HEIGHT = 320 * 3;

	//Gdiplus::Rect rt(
	//	0 - scrollX,             // X 좌표 시작점
	//	8 - scrollY,             // Y 좌표 시작점
	//	DEST_WIDTH,    // 출력할 너비 (2048)
	//	DEST_HEIGHT    // 출력할 높이 (320)
	//);

	//graphics.DrawImage(img, rt);


	wstring text = L"Tile_Option : " + to_wstring(m_iOption);
	TextOut(hDC, 10, 0, text.c_str(), text.length());
	text = L"Camera_Move : WASD";
	TextOut(hDC, 10, 20, text.c_str(), text.length());
	text = L"Save : Q, Load : R";
	TextOut(hDC, 10, 40, text.c_str(), text.length());
	text = L"Tile_Clear: C";
	TextOut(hDC, 10, 60, text.c_str(), text.length());
	//GET(CLineMgr)->Render(hDC);
}

void CTileEditScene::Release()
{
	GET(CObjMgr)->DeleteAllLayer();
	GET(CTileMgr)->Clear_Tile();
	GET(CUIMgr)->Release();
	GET(CSoundMgr)->StopAll();
}

void CTileEditScene::Key_Input()
{
#pragma region 마우스_왼오_클릭_칠하기
	if (GET(CKeyMgr)->Key_Pressing(VK_LBUTTON) && !GET(CUIMgr)->Find_UI(L"MapTileUI")->IsOpen()
		&& !dynamic_cast<CMapTileOptionUI*>(GET(CUIMgr)->Find_UI(L"MapTileOptionUI"))->IsMouseOn())
	{
		POINT	pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x = (int)GET(CCamera)->GetRealPos(pt).fX;
		pt.y = (int)GET(CCamera)->GetRealPos(pt).fY;

		
		GET(CTileMgr)->Picking_Tile(pt, m_iDrawIDX, m_iDrawIDY, m_iOption);
	}
	// 오른쪽 클릭은 옵션만 지정
	if (GET(CKeyMgr)->Key_Pressing(VK_RBUTTON))
	{
		POINT	pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x = (int)GET(CCamera)->GetRealPos(pt).fX;
		pt.y = (int)GET(CCamera)->GetRealPos(pt).fY;


		GET(CTileMgr)->Picking_Tile(pt, m_iOption);
	}
#pragma endregion

#pragma region 키입력_카메라이동
	if (GET(CKeyMgr)->Key_Pressing(VK_UP))
	{
		GET(CCamera)->Set_ScrollY(-5.f);
	}
	if (GET(CKeyMgr)->Key_Pressing(VK_LEFT))
	{
		GET(CCamera)->Set_ScrollX(-5.f);
	}
	if (GET(CKeyMgr)->Key_Pressing(VK_DOWN))
	{
		GET(CCamera)->Set_ScrollY(5.f);
	}
	if (GET(CKeyMgr)->Key_Pressing(VK_RIGHT))
	{
		GET(CCamera)->Set_ScrollX(5.f);
	}
#pragma endregion
#pragma region Q_W저장불러오기
	if (GET(CKeyMgr)->Key_Pressing('Q'))
	{
		GET(CTileMgr)->Save_Tile();
	}
	if (GET(CKeyMgr)->Key_Pressing('R'))
	{
		//GET(CTileMgr)->Load_Tile(L"TestScene");
		//GET(CTileMgr)->Load_Tile(L"BelialScene");
		//GET(CTileMgr)->Load_Tile(L"IceDungeon01");
		GET(CTileMgr)->Load_Tile(L"IceDungeon01");
	}
	if (GET(CKeyMgr)->Key_Pressing('F'))
	{
		GET(CSceneMgr)->ChangeScene(L"Logo");
	}
#pragma endregion

	if (GET(CKeyMgr)->Key_Down(VK_SPACE))
	{
		if (GET(CUIMgr)->Find_UI(L"MapTileUI"))
		{
			if (GET(CUIMgr)->Find_UI(L"MapTileUI")->IsOpen())
				GET(CUIMgr)->Find_UI(L"MapTileUI")->Close();
			else
				GET(CUIMgr)->Find_UI(L"MapTileUI")->Open();
		}
	}	

	if (GET(CKeyMgr)->Key_Down('Z'))
	{
		Vec2 pv = GET(CCamera)->GetRealPos(GET(CMouse)->Get_Point());
		GET(CObjMgr)->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(pv.fX, pv.fY));
	}

	if (GET(CKeyMgr)->Key_Down(VK_TAB))
	{
		g_bDebugMod = !g_bDebugMod;
	}

	if (GET(CKeyMgr)->Key_Down('C'))
	{
		GET(CTileMgr)->Clear_Tile();
	}

}