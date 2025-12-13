#include "pch.h"
#include "CDungeonFoodShop.h"
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
CDungeonFoodShop::CDungeonFoodShop()
{
}

CDungeonFoodShop::~CDungeonFoodShop()
{
}

void CDungeonFoodShop::Initialize()
{
	//아직 클리어 안한 씬에서만 몹 생성
	if (!m_bIsClearScene)
	{
		//GET(CObjMgr)->AddObject(OBJ_MONSTER, CAbstractFactory<CGiantBat>::Create(700.f, 500.f));
		//GET(CObjMgr)->AddObject(OBJ_MONSTER, CAbstractFactory<CBanshee>::Create(800.f, 500.f));
		//GET(CObjMgr)->AddObject(OBJ_MONSTER, CAbstractFactory<CBat>::Create(1200.f, 500.f));
		//GET(CObjMgr)->AddObject(OBJ_MONSTER, CAbstractFactory<CLittleGhost>::Create(1200.f, 200.f));
		//GET(CObjMgr)->AddObject(OBJ_MONSTER, CAbstractFactory<CBigWhiteSkel>::Create(800.f, 200.f));
		//GET(CObjMgr)->AddObject(OBJ_NPC, CAbstractFactory<CTresure>::Create(800, 500.f));

	}
	switch (GET(CSceneMgr)->GetPreSceneID())
	{
	case SCENE_DUNGEON_02:
		GET(CObjMgr)->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(2110.f, 865.f));
		break;
	default:
		GET(CObjMgr)->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(2110.f, 865.f));
		break;
	}
	GET(CPlayerMgr)->Initialize();

	GET(CObjMgr)->Initialize();
	GET(CLineMgr)->Initialize();
	GET(CTileMgr)->Initialize();
	GET(CTileMgr)->Load_Tile(L"DungeonFoodShop");

	GET(CUIMgr)->Insert_UI(L"PlayerUI", new CPlayerUI(GET(CPlayerMgr)->GetPlayer()));
	GET(CUIMgr)->Insert_UI(L"InventoryUI", new CInventoryUI(GET(CPlayerMgr)->GetPlayer()));
	GET(CUIMgr)->Initialize();

	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Background/SubBG.bmp", L"SubBG");

	// Camera 지정
	GET(CCamera)->Initialize();
	GET(CCamera)->SetTarget(GET(CObjMgr)->GetObjLayer(OBJ_PLAYER).front());

	//---------------------------------문 설치---------------------------------------
	CObj* pDoor = CAbstractFactory<CDoor>::Create(2210, 865.f);
	dynamic_cast<CDoor*>(pDoor)->SetNextSceneName(L"Dungeon02");
	dynamic_cast<CDoor*>(pDoor)->SetDoorState(CDoor::CLOSE_RIGHT);
	GET(CObjMgr)->AddObject(OBJ_DOOR, pDoor);
	//---------------------------------문 설치---------------------------------------

	//GET(CSoundMgr)->PlayBGM(L"JailField.wav", 1.f);
}

void CDungeonFoodShop::Update()
{
	m_bIsClearScene = GET(CObjMgr)->GetObjLayer(OBJ_MONSTER).empty();
	OpenDoor();
}

void CDungeonFoodShop::Late_Update()
{
	DoorToNextScene();
}

void CDungeonFoodShop::Render(HDC hDC)
{
	int scrollX = GET(CCamera)->Get_ScrollX();
	int scrollY = GET(CCamera)->Get_ScrollY();
	Rectangle(hDC, 0, 0, WINCX, WINCY);
}

void CDungeonFoodShop::Release()
{
	GET(CObjMgr)->DeleteAllLayer();
	GET(CTileMgr)->Clear_Tile();
	GET(CUIMgr)->Release();
	//GET(CSoundMgr)->StopAll();
}
