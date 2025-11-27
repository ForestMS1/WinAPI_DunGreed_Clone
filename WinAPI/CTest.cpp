#include "pch.h"
#include "CTest.h"
#include "CLineMgr.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CPlayer.h"
#include "CCamera.h"
#include "CResourceMgr.h"
#include "CKeyMgr.h"
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
	CResourceMgr::Get_Instance()->Insert_Bmp(L"../Resources/Images/Town/Cloud.bmp", L"Cloud");
	//CResourceMgr::Get_Instance()->Insert_Bmp(L"../Resources/Images/")
	CObjMgr::Get_Instance()->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(100.f, 100.f));
	CObjMgr::Get_Instance()->Initialize();
	CLineMgr::Get_Instance()->Initialize();

	// Camera 지정
	GET(CCamera)->SetLookAt(Vec2(WINCX >> 1, WINCY >> 1));
	GET(CCamera)->SetTarget(GET(CObjMgr)->GetObjLayer(OBJ_PLAYER).front());
}

void CTest::Update()
{
	GetCursorPos(&m_ptMouse);
	ScreenToClient(g_hWnd, &m_ptMouse);

	Vec2 pos = GET(CCamera)->GetRealPos(m_ptMouse);

	if (GET(CKeyMgr)->Key_Down(VK_LBUTTON))
	{
		m_bIsDrawing = true;
		m_ptLeft.x = (int)pos.fX;
		m_ptLeft.y = (int)pos.fY;
	}
	else if (GET(CKeyMgr)->Key_Down(VK_RBUTTON))
	{
		m_bIsDrawing = false;
		m_ptRight.x = (int)pos.fX;
		m_ptRight.y = (int)pos.fY;
		GET(CLineMgr)->Add_Line(new CLine(m_ptLeft, m_ptRight));
	}


	GET(CObjMgr)->Update();
	GET(CLineMgr)->Update();
	GET(CCamera)->Update();
}

void CTest::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	CLineMgr::Get_Instance()->Late_Update();
}

void CTest::Render(HDC hDC)
{
	Rectangle(hDC, 0, 0, WINCX, WINCY);
	HDC hMemDC = CResourceMgr::Get_Instance()->Find_Bmp(L"Cloud");

	GdiTransparentBlt(
		hDC,
		-(int)GET(CCamera)->GetDiff().fX,				// 복사 받을 공간의 LEFT	
		-(int)GET(CCamera)->GetDiff().fY,				// 복사 받을 공간의 TOP
		WINCX,											// 복사 받을 공간의 가로 
		WINCY,											// 복사 받을 공간의 세로 
		hMemDC,											// 복사 할 DC
		0,
		0,
		960,
		540,
		RGB(255, 0, 255)
	);

	if (m_bIsDrawing)
	{
		Vec2 st = GET(CCamera)->GetRenderPos(Vec2(m_ptLeft.x, m_ptLeft.y));
		MoveToEx(hDC, (int)st.fX, (int)st.fY, nullptr);
		LineTo(hDC, m_ptMouse.x, m_ptMouse.y);
	}


	CObjMgr::Get_Instance()->Render(hDC);
	CLineMgr::Get_Instance()->Render(hDC);
}

void CTest::Release()
{
}
