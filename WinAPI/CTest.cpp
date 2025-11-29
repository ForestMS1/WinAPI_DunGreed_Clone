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
CTest::CTest() : m_bIsDrawing(false)
{
	ZeroMemory(&m_ptMouse, sizeof(m_ptMouse));
	ZeroMemory(&m_ptLeft, sizeof(m_ptLeft));
	ZeroMemory(&m_ptRight, sizeof(m_ptRight));
}

CTest::~CTest()
{
}

void CTest::Initialize()
{
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Town/Cloud.bmp", L"Cloud");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Town/TownBG_Day.bmp", L"TownBG_Day");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Town/TownLayer_Day.bmp", L"TownLayer_Day");
	GET(CObjMgr)->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(100.f, 100.f));
	GET(CObjMgr)->Initialize();
	GET(CLineMgr)->Initialize();
	GET(CTileMgr)->Initialize();
	GET(CTileMgr)->Load_Tile();

	// Camera 지정
	GET(CCamera)->SetLookAt(Vec2(WINCX >> 1, WINCY >> 1));
	GET(CCamera)->SetTarget(GET(CObjMgr)->GetObjLayer(OBJ_PLAYER).front());
}

void CTest::Update()
{
	GetCursorPos(&m_ptMouse);
	ScreenToClient(g_hWnd, &m_ptMouse);

	Vec2 pos = GET(CCamera)->GetRealPos(m_ptMouse);

	//if (GET(CKeyMgr)->Key_Down(VK_LBUTTON))
	//{
	//	m_bIsDrawing = true;
	//	m_ptLeft.x = (int)pos.fX;
	//	m_ptLeft.y = (int)pos.fY;
	//}
	//else if (GET(CKeyMgr)->Key_Down(VK_RBUTTON))
	//{
	//	m_bIsDrawing = false;
	//	m_ptRight.x = (int)pos.fX;
	//	m_ptRight.y = (int)pos.fY;
	//	GET(CLineMgr)->Add_Line(new CLine(m_ptLeft, m_ptRight));
	//}

	Key_Input();
	GET(CObjMgr)->Update();
	GET(CCamera)->Update();
	GET(CTileMgr)->Update();
}

void CTest::Late_Update()
{
	GET(CObjMgr)->Late_Update();
	GET(CTileMgr)->Late_Update();
}

void CTest::Render(HDC hDC)
{
	Rectangle(hDC, 0, 0, WINCX, WINCY);
	HDC hMemDC = CResourceMgr::Get_Instance()->Find_Bmp(L"Cloud");
	//TODO : 배경 무한 움직임
	GdiTransparentBlt(
		hDC,
		0,												// 복사 받을 공간의 LEFT	
		0,												// 복사 받을 공간의 TOP
		WINCX,											// 복사 받을 공간의 가로 
		WINCY,											// 복사 받을 공간의 세로 
		hMemDC,											// 복사 할 DC
		0,
		0,
		960,
		540,
		RGB(255, 0, 255)
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
	hMemDC = CResourceMgr::Get_Instance()->Find_Bmp(L"TownLayer_Day");
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
		95,
		RGB(255, 0, 255)
	);

	GET(CTileMgr)->Render(hDC);
	GET(CObjMgr)->Render(hDC);
	//GET(CLineMgr)->Render(hDC); //굳이 그릴필요 없음
}

void CTest::Release()
{
}

void CTest::Key_Input()
{
	if (GET(CKeyMgr)->Key_Down(VK_TAB))
	{
		g_bDebugMod = !g_bDebugMod;
	}
}