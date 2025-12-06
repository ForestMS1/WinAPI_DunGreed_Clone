#include "pch.h"
#include "CBelialScene.h"
#include "CPlayer.h"
#include "CBelial.h"
#include "CPlayerUI.h"
#include "CInventoryUI.h"

CBelialScene::CBelialScene()
{
}

CBelialScene::~CBelialScene()
{
}

void CBelialScene::Initialize()
{
	GET(CObjMgr)->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(100.f, 700.f));
	GET(CObjMgr)->AddObject(OBJ_MONSTER, CAbstractFactory<CBelial>::Create(1400.f, 500.f));
	GET(CObjMgr)->Initialize();
	GET(CLineMgr)->Initialize();
	GET(CTileMgr)->Initialize();
	GET(CTileMgr)->Load_Tile(L"BelialSceneTile");

	GET(CPlayerMgr)->Initialize();
	GET(CUIMgr)->Insert_UI(L"PlayerUI", new CPlayerUI(GET(CPlayerMgr)->GetPlayer()));
	GET(CUIMgr)->Insert_UI(L"InventoryUI", new CInventoryUI(GET(CPlayerMgr)->GetPlayer()));
	GET(CUIMgr)->Initialize();
	// Camera ÁöÁ¤
	GET(CCamera)->Initialize();
	//GET(CCamera)->SetLookAt(Vec2(WINCX >> 1, WINCY >> 1));
	GET(CCamera)->SetTarget(GET(CObjMgr)->GetObjLayer(OBJ_PLAYER).front());
}

void CBelialScene::Update()
{
}

void CBelialScene::Late_Update()
{
}

void CBelialScene::Render(HDC hDC)
{
	Rectangle(hDC, 0, 0, WINCX, WINCY);
	//GET(CTileMgr)->Render(hDC);
	//GET(CObjMgr)->Render(hDC);
}

void CBelialScene::Release()
{
	GET(CObjMgr)->DeleteLayerObj(OBJ_PLAYER);
	GET(CObjMgr)->DeleteLayerObj(OBJ_MONSTER);
}
