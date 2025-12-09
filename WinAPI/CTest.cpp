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
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Town/Cloud.bmp", L"Cloud");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Town/TownBG_Day.bmp", L"TownBG_Day");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Town/TownLayer_Day.bmp", L"TownLayer_Day");
	GET(CObjMgr)->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(100.f, 100.f));
	//GET(CObjMgr)->AddObject(OBJ_MONSTER, CAbstractFactory<CBelial>::Create(2000.f, 200.f));
	GET(CObjMgr)->AddObject(OBJ_MONSTER, CAbstractFactory<CGiantBat>::Create(500.f, 200.f));
	GET(CObjMgr)->Initialize();
	GET(CPlayerMgr)->Initialize();
	GET(CLineMgr)->Initialize();
	GET(CTileMgr)->Initialize();
	GET(CTileMgr)->Load_Tile(L"TestScene");

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
}

void CTest::Render(HDC hDC)
{
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
	//hMemDC = CResourceMgr::Get_Instance()->Find_Bmp(L"TownLayer_Day");
	//GdiTransparentBlt(
	//	hDC,
	//	0,												// 복사 받을 공간의 LEFT	
	//	0,												// 복사 받을 공간의 TOP
	//	WINCX,											// 복사 받을 공간의 가로 
	//	WINCY,											// 복사 받을 공간의 세로 
	//	hMemDC,											// 복사 할 DC
	//	0,
	//	0,
	//	320,
	//	95,
	//	RGB(255, 0, 255)
	//);

	//GET(CTileMgr)->Render(hDC);
	//GET(CObjMgr)->Render(hDC);
	//GET(CLineMgr)->Render(hDC); //굳이 그릴필요 없음
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