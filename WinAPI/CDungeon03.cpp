#include "pch.h"
#include "CDungeon03.h"
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
#include "CBrokenCell.h"
#include "CSkelDog.h"
#include "CTorch.h"
CDungeon03::CDungeon03()
{
}

CDungeon03::~CDungeon03()
{
}

void CDungeon03::Initialize()
{
	//아직 클리어 안한 씬에서만 몹 생성
	if (!m_bIsClearScene)
	{
		//GET(CObjMgr)->AddObject(OBJ_MONSTER, CAbstractFactory<CGiantBat>::Create(700.f, 500.f));
		//GET(CObjMgr)->AddObject(OBJ_MONSTER, CAbstractFactory<CBanshee>::Create(800.f, 500.f));
		GET(CObjMgr)->AddObject(OBJ_MONSTER, CAbstractFactory<CSkelDog>::Create(600.f, 600.f));
		GET(CObjMgr)->AddObject(OBJ_MONSTER, CAbstractFactory<CSkelDog>::Create(700.f, 600.f));
		GET(CObjMgr)->AddObject(OBJ_MONSTER, CAbstractFactory<CSkelDog>::Create(800.f, 600.f));
		GET(CObjMgr)->AddObject(OBJ_MONSTER, CAbstractFactory<CSkelDog>::Create(900.f, 600.f));
		GET(CObjMgr)->AddObject(OBJ_MONSTER, CAbstractFactory<CBat>::Create(1200.f, 550.f));
		GET(CObjMgr)->AddObject(OBJ_MONSTER, CAbstractFactory<CLittleGhost>::Create(1200.f, 200.f));
		GET(CObjMgr)->AddObject(OBJ_MONSTER, CAbstractFactory<CBigWhiteSkel>::Create(800.f, 200.f));
	}
	GET(CObjMgr)->AddObject(OBJ_EFFECT, CAbstractFactory<CTorch>::Create(735.f, 225));
	GET(CObjMgr)->AddObject(OBJ_EFFECT, CAbstractFactory<CTorch>::Create(345.f, 225));
	GET(CObjMgr)->AddObject(OBJ_EFFECT, CAbstractFactory<CTorch>::Create(555, 615));
	GET(CObjMgr)->AddObject(OBJ_EFFECT, CAbstractFactory<CTorch>::Create(955.f, 615));
	//GET(CObjMgr)->AddObject(OBJ_EFFECT, CAbstractFactory<CBrokenCell>::Create(690, 550));

	switch (GET(CSceneMgr)->GetPreSceneID())
	{
	case SCENE_DUNGEON_START:
		GET(CObjMgr)->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(150.f, 130.f));
		break;
	case SCENE_DUNGEON_04:
		GET(CObjMgr)->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(1980.f, 605.f));
		break;
	default:
		GET(CObjMgr)->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(150.f, 130.f));
		break;
	}
	GET(CPlayerMgr)->Initialize();

	GET(CObjMgr)->Initialize();
	GET(CLineMgr)->Initialize();
	GET(CTileMgr)->Initialize();
	GET(CTileMgr)->Load_Tile(L"Dungeon03");

	GET(CUIMgr)->Insert_UI(L"PlayerUI", new CPlayerUI(GET(CPlayerMgr)->GetPlayer()));
	GET(CUIMgr)->Insert_UI(L"InventoryUI", new CInventoryUI(GET(CPlayerMgr)->GetPlayer()));
	GET(CUIMgr)->Initialize();

	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Background/SubBG.bmp", L"SubBG");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Background/SubBG.bmp", L"SubBG");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Dungeon/BrokenCell0.bmp", L"BrokenCell0");

	// Camera 지정
	GET(CCamera)->Initialize();
	GET(CCamera)->SetTarget(GET(CObjMgr)->GetObjLayer(OBJ_PLAYER).front());

	//---------------------------------문 설치---------------------------------------
	CObj* pDoor = CAbstractFactory<CDoor>::Create(70.f, 220.f);
	dynamic_cast<CDoor*>(pDoor)->SetNextSceneName(L"DungeonStart");
	GET(CObjMgr)->AddObject(OBJ_DOOR, pDoor);
	
	pDoor = CAbstractFactory<CDoor>::Create(2080, 605);
	dynamic_cast<CDoor*>(pDoor)->SetNextSceneName(L"Dungeon04");
	dynamic_cast<CDoor*>(pDoor)->SetDoorState(CDoor::CLOSE_RIGHT);
	GET(CObjMgr)->AddObject(OBJ_DOOR, pDoor);
	//---------------------------------문 설치---------------------------------------

	//GET(CSoundMgr)->PlayBGM(L"JailField.wav", 1.f);
}

void CDungeon03::Update()
{
	m_bIsClearScene = GET(CObjMgr)->GetObjLayer(OBJ_MONSTER).empty();
	OpenDoor();
}

void CDungeon03::Late_Update()
{
	DoorToNextScene();
}

void CDungeon03::Render(HDC hDC)
{
	int scrollX = GET(CCamera)->Get_ScrollX();
	int scrollY = GET(CCamera)->Get_ScrollY();
	Rectangle(hDC, 0, 0, WINCX, WINCY);
}

void CDungeon03::Release()
{
	GET(CObjMgr)->DeleteAllLayer();
	GET(CTileMgr)->Clear_Tile();
	GET(CUIMgr)->Release();
	//GET(CSoundMgr)->StopAll();
}
