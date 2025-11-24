#include "pch.h"
#include "CEdit.h"
#include "CLineMgr.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CPlayer.h"
#include "CCamera.h"
#include "CResourceMgr.h"
#include "CKeyMgr.h"
CEdit::CEdit() : m_bIsDrawing(false)
{
	ZeroMemory(&m_ptMouse, sizeof(m_ptMouse));
	ZeroMemory(&m_ptLeft, sizeof(m_ptLeft));
	ZeroMemory(&m_ptRight, sizeof(m_ptRight));
}

CEdit::~CEdit()
{
}

void CEdit::Initialize()
{
	CResourceMgr::Get_Instance()->Insert_Bmp(L"../Resources/Images/Town/Cloud.bmp", L"Cloud");
	CObjMgr::Get_Instance()->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(100.f, 100.f));
	CObjMgr::Get_Instance()->Initialize();
	CLineMgr::Get_Instance()->Initialize();

	// Camera 지정
	GET(CCamera)->SetLookAt(Vec2(WINCX >> 1, WINCY >> 1));
	//GET(CCamera)->SetTarget(GET(CObjMgr)->GetObjLayer(OBJ_PLAYER).front());
}

void CEdit::Update()
{
	GetCursorPos(&m_ptMouse);
	ScreenToClient(g_hWnd, &m_ptMouse);


	//m_ptMouse.x = (int)GET(CCamera)->GetRealPos(m_ptMouse).fX;
	//m_ptMouse.y = (int)GET(CCamera)->GetRealPos(m_ptMouse).fY;

	// 키 매니저
	//if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	if(GET(CKeyMgr)->Key_Down(VK_LBUTTON))
	{
		//m_ptLeft.x = m_ptMouse.x;
		//m_ptLeft.y = m_ptMouse.y;
		//m_bIsDrawing = true;
		Vec2 vLookAt = GET(CCamera)->GetRealPos(m_ptMouse);
		GET(CCamera)->SetLookAt(vLookAt);
	}
	else if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
	{
		//m_ptRight.x = m_ptMouse.x;
		//m_ptRight.y = m_ptMouse.y;
		//CLineMgr::Get_Instance()->Add_Line(new CLine(m_ptLeft, m_ptRight));
		//m_ptLeft.x = m_ptMouse.x;
		//m_ptLeft.y = m_ptMouse.y;
		//m_bIsDrawing = false;
	}




	GET(CObjMgr)->Update();
	GET(CLineMgr)->Update();
	GET(CCamera)->Update();
}

void CEdit::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	CLineMgr::Get_Instance()->Late_Update();
}

void CEdit::Render(HDC hDC)
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
		MoveToEx(hDC, m_ptLeft.x - (int)GET(CCamera)->GetDiff().fX, m_ptLeft.y - (int)GET(CCamera)->GetDiff().fY, nullptr);
		LineTo(hDC, m_ptMouse.x - (int)GET(CCamera)->GetDiff().fX, m_ptMouse.y - (int)GET(CCamera)->GetDiff().fY);
		//MoveToEx(hDC, (int)vMouseRenderPos.fX, (int)vMouseRenderPos.fY, nullptr);
		//LineTo(hDC, (int)vMouseRenderPos.fX, (int)vMouseRenderPos.fY);
	}


	CObjMgr::Get_Instance()->Render(hDC);
	CLineMgr::Get_Instance()->Render(hDC);
}

void CEdit::Release()
{
}
