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

	//¾À µî·Ï
	CSceneMgr::Get_Instance()->CreateScene(L"Logo", new CLogo);


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

	CObjMgr::Get_Instance()->Render(m_hDC);

	//m_hBackDC = CreateCompatibleDC(m_hDC);
	//
	//HBITMAP hBit = (HBITMAP)SelectObject(m_hBackDC, m_hBitMap);

	//DeleteObject(hBit);

	//BitBlt(m_hDC, 0, 0, WINCX, WINCY, m_hBackDC, 0, 0, 0);
}

void CMainGame::Release()
{
	CResourceMgr::Destroy_Instance();
	CSceneMgr::Destroy_Instance();
	CObjMgr::Destroy_Instance();
	ReleaseDC(g_hWnd, m_hDC);
}
