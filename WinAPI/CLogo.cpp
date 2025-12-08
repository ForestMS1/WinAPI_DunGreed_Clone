#include "pch.h"
#include "CLogo.h"
#include "CObjMgr.h"
#include "CPlayer.h"
#include "CGoTileEditBtn.h"
#include "CGameStartBtn.h"
#include "CResourceMgr.h"

CLogo::CLogo() : m_pGoTileBtn(nullptr), m_pGameStartBtn(nullptr)
{
}

CLogo::~CLogo()
{
	Release();
}

void CLogo::Initialize()
{
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/Logo.bmp", L"Logo");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/Bird.bmp", L"Bird");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/BackGround/Sky.bmp", L"Sky");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/BackGround/Cloud2.bmp", L"Cloud2");

	if (m_pGoTileBtn == nullptr)
	{
		m_pGoTileBtn = new CGoTileEditBtn;
		m_pGoTileBtn->Initialize();
	}
	if (m_pGameStartBtn == nullptr)
	{
		m_pGameStartBtn = new CGameStartBtn;
		m_pGameStartBtn->Initialize();
	}
	GET(CSoundMgr)->PlayBGM(L"Title.wav", 1.f);
}

void CLogo::Update()
{
	CObjMgr::Get_Instance()->Update();
}

void CLogo::Late_Update()
{
	CObjMgr::Get_Instance()->Late_Update();
	if (m_pGoTileBtn != nullptr)
		m_pGoTileBtn->Late_Update();
	if (m_pGameStartBtn != nullptr)
		m_pGameStartBtn->Late_Update();

	//юс╫ц
	if (GET(CKeyMgr)->Key_Down('Z'))
	{
		GET(CSceneMgr)->ChangeScene(L"Belial");
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
	CObjMgr::Get_Instance()->DeleteLayerObj(OBJ_PLAYER);
	GET(CSoundMgr)->StopAll();
	Safe_Delete(m_pGoTileBtn);
	Safe_Delete(m_pGameStartBtn);
}
