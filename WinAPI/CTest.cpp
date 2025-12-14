#include "pch.h"
#include "CTest.h"
#include "CLineMgr.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CPlayer.h"
#include "CCamera.h"
#include "CResourceMgr.h"
#include "CKeyMgr.h"
#include "CTileMgr.h"
#include "CBelial.h"
#include "CPlayerUI.h"
#include "CInventoryUI.h"
#include "CPlayerMgr.h"
#include "CGiantBat.h"
#include "CBanshee.h"
#include "CNPC_Giant.h"
#include "CNPC_Commander.h"
#include "CDungeonEat.h"
#include "CSnow.h"
CTest::CTest() : m_bIsDrawing(false)
{
	ZeroMemory(&m_ptMouse, sizeof(m_ptMouse));
	ZeroMemory(&m_ptLeft, sizeof(m_ptLeft));
	ZeroMemory(&m_ptRight, sizeof(m_ptRight));
}

CTest::~CTest()
{
	Release();
}

void CTest::Initialize()
{
	GET(CResourceMgr)->Insert_Png(L"../Resources/Images/Town/Villiaged2.png", L"Villiaged2");


	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Town/Cloud.bmp", L"Cloud");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Town/TownBG_Day.bmp", L"TownBG_Day");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Town/TownLayer_Day.bmp", L"TownLayer_Day");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Town/Shop.bmp", L"Shop");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Town/TrainingSchool.bmp", L"TrainingSchool");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Town/DungeonSignL.bmp", L"DungeonSignL");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Town/DungeonSignR.bmp", L"DungeonSignR");
	GET(CObjMgr)->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(200.f, 550.f));
	//GET(CObjMgr)->AddObject(OBJ_MONSTER, CAbstractFactory<CBelial>::Create(2000.f, 200.f));
	//GET(CObjMgr)->AddObject(OBJ_MONSTER, CAbstractFactory<CGiantBat>::Create(500.f, 200.f));
	//GET(CObjMgr)->AddObject(OBJ_MONSTER, CAbstractFactory<CBanshee>::Create(700.f, 200.f));
	GET(CObjMgr)->AddObject(OBJ_NPC, CAbstractFactory<CNPC_Giant>::Create(4934.f, 414.f));
	GET(CObjMgr)->AddObject(OBJ_NPC, CAbstractFactory<CNPC_Commander>::Create(545, 885));
	GET(CObjMgr)->AddObject(OBJ_NPC, CAbstractFactory<CDungeonEat>::Create(2900.f, 793.f));
	GET(CObjMgr)->AddObject(OBJ_NPC, CAbstractFactory<CDungeonEat>::Create(2900.f + 351, 793.f));
	GET(CObjMgr)->AddObject(OBJ_NPC, CAbstractFactory<CDungeonEat>::Create(2900.f + 351 * 2, 793.f));
	
	// 눈내리기~~
	CSnow* pSnow = new CSnow;
	GET(CObjMgr)->AddObject(OBJ_EFFECT, pSnow);

	GET(CObjMgr)->Initialize();
	pSnow->SetSpeed(7.f);

	GET(CPlayerMgr)->Initialize();
	GET(CTileMgr)->Initialize();
	GET(CTileMgr)->Load_Tile(L"TownScene");
	GET(CLineMgr)->Load_Line();
	GET(CLineMgr)->Initialize();


	GET(CUIMgr)->Insert_UI(L"PlayerUI", new CPlayerUI(GET(CPlayerMgr)->GetPlayer()));
	GET(CUIMgr)->Insert_UI(L"InventoryUI", new CInventoryUI(GET(CPlayerMgr)->GetPlayer()));

	GET(CUIMgr)->Initialize();

	// Camera 지정
	GET(CCamera)->Initialize();
	//GET(CCamera)->SetLookAt(Vec2(WINCX >> 1, WINCY >> 1));
	GET(CCamera)->SetTarget(GET(CObjMgr)->GetObjLayer(OBJ_PLAYER).front());

	GET(CSoundMgr)->PlayBGM(L"BGM_Town.wav", 0.3f);
}

void CTest::Update()
{
	GET(CPlayerMgr)->Update();
	Key_Input();
}

