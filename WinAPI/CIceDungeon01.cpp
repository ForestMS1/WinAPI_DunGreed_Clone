#include "pch.h"
#include "CIceDungeon01.h"
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
#include "CSnow.h"
#include "CNPC_Xmas.h"
#include "CPresent.h"
CIceDungeon01::CIceDungeon01()
{
}

CIceDungeon01::~CIceDungeon01()
{
}

void CIceDungeon01::Initialize()
{
	//아직 클리어 안한 씬에서만 몹 생성
	if (!m_bIsClearScene)
	{
		GET(CObjMgr)->AddObject(OBJ_MONSTER, CAbstractFactory<CGiantBat>::Create(700.f, 500.f));
		//GET(CObjMgr)->AddObject(OBJ_MONSTER, CAbstractFactory<CBanshee>::Create(800.f, 500.f));
		//GET(CObjMgr)->AddObject(OBJ_MONSTER, CAbstractFactory<CBat>::Create(1200.f, 500.f));
		//GET(CObjMgr)->AddObject(OBJ_MONSTER, CAbstractFactory<CLittleGhost>::Create(1200.f, 200.f));
		//GET(CObjMgr)->AddObject(OBJ_MONSTER, CAbstractFactory<CBigWhiteSkel>::Create(800.f, 200.f));
		//GET(CObjMgr)->AddObject(OBJ_NPC, CAbstractFactory<CTresure>::Create(800, 500.f));

	}
	GET(CObjMgr)->AddObject(OBJ_NPC, CAbstractFactory<CNPC_Xmas>::Create(1500, 860));
	GET(CObjMgr)->AddObject(OBJ_NPC, CAbstractFactory<CPresent>::Create(1200, 422));


	CSnow* pSnow = new CSnow;
	pSnow->Initialize();
	GET(CObjMgr)->AddObject(OBJ_EFFECT, pSnow);
	switch (GET(CSceneMgr)->GetPreSceneID())
	{
	case SCENE_DUNGEON_06:
		GET(CObjMgr)->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(990.f, 195.f));
		break;
	case SCENE_NIFLEHEIM:
		GET(CObjMgr)->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(1915.f, 805.f));
		break;
	default:
		GET(CObjMgr)->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(990.f, 195.f));
		break;
	}
	GET(CPlayerMgr)->Initialize();

	GET(CObjMgr)->Initialize();
	GET(CLineMgr)->Initialize();
	GET(CTileMgr)->Initialize();
	GET(CTileMgr)->Load_Tile(L"IceDungeon01");

	GET(CUIMgr)->Insert_UI(L"PlayerUI", new CPlayerUI(GET(CPlayerMgr)->GetPlayer()));
	GET(CUIMgr)->Insert_UI(L"InventoryUI", new CInventoryUI(GET(CPlayerMgr)->GetPlayer()));
	GET(CUIMgr)->Initialize();

	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Background/BGLayer_0.bmp", L"BGLayer_0");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Background/Snow.bmp", L"Snow");

	// Camera 지정
	GET(CCamera)->Initialize();
	GET(CCamera)->SetTarget(GET(CObjMgr)->GetObjLayer(OBJ_PLAYER).front());

	//---------------------------------문 설치---------------------------------------
	CObj* pDoor = CAbstractFactory<CDoor>::Create(990.f, 95.f);
	dynamic_cast<CDoor*>(pDoor)->SetNextSceneName(L"Dungeon06");
	dynamic_cast<CDoor*>(pDoor)->SetDoorState(CDoor::CLOSE_BOTTOM);
	GET(CObjMgr)->AddObject(OBJ_DOOR, pDoor);

	pDoor = CAbstractFactory<CDoor>::Create(2015.f, 805.f);
	dynamic_cast<CDoor*>(pDoor)->SetNextSceneName(L"NifleHeim");
	dynamic_cast<CDoor*>(pDoor)->SetDoorState(CDoor::CLOSE_RIGHT);
	GET(CObjMgr)->AddObject(OBJ_DOOR, pDoor);
	//---------------------------------문 설치---------------------------------------

	//GET(CSoundMgr)->StopSound(SOUND_BGM);
	GET(CSoundMgr)->StopAll();
	GET(CSoundMgr)->PlayBGM(L"2.IceField.wav", 1.f);
}

void CIceDungeon01::Update()
{
	m_bIsClearScene = GET(CObjMgr)->GetObjLayer(OBJ_MONSTER).empty();
	OpenDoor();
}

void CIceDungeon01::Late_Update()
{
	DoorToNextScene();
}

void CIceDungeon01::Render(HDC hDC)
{
	int scrollX = GET(CCamera)->Get_ScrollX();
	int scrollY = GET(CCamera)->Get_ScrollY();
	Rectangle(hDC, 0, 0, WINCX, WINCY);

	HDC hBackDC = GET(CResourceMgr)->Find_Bmp(L"BGLayer_0");
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			GdiTransparentBlt(
				hDC,
				(320 * j),
				(260 * i),
				320,
				260,
				hBackDC,
				0,
				0,
				320,
				260,
				RGB(255, 0, 255)
			);
		}
	}
}

void CIceDungeon01::Release()
{
	GET(CObjMgr)->DeleteAllLayer();
	GET(CTileMgr)->Clear_Tile();
	GET(CUIMgr)->Release();
	//GET(CSoundMgr)->StopAll();
}
