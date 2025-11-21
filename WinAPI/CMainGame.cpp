#include "pch.h"
#include "CMainGame.h"

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
}

void CMainGame::Update()
{
}

void CMainGame::Late_Update()
{
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
}

void CMainGame::Release()
{

	ReleaseDC(g_hWnd, m_hDC);
}
