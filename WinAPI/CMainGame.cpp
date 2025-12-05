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
#include "CBelialScene.h"
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
	CScene* pScene = new CLogo;
	pScene->SetSceneID(SCENE_LOGO);
	GET(CSceneMgr)->CreateScene(L"Logo", pScene);
	pScene = new CTest;
	pScene->SetSceneID(SCENE_TEST);
	GET(CSceneMgr)->CreateScene(L"Test", pScene);
	pScene = new CBelialScene;
	pScene->SetSceneID(SCENE_BELIAL);
	GET(CSceneMgr)->CreateScene(L"Belial", pScene);
	pScene = new CTileEditScene;
	pScene->SetSceneID(SCENE_MAPTOOL);
	GET(CSceneMgr)->CreateScene(L"TileEdit", pScene);

	// 최초로 나올 씬
	GET(CSceneMgr)->ChangeScene(L"Logo");

	GET(CMouse)->Initialize();


#ifdef _DEBUG

	if (::AllocConsole() == TRUE)
	{
		FILE* nfp[3];
		freopen_s(nfp + 0, "CONOUT$", "rb", stdin);
		freopen_s(nfp + 1, "CONOUT$", "wb", stdout);
		freopen_s(nfp + 2, "CONOUT$", "wb", stderr);
		std::ios::sync_with_stdio();
	}

#endif // _DEBUG
	
}

void CMainGame::Update()
{
	GET(CTimeMgr)->Update();
	GET(CMouse)->Update();
	GET(CSceneMgr)->Update();
	GET(CObjMgr)->Update();
	GET(CCamera)->Update();
	GET(CTileMgr)->Update();
}

void CMainGame::Late_Update()
{
	GET(CSceneMgr)->Late_Update();
	GET(CKeyMgr)->Update();
	GET(CObjMgr)->Late_Update();
	GET(CTileMgr)->Late_Update();
	GET(CMouse)->Late_Update();
	if (!GET(CObjMgr)->GetObjLayer(OBJ_PLAYER).empty())
	{
		CCollisionMgr::MonsterDetecPlayer(GET(CObjMgr)->GetObjLayer(OBJ_PLAYER).front(), GET(CObjMgr)->GetObjLayer(OBJ_MONSTER));
		CCollisionMgr::Collision_Bullet(GET(CObjMgr)->GetObjLayer(OBJ_PLAYER), GET(CObjMgr)->GetObjLayer(OBJ_ENEMY_BULLET));
		CCollisionMgr::Collision_Bullet(GET(CObjMgr)->GetObjLayer(OBJ_MONSTER), GET(CObjMgr)->GetObjLayer(OBJ_PLAYER_BULLET));
	}
	CCollisionMgr::Collision_Rect(GET(CTileMgr)->GetVecTile(), GET(CObjMgr)->GetObjLayer(OBJ_ENEMY_BULLET));
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

	GET(CSceneMgr)->Render(m_hBackDC);
	GET(CTileMgr)->Render(m_hBackDC);
	GET(CObjMgr)->Render(m_hBackDC);
	GET(CMouse)->Render(m_hBackDC);

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
#ifdef _DEBUG

	FreeConsole();

#endif // _DEBUG

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
