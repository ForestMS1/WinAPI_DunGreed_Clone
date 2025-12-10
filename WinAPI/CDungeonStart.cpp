#include "pch.h"
#include "CDungeonStart.h"
#include "CPlayer.h"
#include "CGiantBat.h"
#include "CPlayerUI.h"
#include "CInventoryUI.h"
#include "CDoor.h"
CDungeonStart::CDungeonStart()
{
}

CDungeonStart::~CDungeonStart()
{
}

void CDungeonStart::Initialize()
{
	GET(CObjMgr)->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(500.f, 600.f));
	//GET(CObjMgr)->AddObject(OBJ_MONSTER, CAbstractFactory<CGiantBat>::Create(1400.f, 500.f));
	GET(CObjMgr)->Initialize();
	GET(CLineMgr)->Initialize();
	GET(CTileMgr)->Initialize();
	GET(CTileMgr)->Load_Tile(L"DungeonStart");

	GET(CPlayerMgr)->Initialize();
	GET(CUIMgr)->Insert_UI(L"PlayerUI", new CPlayerUI(GET(CPlayerMgr)->GetPlayer()));
	GET(CUIMgr)->Insert_UI(L"InventoryUI", new CInventoryUI(GET(CPlayerMgr)->GetPlayer()));
	GET(CUIMgr)->Initialize();

	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Background/SubBG.bmp", L"SubBG");

	// Camera 지정
	GET(CCamera)->Initialize();
	//GET(CCamera)->SetLookAt(Vec2(WINCX >> 1, WINCY >> 1));
	GET(CCamera)->SetTarget(GET(CObjMgr)->GetObjLayer(OBJ_PLAYER).front());

	GET(CSoundMgr)->PlayBGM(L"JailField.wav", 1.f);

	//---------------------------------문 설치---------------------------------------
	//이미 클리어 한 씬이면 문 설치 안함
	if (m_bIsClearScene)
		return;
	CObj* pDoor = CAbstractFactory<CDoor>::Create(80.f, 545.f);
	dynamic_cast<CDoor*>(pDoor)->SetNextSceneName(L"Dungeon01");
	GET(CObjMgr)->AddObject(OBJ_DOOR, pDoor);
	//---------------------------------문 설치---------------------------------------
}

void CDungeonStart::Update()
{
	OpenDoor();
}

void CDungeonStart::Late_Update()
{
	DoorToNextScene();
}

void CDungeonStart::Render(HDC hDC)
{
	int scrollX = GET(CCamera)->Get_ScrollX();
	int scrollY = GET(CCamera)->Get_ScrollY();
	Rectangle(hDC, 0, 0, WINCX, WINCY);
	HDC hBackDC = GET(CResourceMgr)->Find_Bmp(L"SubBG");
	GdiTransparentBlt(
		hDC,
		0 - scrollX,
		0 - scrollY,
		WINCX,
		WINCY,
		hBackDC,
		0,
		0,
		320,
		180,
		RGB(255, 0, 255));
	GdiTransparentBlt(
		hDC,
		WINCX - scrollX,
		0 - scrollY,
		WINCX,
		WINCY,
		hBackDC,
		0,
		0,
		320,
		180,
		RGB(255, 0, 255));
	GdiTransparentBlt(
		hDC,
		0 - scrollX,
		WINCY - scrollY,
		WINCX,
		WINCY,
		hBackDC,
		0,
		0,
		320,
		180,
		RGB(255, 0, 255));
	GdiTransparentBlt(
		hDC,
		WINCX - scrollX,
		WINCY - scrollY,
		WINCX,
		WINCY,
		hBackDC,
		0,
		0,
		320,
		180,
		RGB(255, 0, 255));
}

void CDungeonStart::Release()
{
	GET(CObjMgr)->DeleteAllLayer();
	GET(CTileMgr)->Clear_Tile();
	GET(CUIMgr)->Release();
	//GET(CSoundMgr)->StopAll();
}
