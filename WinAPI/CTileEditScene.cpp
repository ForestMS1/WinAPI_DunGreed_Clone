#include "pch.h"
#include "CTileEditScene.h"
#include "CResourceMgr.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CTileMgr.h"
#include "CCamera.h"
#include "CKeyMgr.h"
#include "CMapTileUI.h"
#include "CTileBtn.h"
#include "CMouse.h"
#include "CMapTileOptionUI.h"
#include "CPlayer.h"
CTileEditScene::CTileEditScene() : m_iDrawIDX(0), m_iDrawIDY(0), m_iOption(1)
, m_pTileSelectUI(nullptr), m_pTileOptionSelectUI(nullptr)
{

}

CTileEditScene::~CTileEditScene()
{
	Release();
}

void CTileEditScene::Initialize()
{
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Town/TownTinyVersion.bmp", L"Town");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Background/SubBG.bmp", L"SubBG");
	GET(CTileMgr)->Initialize();

	// Camera 지정
	GET(CCamera)->SetLookAt(Vec2(WINCX >> 1, WINCY >> 1));
	if(m_pTileSelectUI == nullptr)
		m_pTileSelectUI = new CMapTileUI;
	if (m_pTileOptionSelectUI == nullptr)
		m_pTileOptionSelectUI = new CMapTileOptionUI;
	m_pTileSelectUI->Initialize();
	m_pTileOptionSelectUI->Initialize();

	Vec2 pv = GET(CCamera)->GetRealPos(GET(CMouse)->Get_Point());
	//GET(CObjMgr)->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(50, 50));
}

void CTileEditScene::Update()
{
	GetCursorPos(&m_ptMouse);
	ScreenToClient(g_hWnd, &m_ptMouse);

	Key_Input();
	GET(CTileMgr)->Update();
	GET(CCamera)->Update();
	m_pTileSelectUI->Update();
	m_pTileOptionSelectUI->Update();
}

void CTileEditScene::Late_Update()
{
	GET(CTileMgr)->Late_Update();
	m_pTileSelectUI->Late_Update();
	m_pTileOptionSelectUI->Late_Update();
	m_iDrawIDX = GET(CMouse)->Get_DrawIDX();
	m_iDrawIDY = GET(CMouse)->Get_DrawIDY();
	m_iOption = GET(CMouse)->Get_Option();
}

void CTileEditScene::Render(HDC hDC)
{
	Rectangle(hDC, 0, 0, WINCX, WINCY);

#pragma region 마우스커서에_현재_선택된_타일_그리기
	//HDC hTownDC = GET(CResourceMgr)->Find_Bmp(L"SubBG");
	//GdiTransparentBlt(
	//	hDC,
	//	0,
	//	0,
	//	WINCX,
	//	WINCY,
	//	hTownDC,
	//	0,
	//	0,
	//	320,
	//	180,
	//	0);

	GET(CTileMgr)->Render(hDC);
	GET(CObjMgr)->Render(hDC);

	HDC hMemDC = GET(CResourceMgr)->Find_Bmp(L"MapTileOld");

	int frameWidth = BMPTILECX;
	int frameHeight = BMPTILECX;

	int SrcX = frameWidth * m_iDrawIDX;
	int SrcY = frameHeight * m_iDrawIDY;


	// 마우스 커서에 선택된 타일 출력
	GdiTransparentBlt(
		hDC,
		m_ptMouse.x - TILECX/2,				// 복사 받을 공간의 LEFT	
		m_ptMouse.y - TILECY/2,				// 복사 받을 공간의 TOP
		TILECX,												// 복사 받을 공간의 가로 
		TILECY,												// 복사 받을 공간의 세로 
		hMemDC,														// 복사 할 DC
		SrcX,														// 원본이미지 left
		SrcY,														// 원본이미지 top
		frameWidth,													// 원본이미지 가로
		frameHeight,												// 원본이미지 세로
		RGB(255, 0, 255)
	);

	hMemDC = GET(CResourceMgr)->Find_Bmp(L"MapTileOption");

	if (!m_pTileSelectUI->IsOpen())
	{
		// 마우스에 옵션값 사각형 이미지 띄우기
		GdiTransparentBlt(
			hDC,
			m_ptMouse.x - TILECX / 2,							// 복사 받을 공간의 LEFT	
			m_ptMouse.y - TILECY / 2,							// 복사 받을 공간의 TOP
			TILECX,												// 복사 받을 공간의 가로 
			TILECY,												// 복사 받을 공간의 세로 
			hMemDC,												// 복사 할 DC
			m_iOption * BMPTILECX,								// 원본이미지 left
			0,													// 원본이미지 top
			16,													// 원본이미지 가로
			16,													// 원본이미지 세로
			RGB(255, 0, 255)
		);
	}


	// 하단 옵션 사각형 이미지 띄우기
	//GdiTransparentBlt(
	//	hDC,
	//	0,				// 복사 받을 공간의 LEFT	
	//	WINCY-32,				// 복사 받을 공간의 TOP
	//	256,												// 복사 받을 공간의 가로 
	//	32,												// 복사 받을 공간의 세로 
	//	hMemDC,														// 복사 할 DC
	//	0,														// 원본이미지 left
	//	0,														// 원본이미지 top
	//	128,													// 원본이미지 가로
	//	16,												// 원본이미지 세로
	//	RGB(255, 0, 255)
	//);

	wstring text = L"Tile_Option : " + to_wstring(m_iOption);
	TextOut(hDC, 10, 0, text.c_str(), text.length());
	text = L"Camera_Move : WASD";
	TextOut(hDC, 10, 20, text.c_str(), text.length());
	text = L"Save : Q, Load : R";
	TextOut(hDC, 10, 40, text.c_str(), text.length());
	text = L"Tile_Clear: C";
	TextOut(hDC, 10, 60, text.c_str(), text.length());
	m_pTileSelectUI->Render(hDC);
	m_pTileOptionSelectUI->Render(hDC);

#pragma endregion
}

