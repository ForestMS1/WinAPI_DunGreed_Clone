#include "pch.h"
#include "CTileEditScene.h"
#include "CResourceMgr.h"
#include "CObjMgr.h"
#include "CAbstractFactory.h"
#include "CTileMgr.h"
#include "CCamera.h"
#include "CKeyMgr.h"
#include "CUIMgr.h"
#include "CMapTileUI.h"

CTileEditScene::CTileEditScene() : m_iDrawIDX(0), m_iDrawIDY(0), m_iOption(1)
{

}

CTileEditScene::~CTileEditScene()
{
	Release();
}

void CTileEditScene::Initialize()
{
	GET(CTileMgr)->Initialize();
	GET(CUIMgr)->Initialize();

	// Camera 지정
	GET(CCamera)->SetLookAt(Vec2(WINCX >> 1, WINCY >> 1));
}

void CTileEditScene::Update()
{
	GetCursorPos(&m_ptMouse);
	ScreenToClient(g_hWnd, &m_ptMouse);

	Key_Input();
	GET(CTileMgr)->Update();
	GET(CUIMgr)->Update();
	GET(CCamera)->Update();

	dynamic_cast<CMapTileUI*>(GET(CUIMgr)->Get_UI(L"MapTileUI"))->Set_TileIdx(m_iDrawIDX, m_iDrawIDY);
}

void CTileEditScene::Late_Update()
{
	GET(CTileMgr)->Late_Update();
	GET(CUIMgr)->Late_Update();
}

void CTileEditScene::Render(HDC hDC)
{
	Rectangle(hDC, 0, 0, WINCX, WINCY);

	GET(CTileMgr)->Render(hDC);
	GET(CUIMgr)->Render(hDC);

#pragma region 마우스커서에_현재_선택된_타일_그리기
	HDC hMemDC = GET(CResourceMgr)->Find_Bmp(L"MapTile");

	int frameWidth = BMPTILECX;
	int frameHeight = BMPTILECX;

	int SrcX = frameWidth * m_iDrawIDX;
	int SrcY = frameHeight * m_iDrawIDY;


	GdiTransparentBlt(
		hDC,
		m_ptMouse.x - TILECX/2,				// 복사 받을 공간의 LEFT	
		m_ptMouse.y - TILECX/2,				// 복사 받을 공간의 TOP
		TILECX,												// 복사 받을 공간의 가로 
		TILECY,												// 복사 받을 공간의 세로 
		hMemDC,														// 복사 할 DC
		SrcX,														// 원본이미지 left
		SrcY,														// 원본이미지 top
		frameWidth,													// 원본이미지 가로
		frameHeight,												// 원본이미지 세로
		RGB(255, 0, 255)
	);
#pragma endregion
}

void CTileEditScene::Release()
{
}

void CTileEditScene::Key_Input()
{
#pragma region 마우스_왼오_클릭_칠하기_지우기
	if (GET(CKeyMgr)->Key_Pressing(VK_LBUTTON))
	{
		POINT	pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x = (int)GET(CCamera)->GetRealPos(pt).fX;
		pt.y = (int)GET(CCamera)->GetRealPos(pt).fY;

		// TODO : MapTile 이미지 에서 클릭한 타일인덱스를 아래 Picking_Tile에 넘겨주면 됨.....
		GET(CTileMgr)->Picking_Tile(pt, m_iDrawIDX, m_iDrawIDY, m_iOption);
	}
	if (GET(CKeyMgr)->Key_Pressing(VK_RBUTTON))
	{
		POINT	pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		pt.x = (int)GET(CCamera)->GetRealPos(pt).fX;
		pt.y = (int)GET(CCamera)->GetRealPos(pt).fY;

		// TODO : MapTile 이미지 에서 클릭한 타일인덱스를 아래 Picking_Tile에 넘겨주면 됨.....
		GET(CTileMgr)->Picking_Tile(pt, m_iDrawIDX, m_iDrawIDY, 0);
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

#pragma region 선택타일바꾸기
	if (GET(CKeyMgr)->Key_Down('W'))
	{
		m_iDrawIDY--;
		if (m_iDrawIDY < 0)
		{
			m_iDrawIDY = 0;
		}
	}
	if (GET(CKeyMgr)->Key_Down('A'))
	{
		m_iDrawIDX--;
		if (m_iDrawIDX < 0)
		{
			m_iDrawIDX = 0;
		}
	}
	if (GET(CKeyMgr)->Key_Down('S'))
	{
		//아래거선택
		m_iDrawIDY++;
		if (m_iDrawIDY > 31)
		{
			m_iDrawIDY = 31;
		}
	}
	if (GET(CKeyMgr)->Key_Down('D'))
	{
		m_iDrawIDX++;
		if (m_iDrawIDX > 31)
		{
			m_iDrawIDX = 31;
		}
	}
#pragma endregion

	if (GET(CKeyMgr)->Key_Down(VK_SPACE))
	{
		CUI* pUI = GET(CUIMgr)->Get_UI(L"MapTileUI");
		if (pUI)
		{
			if (pUI->IsOpen())
				pUI->Close();
			else
				pUI->Open();
		}
	}
}