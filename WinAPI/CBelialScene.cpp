#include "pch.h"
#include "CBelialScene.h"
#include "CPlayer.h"
#include "CBelial.h"
#include "CPlayerUI.h"
#include "CInventoryUI.h"
#include "CDoor.h"
CBelialScene::CBelialScene()
{
}

CBelialScene::~CBelialScene()
{
}

void CBelialScene::Initialize()
{
	GET(CObjMgr)->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(300.f, 900.f));
	GET(CObjMgr)->AddObject(OBJ_MONSTER, CAbstractFactory<CBelial>::Create(1400.f, 500.f));
	GET(CObjMgr)->Initialize();
	GET(CLineMgr)->Initialize();
	GET(CTileMgr)->Initialize();
	GET(CTileMgr)->Load_Tile(L"BelialScene");

	GET(CPlayerMgr)->Initialize();
	GET(CUIMgr)->Insert_UI(L"PlayerUI", new CPlayerUI(GET(CPlayerMgr)->GetPlayer()));
	GET(CUIMgr)->Insert_UI(L"InventoryUI", new CInventoryUI(GET(CPlayerMgr)->GetPlayer()));
	GET(CUIMgr)->Initialize();
	// Camera 지정
	GET(CCamera)->Initialize();
	//GET(CCamera)->SetLookAt(Vec2(WINCX >> 1, WINCY >> 1));
	GET(CCamera)->SetTarget(GET(CObjMgr)->GetObjLayer(OBJ_PLAYER).front());

	//---------------------------------문 설치---------------------------------------
	CObj* pDoor = CAbstractFactory<CDoor>::Create(200.f, 990.f);
	dynamic_cast<CDoor*>(pDoor)->SetNextSceneName(L"Dungeon01");
	GET(CObjMgr)->AddObject(OBJ_DOOR, pDoor);
	//---------------------------------문 설치---------------------------------------
}

void CBelialScene::Update()
{
	OpenDoor();
}

void CBelialScene::Late_Update()
{
	DoorToNextScene();
}

void CBelialScene::Render(HDC hDC)
{
	Rectangle(hDC, 0, 0, WINCX, WINCY);
	//GET(CTileMgr)->Render(hDC);
	//GET(CObjMgr)->Render(hDC);
}

void CBelialScene::Release()
{
	//GET(CObjMgr)->DeleteLayerObj(OBJ_PLAYER);
	//GET(CObjMgr)->DeleteLayerObj(OBJ_MONSTER);
	GET(CObjMgr)->DeleteAllLayer();
	GET(CTileMgr)->Clear_Tile();
	GET(CUIMgr)->Release();
	GET(CSoundMgr)->StopAll();
}
