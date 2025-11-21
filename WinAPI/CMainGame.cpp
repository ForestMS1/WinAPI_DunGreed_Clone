#include "pch.h"
#include "CMainGame.h"
#include "CSceneMgr.h"
#include "CObjMgr.h"
#include "CSceneMgr.h"
#include "CLogo.h"
#include "CPlayer.h"
#include "CResourceMgr.h"

CMainGame::CMainGame() : m_iFps(0), m_dwLastTime(GetTickCount())
{
	ZeroMemory(&m_szFPS, sizeof(m_szFPS));
}

CMainGame::~CMainGame()
{
	Release();
}

void CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);
	m_hBackDC = CreateCompatibleDC(m_hDC);
	m_hBitMap = CreateCompatibleBitmap(m_hDC, WINCX, WINCY);
	HBITMAP hBit = (HBITMAP)SelectObject(m_hBackDC, m_hBitMap);
	DeleteObject(hBit);


	//씬 등록
	CSceneMgr::Get_Instance()->CreateScene(L"Logo", new CLogo);



	// 최초로 나올 씬
	CSceneMgr::Get_Instance()->ChangeScene(L"Logo");
	
}

void CMainGame::Update()
{
	CObjMgr::Get_Instance()->Update();
}

void CMainGame::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
}

void CMainGame::Render()
{
	++m_iFps;

	if (m_dwLastTime + 1000 < GetTickCount())
	{
		swprintf_s(m_szFPS, L"FPS : %d", m_iFps);

		m_iFps = 0;

		SetWindowText(g_hWnd, m_szFPS);

		m_dwLastTime = GetTickCount();
	}

	Graphics graphics(m_hBackDC);

	CSceneMgr::Get_Instance()->Render(m_hBackDC);

	BitBlt(m_hDC,				// 복사 받을 DC
		0,						// 복사 받을 공간의 LEFT	
		0,						// 복사 받을 공간의 TOP
		WINCX,					// 복사 받을 공간의 가로 
		WINCY,					// 복사 받을 공간의 세로 
		m_hBackDC,				// 복사 할 DC
		0,						// 복사할 이미지의 LEFT, TOP
		0,
		SRCCOPY);				// 그대로 복사
}

void CMainGame::Release()
{
	CResourceMgr::Destroy_Instance();
	CSceneMgr::Destroy_Instance();
	CObjMgr::Destroy_Instance();
	ReleaseDC(g_hWnd, m_hDC);
}
