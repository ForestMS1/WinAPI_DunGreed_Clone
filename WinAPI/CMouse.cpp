#include "pch.h"
#include "CMouse.h"
#include "CResourceMgr.h"
#include "CKeyMgr.h"
#include "CCamera.h"
CMouse* CMouse::m_pInstance = nullptr;

CMouse::CMouse() : m_iOption(0), m_pItem(nullptr)
{
	ZeroMemory(&m_tInfo, sizeof(INFO));
	ZeroMemory(&m_tRect, sizeof(RECT));
}
CMouse::~CMouse()
{
	Release();
}

void CMouse::Initialize()
{
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;

	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/Cursor/BasicCursor.bmp", L"BasicCursor");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/Cursor/ShootingCursor.bmp", L"ShootingCursor");
	ShowCursor(false);
	m_eState = EMPTY;
}
void CMouse::Update()
{
	GetCursorPos(&m_ptInfo);
	ScreenToClient(g_hWnd, &m_ptInfo);

	m_tInfo.fX = (float)m_ptInfo.x;
	m_tInfo.fY = (float)m_ptInfo.y;

	m_tRect.left = m_tInfo.fX - m_tInfo.fCX * 0.5f;
	m_tRect.top = m_tInfo.fY - m_tInfo.fCY * 0.5f;
	m_tRect.right = m_tInfo.fX + m_tInfo.fCX * 0.5f;
	m_tRect.bottom = m_tInfo.fY + m_tInfo.fCY * 0.5f;
}
void CMouse::Late_Update()
{
#ifdef _DEBUG
	if (GET(CKeyMgr)->Key_Pressing(VK_RETURN))
	{
		Vec2 rp = GET(CCamera)->GetRealPos(Vec2(m_tInfo.fX, m_tInfo.fY));
		Vec2 renderPos = GET(CCamera)->GetRenderPos(Vec2(m_tInfo.fX, m_tInfo.fY));
		cout << "마우스 실제 위치 : " << rp.fX << "\t" << rp.fY << endl;
		cout << "마우스 렌더 위치 : " << renderPos.fX << "\t" << renderPos.fY << endl;
	}
#endif // _DEBUG

	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;

	if (GET(CSceneMgr)->GetCurSceneID() == SCENE_LOGO || GET(CSceneMgr)->GetCurSceneID() == SCENE_MAPTOOL)
	{
		m_tInfo.fCX = 27.f;
		m_tInfo.fCY = 33.f;
	}
}
void CMouse::Render(HDC hDC)
{

#pragma region 기본마우스커서이미지

	if (GET(CSceneMgr)->GetCurSceneID() == SCENE_LOGO || GET(CSceneMgr)->GetCurSceneID() == SCENE_MAPTOOL)
	{
		HDC hBasicDC = GET(CResourceMgr)->Find_Bmp(L"BasicCursor");

		GdiTransparentBlt(
			hDC,
			m_tInfo.fX,
			m_tInfo.fY,
			m_tInfo.fCX,
			m_tInfo.fCY,
			hBasicDC,
			0,
			0,
			27,
			33,
			RGB(255, 0, 255)
		);
	}
	else
	{
		HDC hMemDC = GET(CResourceMgr)->Find_Bmp(L"ShootingCursor");

		GdiTransparentBlt(
			hDC,
			m_tRect.left,
			m_tRect.top,
			m_tInfo.fCX,
			m_tInfo.fCY,
			hMemDC,
			0,
			0,
			63,
			63,
			RGB(255, 0, 255)
		);
	}

#pragma endregion

#pragma region 인벤토리아이템집기

	if (m_pItem != nullptr)
	{
		POINT mpt = GET(CMouse)->Get_Point();
		HDC hMouseDC = GET(CResourceMgr)->Find_Bmp(m_pItem->Get_FrameKey());

		GdiTransparentBlt(
			hDC,
			mpt.x - m_tInfo.fCX * 0.5f,
			mpt.y - m_tInfo.fCY * 0.5f,
			m_tInfo.fCX,
			m_tInfo.fCY,
			hMouseDC,
			0,
			0,
			m_pItem->Get_FrameWidth(),
			m_pItem->Get_FrameHeight(),
			RGB(255, 0, 255)
		);
	}

#pragma endregion

#pragma region 타일에디터씬

	// 타일에디터 씬 ------------------------------------------------------------------------------------------
	HDC hTileDC = GET(CResourceMgr)->Find_Bmp(L"MapTileOld");
	HDC hMemDC = GET(CResourceMgr)->Find_Bmp(L"MapTileOption");

	if (GET(CUIMgr)->Find_UI(L"MapTileUI") != nullptr && !GET(CUIMgr)->Find_UI(L"MapTileUI")->IsOpen())
	{
		int frameWidth = BMPTILECX;
		int frameHeight = BMPTILECX;

		int SrcX = frameWidth * m_iDrawIDX;
		int SrcY = frameHeight * m_iDrawIDY;


		// 마우스 커서에 선택된 타일 출력
		GdiTransparentBlt(
			hDC,
			m_tInfo.fX - TILECX / 2,				// 복사 받을 공간의 LEFT	
			m_tInfo.fY - TILECY / 2,				// 복사 받을 공간의 TOP
			TILECX,												// 복사 받을 공간의 가로 
			TILECY,												// 복사 받을 공간의 세로 
			hTileDC,														// 복사 할 DC
			SrcX,														// 원본이미지 left
			SrcY,														// 원본이미지 top
			frameWidth,													// 원본이미지 가로
			frameHeight,												// 원본이미지 세로
			RGB(255, 0, 255)
		);
		// 마우스에 옵션값 사각형 이미지 띄우기
		GdiTransparentBlt(
			hDC,
			m_tInfo.fX - TILECX / 2,							// 복사 받을 공간의 LEFT	
			m_tInfo.fY - TILECY / 2,							// 복사 받을 공간의 TOP
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

#pragma endregion
}
void CMouse::Release()
{

}