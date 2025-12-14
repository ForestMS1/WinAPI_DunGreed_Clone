#include "pch.h"
#include "CDungeon_NifleHeim.h"
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
#include "CNifleHeim.h"
#include "CPortal.h"
#include "CRSPMgr.h"
CDungeon_NifleHeim::CDungeon_NifleHeim()
{
}

CDungeon_NifleHeim::~CDungeon_NifleHeim()
{
}

void CDungeon_NifleHeim::Initialize()
{
	//아직 클리어 안한 씬에서만 몹 생성
	if (!m_bIsClearScene)
	{
		//GET(CObjMgr)->AddObject(OBJ_MONSTER, CAbstractFactory<CGiantBat>::Create(700.f, 500.f));
		GET(CObjMgr)->AddObject(OBJ_MONSTER, CAbstractFactory<CNifleHeim>::Create(1250.f, 550.f));
		//GET(CObjMgr)->AddObject(OBJ_MONSTER, CAbstractFactory<CBanshee>::Create(800.f, 500.f));
		//GET(CObjMgr)->AddObject(OBJ_MONSTER, CAbstractFactory<CBat>::Create(1200.f, 500.f));
		//GET(CObjMgr)->AddObject(OBJ_MONSTER, CAbstractFactory<CLittleGhost>::Create(1200.f, 200.f));
		//GET(CObjMgr)->AddObject(OBJ_MONSTER, CAbstractFactory<CBigWhiteSkel>::Create(800.f, 200.f));
		//GET(CObjMgr)->AddObject(OBJ_NPC, CAbstractFactory<CTresure>::Create(800, 500.f));

	}
	CSnow* pSnow = new CSnow;
	pSnow->Initialize();
	GET(CObjMgr)->AddObject(OBJ_EFFECT, pSnow);
	switch (GET(CSceneMgr)->GetPreSceneID())
	{
	case SCENE_ICE_DUNGEON_01:
		GET(CObjMgr)->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(200.f, 865.f));
		break;
	default:
		GET(CObjMgr)->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(200.f, 865.f));
		break;
	}
	GET(CPlayerMgr)->Initialize();

	GET(CObjMgr)->Initialize();
	GET(CLineMgr)->Initialize();
	GET(CTileMgr)->Initialize();
	GET(CTileMgr)->Load_Tile(L"NifleHeimScene");

	GET(CUIMgr)->Insert_UI(L"PlayerUI", new CPlayerUI(GET(CPlayerMgr)->GetPlayer()));
	GET(CUIMgr)->Insert_UI(L"InventoryUI", new CInventoryUI(GET(CPlayerMgr)->GetPlayer()));
	GET(CUIMgr)->Initialize();

	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Background/BGLayer_0.bmp", L"BGLayer_0");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Background/Snow.bmp", L"Snow");

	// Camera 지정
	GET(CCamera)->Initialize();
	GET(CCamera)->SetTarget(GET(CObjMgr)->GetObjLayer(OBJ_PLAYER).front());

	//---------------------------------문 설치---------------------------------------
	CObj* pDoor = CAbstractFactory<CDoor>::Create(100.f, 865.f);
	dynamic_cast<CDoor*>(pDoor)->SetNextSceneName(L"IceDungeon01");
	GET(CObjMgr)->AddObject(OBJ_DOOR, pDoor);
	//---------------------------------문 설치---------------------------------------

	//GET(CSoundMgr)->PlayBGM(L"JailField.wav", 1.f);
	GET(CSoundMgr)->StopSound(SOUND_BGM);

	GET(CRSPMgr)->Initialize();
	GET(CUIMgr)->Find_UI(L"RSP")->Close();
	GET(CUIMgr)->Find_UI(L"PlayerSelectUI")->Close();
}

void CDungeon_NifleHeim::Update()
{
	m_bIsClearScene = GET(CObjMgr)->GetObjLayer(OBJ_MONSTER).empty();
	OpenDoor();
	GET(CRSPMgr)->Update();
}

void CDungeon_NifleHeim::Late_Update()
{
	DoorToNextScene();
	if (!GET(CObjMgr)->GetObjLayer(OBJ_MONSTER).empty())
	{
		// 하드코딩...
		CNifleHeim* NifleHeim = dynamic_cast<CNifleHeim*>(GET(CObjMgr)->GetObjLayer(OBJ_MONSTER).front());
		if (NifleHeim->GetPortal() != nullptr && dynamic_cast<CPortal*>(NifleHeim->GetPortal())->EnterPortal())
		{
			GET(CSceneMgr)->ChangeScene(L"Ending");
		}
	}

	GET(CRSPMgr)->Late_Update();
}

void CDungeon_NifleHeim::Render(HDC hDC)
{
	int scrollX = GET(CCamera)->Get_ScrollX();
	int scrollY = GET(CCamera)->Get_ScrollY();
	Rectangle(hDC, 0, 0, WINCX, WINCY);

	HDC hBackDC = GET(CResourceMgr)->Find_Bmp(L"BGLayer_0");
	GdiTransparentBlt(
		hDC,
		0,
		0,
		1920,
		1080,
		hBackDC,
		0,
		0,
		320,
		260,
		RGB(255, 0, 255)
	);
}

void CDungeon_NifleHeim::Release()
{
	GET(CObjMgr)->DeleteAllLayer();
	GET(CTileMgr)->Clear_Tile();
	GET(CUIMgr)->Release();
	GET(CRSPMgr)->Release();
	//GET(CSoundMgr)->StopAll();
}
