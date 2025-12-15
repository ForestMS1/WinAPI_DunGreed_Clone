#include "pch.h"
#include "CLogo.h"
#include "CObjMgr.h"
#include "CPlayer.h"
#include "CGoTileEditBtn.h"
#include "CGameStartBtn.h"
#include "CResourceMgr.h"
#include "CBird.h"

CLogo::CLogo() : m_pGoTileBtn(nullptr), m_pGameStartBtn(nullptr) //m_dwBirdDelay(GetTickCount())
{
}

CLogo::~CLogo()
{
	Release();
}

void CLogo::Initialize()
{
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/Logo.bmp", L"Logo");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Bird.bmp", L"Bird");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/BackGround/Sky.bmp", L"Sky");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/BackGround/Cloud1_WINCXY.bmp", L"Cloud1");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/BackGround/Cloud2_WINCXY.bmp", L"Cloud2");

	GET(CObjMgr)->AddObject(OBJ_EFFECT, CAbstractFactory<CBird>::Create(-30, (WINCY >> 1)	-  300));
	GET(CObjMgr)->AddObject(OBJ_EFFECT, CAbstractFactory<CBird>::Create(-80, (WINCY >> 1)	-  260));
	GET(CObjMgr)->AddObject(OBJ_EFFECT, CAbstractFactory<CBird>::Create(-130, (WINCY >> 1)	-  220));
	GET(CObjMgr)->AddObject(OBJ_EFFECT, CAbstractFactory<CBird>::Create(-180, (WINCY >> 1)	-  180));
	GET(CObjMgr)->AddObject(OBJ_EFFECT, CAbstractFactory<CBird>::Create(-230, (WINCY >> 1)	-  140));
	GET(CObjMgr)->Initialize();

	if (m_pGoTileBtn == nullptr)
	{
		m_pGoTileBtn = new CGoTileEditBtn;
	}
	m_pGoTileBtn->Initialize();

	if (m_pGameStartBtn == nullptr)
	{
		m_pGameStartBtn = new CGameStartBtn;
	}
	m_pGameStartBtn->Initialize();

	GET(CCamera)->SetTarget(nullptr);
	GET(CCamera)->SetLookAt(Vec2(WINCX >> 1, WINCY >> 1));

	GET(CSoundMgr)->PlayBGM(L"Title.wav", 1.f);
}

void CLogo::Update()
{
	if (m_pGoTileBtn != nullptr)
		m_pGoTileBtn->Update();
	if (m_pGameStartBtn != nullptr)
		m_pGameStartBtn->Update();
}

void CLogo::Late_Update()
{
	if (m_pGoTileBtn != nullptr)
		m_pGoTileBtn->Late_Update();
	if (m_pGameStartBtn != nullptr)
		m_pGameStartBtn->Late_Update();

	//юс╫ц
	if (GET(CKeyMgr)->Key_Down('Z'))
	{
		GET(CSceneMgr)->ChangeScene(L"Dungeon01");
	}
	if (GET(CKeyMgr)->Key_Down('X'))
	{
		GET(CSceneMgr)->ChangeScene(L"NifleHeim");
	}
}

void CLogo::Render(HDC hDC)
{
	HDC hSkyDC = CResourceMgr::Get_Instance()->Find_Bmp(L"Sky");
	GdiTransparentBlt(
		hDC,
		0,
		0,
		WINCX,
		WINCY,
		hSkyDC,
		0,
		0,
		WINCX,
		WINCY,
		RGB(0, 0, 0)
	);

	HDC hCloudDC = CResourceMgr::Get_Instance()->Find_Bmp(L"Cloud1");
	GdiTransparentBlt(
		hDC,
		0,
		0,
		WINCX,
		WINCY,
		hCloudDC,
		0,
		0,
		WINCX,
		WINCY,
		RGB(255, 0, 255)
	);
	HDC hCloud2DC = CResourceMgr::Get_Instance()->Find_Bmp(L"Cloud2");
	GdiTransparentBlt(
		hDC,
		0,
		0,
		WINCX,
		WINCY,
		hCloud2DC,
		0,
		0,
		WINCX,
		WINCY,
		RGB(255, 0, 255)
	);

	HDC hLogoDC = GET(CResourceMgr)->Find_Bmp(L"Logo");
	GdiTransparentBlt(
		hDC,
		(WINCX >> 1) - 234,
		(WINCY >> 1) - 225,
		468,
		225,
		hLogoDC,
		0,
		0,
		468,
		225,
		RGB(255, 0, 255)
	);

	if (m_pGoTileBtn != nullptr)
		m_pGoTileBtn->Render(hDC);
	if (m_pGameStartBtn != nullptr)
		m_pGameStartBtn->Render(hDC);
}

void CLogo::Release()
{
	GET(CObjMgr)->DeleteAllLayer();
	GET(CSoundMgr)->StopAll();
	Safe_Delete(m_pGoTileBtn);
	Safe_Delete(m_pGameStartBtn);
}
