#include "pch.h"
#include "CMainGame.h"
#include "CSceneMgr.h"
#include "CObjMgr.h"
#include "CSceneMgr.h"
#include "CLogo.h"
#include "CPlayer.h"
#include "CResourceMgr.h"
#include "CLineMgr.h"
#include "CTest.h"
#include "CKeyMgr.h"
#include "CCamera.h"
#include "CTimeMgr.h"
#include "CTileEditScene.h"
#include "CTileMgr.h"
#include "CMouse.h"
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
	GET(CTimeMgr)->Initialize();
	m_hDC = GetDC(g_hWnd);
	m_hBackDC = CreateCompatibleDC(m_hDC);
	m_hBitMap = CreateCompatibleBitmap(m_hDC, WINCX, WINCY);
	HBITMAP hBit = (HBITMAP)SelectObject(m_hBackDC, m_hBitMap);
	DeleteObject(hBit);


	//씬 등록
	GET(CSceneMgr)->CreateScene(L"Logo", new CLogo);
	GET(CSceneMgr)->CreateScene(L"Test", new CTest);
	GET(CSceneMgr)->CreateScene(L"TileEdit", new CTileEditScene);

	// 최초로 나올 씬
	GET(CSceneMgr)->ChangeScene(L"Test");
	
}

void CMainGame::Update()
{
	GET(CTimeMgr)->Update();
	GET(CSceneMgr)->Update();
}

void CMainGame::Late_Update()
{
	GET(CSceneMgr)->Late_Update();
	GET(CKeyMgr)->Update();
}

void CMainGame::Render()
{
	++m_iFps;

	DWORD curTime = GetTickCount();
	if (m_dwLastTime + 1000 < curTime)
	{
		swprintf_s(m_szFPS, L"FPS : %d, DT : %f, m_vLookAt : (%f, %f)", m_iFps, DT, GET(CCamera)->GetLookAt().fX, GET(CCamera)->GetLookAt().fY);
		m_iFps = 0;


		SetWindowText(g_hWnd, m_szFPS);

		m_dwLastTime = curTime;
	}

	Graphics graphics(m_hBackDC);

	GET(CSceneMgr)->Render(m_hBackDC);

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
	CMouse::Destroy_Instance();
	CTileMgr::Destroy_Instance();
	CCamera::Destroy_Instance();
	CKeyMgr::Destroy_Instance();
	CLineMgr::Destroy_Instance();
	CResourceMgr::Destroy_Instance();
	CSceneMgr::Destroy_Instance();
	CObjMgr::Destroy_Instance();
	CTimeMgr::Destroy_Instance();
	ReleaseDC(g_hWnd, m_hDC);
}