void CTileEditScene::Release()
{
	Safe_Delete(m_pTileSelectUI);
	Safe_Delete(m_pTileOptionSelectUI);
}

void CTileEditScene::Key_Input()
{
#pragma region 마우스_왼오_클릭_칠하기
	if (GET(CKeyMgr)->Key_Pressing(VK_LBUTTON) && !m_pTileSelectUI->IsOpen()
		&& !dynamic_cast<CMapTileOptionUI*>(m_pTileOptionSelectUI)->IsMouseOn())
	{
		POINT	pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x = (int)GET(CCamera)->GetRealPos(pt).fX;
		pt.y = (int)GET(CCamera)->GetRealPos(pt).fY;

		
		GET(CTileMgr)->Picking_Tile(pt, m_iDrawIDX, m_iDrawIDY, m_iOption);
	}
	// 오른쪽 클릭은 옵션만 지정
	if (GET(CKeyMgr)->Key_Pressing(VK_RBUTTON))
	{
		POINT	pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x = (int)GET(CCamera)->GetRealPos(pt).fX;
		pt.y = (int)GET(CCamera)->GetRealPos(pt).fY;


		GET(CTileMgr)->Picking_Tile(pt, m_iOption);
	}
#pragma endregion

#pragma region 키입력_카메라이동
	if (GET(CKeyMgr)->Key_Pressing(VK_UP))
	{
		GET(CCamera)->Set_ScrollY(-5.f);
	}
	if (GET(CKeyMgr)->Key_Pressing(VK_LEFT))
	{
		GET(CCamera)->Set_ScrollX(-5.f);
	}
	if (GET(CKeyMgr)->Key_Pressing(VK_DOWN))
	{
		GET(CCamera)->Set_ScrollY(5.f);
	}
	if (GET(CKeyMgr)->Key_Pressing(VK_RIGHT))
	{
		GET(CCamera)->Set_ScrollX(5.f);
	}
#pragma endregion
#pragma region Q_W저장불러오기
	if (GET(CKeyMgr)->Key_Pressing('Q'))
	{
		GET(CTileMgr)->Save_Tile();
	}
	if (GET(CKeyMgr)->Key_Pressing('R'))
	{
		GET(CTileMgr)->Load_Tile();
	}
#pragma endregion

	if (GET(CKeyMgr)->Key_Down(VK_SPACE))
	{
		if (m_pTileSelectUI)
		{
			if (m_pTileSelectUI->IsOpen())
				m_pTileSelectUI->Close();
			else
				m_pTileSelectUI->Open();
		}
	}	

	if (GET(CKeyMgr)->Key_Down('Z'))
	{
		Vec2 pv = GET(CCamera)->GetRealPos(GET(CMouse)->Get_Point());
		GET(CObjMgr)->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::Create(pv.fX, pv.fY));
	}

	if (GET(CKeyMgr)->Key_Down(VK_TAB))
	{
		g_bDebugMod = !g_bDebugMod;
	}

	if (GET(CKeyMgr)->Key_Down('C'))
	{
		GET(CTileMgr)->Clear_Tile();
	}

}