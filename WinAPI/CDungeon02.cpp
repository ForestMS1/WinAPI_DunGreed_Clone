#include "pch.h"
#include "CDungeon02.h"
#include "CPlayer.h"
#include "CGiantBat.h"
#include "CPlayerUI.h"
#include "CInventoryUI.h"
#include "CBanshee.h"
#include "CDoor.h"
#include "CBat.h"
#include "CLittleGhost.h"
#include "CBigWhiteSkel.h"
#include "CTresure.h"
CDungeon02::CDungeon02()
{
}

CDungeon02::~CDungeon02()
{
}

void CDungeon02::Initialize()
{
	//아직 클리어 안한 씬에서만 몹 생성
	if (!m_bIsClearScene)
	{
		GET(CObjMgr)->AddObject(OBJ_MONSTER, CAbstractFactory<CGiantBat>::Create(250, 525.f));
		//GET(CObjMgr)->AddObject(OBJ_MONSTER, CAbstractFactory<CBanshee>::Create(800.f, 500.f));
		GET(CObjMgr)->AddObject(OBJ_MONSTER, CAbstractFactory<CBat>::Create(1280, 770));
		//GET(CObjMgr)->AddObject(OBJ_MONSTER, CAbstractFactory<CLittleGhost>::Create(1200.f, 200.f));
		GET(CObjMgr)->AddObject(OBJ_MONSTER, CAbstractFactory<CBigWhiteSkel>::Create(520, 670));
		GET(CObjMgr)->AddObject(OBJ_NPC, CAbstractFactory<CTresure>::Create(800, 500.f));

	}
	switch (GET(CSceneMgr)->GetPreSceneID())
	{
	case SCENE_DUNGEON_01:
		GET(CObjMgr)->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(1500.f, 926.f));
		break;
	case SCENE_DUNGEON_FOOD_SHOP:
		GET(CObjMgr)->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(170.f, 220.f));
	default:
		break;
	}
	GET(CPlayerMgr)->Initialize();

	GET(CObjMgr)->Initialize();
	GET(CLineMgr)->Initialize();
	GET(CTileMgr)->Initialize();
	GET(CTileMgr)->Load_Tile(L"Dungeon02");

	GET(CUIMgr)->Insert_UI(L"PlayerUI", new CPlayerUI(GET(CPlayerMgr)->GetPlayer()));
	GET(CUIMgr)->Insert_UI(L"InventoryUI", new CInventoryUI(GET(CPlayerMgr)->GetPlayer()));
	GET(CUIMgr)->Initialize();

	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Background/SubBG.bmp", L"SubBG");

	// Camera 지정
	GET(CCamera)->Initialize();
	GET(CCamera)->SetTarget(GET(CObjMgr)->GetObjLayer(OBJ_PLAYER).front());

	//---------------------------------문 설치---------------------------------------
	CObj* pDoor = CAbstractFactory<CDoor>::Create(70.f, 220.f);
	dynamic_cast<CDoor*>(pDoor)->SetNextSceneName(L"DungeonFoodShop");
	GET(CObjMgr)->AddObject(OBJ_DOOR, pDoor);

	pDoor = CAbstractFactory<CDoor>::Create(1600.f, 926.f);
	dynamic_cast<CDoor*>(pDoor)->SetNextSceneName(L"Dungeon01");
	dynamic_cast<CDoor*>(pDoor)->SetDoorState(CDoor::CLOSE_RIGHT);
	GET(CObjMgr)->AddObject(OBJ_DOOR, pDoor);
	//---------------------------------문 설치---------------------------------------

	//GET(CSoundMgr)->PlayBGM(L"JailField.wav", 1.f);
}

void CDungeon02::Update()
{
	m_bIsClearScene = GET(CObjMgr)->GetObjLayer(OBJ_MONSTER).empty();
	OpenDoor();
}

void CDungeon02::Late_Update()
{
	DoorToNextScene();
}

void CDungeon02::Render(HDC hDC)
{
	int scrollX = GET(CCamera)->Get_ScrollX();
	int scrollY = GET(CCamera)->Get_ScrollY();
	Rectangle(hDC, 0, 0, WINCX, WINCY);
	//HDC hBackDC = GET(CResourceMgr)->Find_Bmp(L"SubBG");
	//GdiTransparentBlt(
	//	hDC,
	//	0 - scrollX,
	//	0 - scrollY,
	//	WINCX,
	//	WINCY,
	//	hBackDC,
	//	0,
	//	0,
	//	320,
	//	180,
	//	RGB(255, 0, 255));
	//GdiTransparentBlt(
	//	hDC,
	//	WINCX - scrollX,
	//	0 - scrollY,
	//	WINCX,
	//	WINCY,
	//	hBackDC,
	//	0,
	//	0,
	//	320,
	//	180,
	//	RGB(255, 0, 255));
	//GdiTransparentBlt(
	//	hDC,
	//	0 - scrollX,
	//	WINCY - scrollY,
	//	WINCX,
	//	WINCY,
	//	hBackDC,
	//	0,
	//	0,
	//	320,
	//	180,
	//	RGB(255, 0, 255));
	//GdiTransparentBlt(
	//	hDC,
	//	WINCX - scrollX,
	//	WINCY - scrollY,
	//	WINCX,
	//	WINCY,
	//	hBackDC,
	//	0,
	//	0,
	//	320,
	//	180,
	//	RGB(255, 0, 255));
}

void CDungeon02::Release()
{
	GET(CObjMgr)->DeleteAllLayer();
	GET(CTileMgr)->Clear_Tile();
	GET(CUIMgr)->Release();
	//GET(CSoundMgr)->StopAll();
}
