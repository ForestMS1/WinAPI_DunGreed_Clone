#include "pch.h"
#include "CDungeon01.h"
#include "CPlayer.h"
#include "CGiantBat.h"
#include "CPlayerUI.h"
#include "CInventoryUI.h"
#include "CBanshee.h"
#include "CDoorLeft.h"
CDungeon01::CDungeon01()
{
}

CDungeon01::~CDungeon01()
{
}

void CDungeon01::Initialize()
{
	GET(CObjMgr)->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(500.f, 600.f));
	GET(CObjMgr)->AddObject(OBJ_MONSTER, CAbstractFactory<CGiantBat>::Create(1400.f, 500.f));
	GET(CObjMgr)->AddObject(OBJ_MONSTER, CAbstractFactory<CBanshee>::Create(1400.f, 500.f));

	CObj* pDoor = CAbstractFactory<CDoorLeft>::Create(100.f, 600.f);
	GET(CObjMgr)->AddObject(OBJ_DOOR, pDoor);
	m_mapDoor.insert({ pDoor, L"Belial" });


	GET(CObjMgr)->Initialize();
	GET(CLineMgr)->Initialize();
	GET(CTileMgr)->Initialize();
	GET(CTileMgr)->Load_Tile(L"Dungeon01");

	GET(CPlayerMgr)->Initialize();
	GET(CUIMgr)->Insert_UI(L"PlayerUI", new CPlayerUI(GET(CPlayerMgr)->GetPlayer()));
	GET(CUIMgr)->Insert_UI(L"InventoryUI", new CInventoryUI(GET(CPlayerMgr)->GetPlayer()));
	GET(CUIMgr)->Initialize();

	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Background/SubBG.bmp", L"SubBG");

	// Camera ÁöÁ¤
	GET(CCamera)->Initialize();
	GET(CCamera)->SetTarget(GET(CObjMgr)->GetObjLayer(OBJ_PLAYER).front());

	//GET(CSoundMgr)->PlayBGM(L"JailField.wav", 1.f);
}

void CDungeon01::Update()
{
	if (GET(CObjMgr)->GetObjLayer(OBJ_MONSTER).empty())
	{
		for (auto& iter : m_mapDoor)
		{
			dynamic_cast<CDoorLeft*>(iter.first)->SetDoorState(CDoorLeft::OPEN);
		}
	}
}

void CDungeon01::Late_Update()
{
	for (auto& iter : m_mapDoor)
	{
		if (dynamic_cast<CDoorLeft*>(iter.first)->GetDoorState() == CDoorLeft::DOOR_STATE::OPEN
			&& CCollisionMgr::Check_Rect(GET(CPlayerMgr)->GetPlayer(), iter.first))
			GET(CSceneMgr)->ChangeScene(iter.second);
	}
}

void CDungeon01::Render(HDC hDC)
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

void CDungeon01::Release()
{
	GET(CObjMgr)->DeleteAllLayer();
	GET(CTileMgr)->Clear_Tile();
	GET(CUIMgr)->Release();
	GET(CSoundMgr)->StopAll();
}