void CTest::Late_Update()
{
	if(GET(CKeyMgr)->Key_Down('N'))
		GET(CSceneMgr)->ChangeScene(L"DungeonStart");

	for (auto pEat : GET(CObjMgr)->GetObjLayer(OBJ_NPC))
	{
		if (dynamic_cast<CDungeonEat*>(pEat) != nullptr)
		{
			if (dynamic_cast<CDungeonEat*>(pEat)->CompleteEat())
			{
				GET(CSceneMgr)->ChangeScene(L"DungeonStart");
				break;
			}
		}
	}
}

void CTest::Render(HDC hDC)
{
	int scrollX = GET(CCamera)->Get_ScrollX();
	int scrollY = GET(CCamera)->Get_ScrollY();
	Rectangle(hDC, 0, 0, WINCX, WINCY);
	HDC hMemDC = CResourceMgr::Get_Instance()->Find_Bmp(L"Cloud");
	//TODO : 배경 무한 움직임
	StretchBlt(
		hDC,
		0,
		0,
		WINCX,
		WINCY,
		hMemDC,
		0,
		0,
		960,
		540,
		SRCCOPY
	);
	hMemDC = CResourceMgr::Get_Instance()->Find_Bmp(L"TownBG_Day");
	GdiTransparentBlt(
		hDC,
		0,												// 복사 받을 공간의 LEFT	
		0,												// 복사 받을 공간의 TOP
		WINCX,											// 복사 받을 공간의 가로 
		WINCY,											// 복사 받을 공간의 세로 
		hMemDC,											// 복사 할 DC
		0,
		0,
		320,
		142,
		RGB(255, 0, 255)
	);
	//hMemDC = CResourceMgr::Get_Instance()->Find_Bmp(L"Shop");
	//GdiTransparentBlt(
	//	hDC,
	//	-20 - scrollX,												// 복사 받을 공간의 LEFT	
	//	-35 - scrollY,												// 복사 받을 공간의 TOP
	//	564,											// 복사 받을 공간의 가로 
	//	356,											// 복사 받을 공간의 세로 
	//	hMemDC,											// 복사 할 DC
	//	0,
	//	0,
	//	564,
	//	356,
	//	RGB(255, 0, 255)
	//);
	//hMemDC = CResourceMgr::Get_Instance()->Find_Bmp(L"TrainingSchool");
	//GdiTransparentBlt(
	//	hDC,
	//	1600 - scrollX,												// 복사 받을 공간의 LEFT	
	//	220 - scrollY,												// 복사 받을 공간의 TOP
	//	270 * 3,											// 복사 받을 공간의 가로 
	//	77 * 3,											// 복사 받을 공간의 세로 
	//	hMemDC,											// 복사 할 DC
	//	0,
	//	0,
	//	270,
	//	77,
	//	RGB(255, 0, 255)
	//);

	//hMemDC = CResourceMgr::Get_Instance()->Find_Bmp(L"DungeonSignL");
	//GdiTransparentBlt(
	//	hDC,
	//	2300 - scrollX,												// 복사 받을 공간의 LEFT	
	//	580 - scrollY,												// 복사 받을 공간의 TOP
	//	20 * 3,											// 복사 받을 공간의 가로 
	//	22 * 3,											// 복사 받을 공간의 세로 
	//	hMemDC,											// 복사 할 DC
	//	0,
	//	0,
	//	20,
	//	22,
	//	RGB(255, 0, 255)
	//);

	Image* img = GET(CResourceMgr)->Find_Png(L"Villiaged2");
	Graphics graphics(hDC);
	graphics.SetInterpolationMode(Gdiplus::InterpolationModeNearestNeighbor);
	const int DEST_WIDTH = 2048 * 3;
	const int DEST_HEIGHT = 320 * 3;

	Gdiplus::Rect rt(
		0 - scrollX,             // X 좌표 시작점
		8 - scrollY,             // Y 좌표 시작점
		DEST_WIDTH,    // 출력할 너비 (2048)
		DEST_HEIGHT    // 출력할 높이 (320)
	);
	graphics.DrawImage(img, rt);
}

void CTest::Release()
{
	GET(CObjMgr)->DeleteAllLayer();
	GET(CTileMgr)->Clear_Tile();
	GET(CUIMgr)->Release();
	GET(CSoundMgr)->StopAll();
}

void CTest::Key_Input()
{
	if (GET(CKeyMgr)->Key_Down(VK_TAB))
	{
		g_bDebugMod = !g_bDebugMod;
	}
}