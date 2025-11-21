#include "pch.h"
#include "CEdit.h"
#include "CLineMgr.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CPlayer.h"
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
	CObjMgr::Get_Instance()->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(100.f, 100.f));
	CObjMgr::Get_Instance()->Initialize();
	CLineMgr::Get_Instance()->Initialize();
}

void CEdit::Update()
{
	GetCursorPos(&m_ptMouse);
	ScreenToClient(g_hWnd, &m_ptMouse);

	// 키 매니저
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8001)
	{
		m_ptLeft.x = m_ptMouse.x;
		m_ptLeft.y = m_ptMouse.y;
		m_bIsDrawing = true;
	}
	else if (GetAsyncKeyState(VK_RBUTTON) & 0x8001)
	{
		m_ptRight.x = m_ptMouse.x;
		m_ptRight.y = m_ptMouse.y;
		CLineMgr::Get_Instance()->Add_Line(new CLine(m_ptLeft, m_ptRight));
		m_ptLeft.x = m_ptMouse.x;
		m_ptLeft.y = m_ptMouse.y;
		m_bIsDrawing = false;
	}

	CObjMgr::Get_Instance()->Update();
	CLineMgr::Get_Instance()->Update();
}

void CEdit::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	CLineMgr::Get_Instance()->Late_Update();
}

void CEdit::Render(HDC hDC)
{
	Rectangle(hDC, 0, 0, WINCX, WINCY);

	if (m_bIsDrawing)
	{
		MoveToEx(hDC, m_ptLeft.x, m_ptLeft.y, nullptr);
		LineTo(hDC, m_ptMouse.x, m_ptMouse.y);
	}


	CObjMgr::Get_Instance()->Render(hDC);
	CLineMgr::Get_Instance()->Render(hDC);
}

void CEdit::Release()
{
}
