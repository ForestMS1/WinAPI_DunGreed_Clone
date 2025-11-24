#include "pch.h"
#include "CToolScene.h"
#include "CTile.h"
#include "CObjMgr.h"
#include "CCamera.h"
#include "CAbstractFactory.h"
#include "CKeyMgr.h"
#include "CResourceMgr.h"
CToolScene::CToolScene()
{

}
CToolScene::~CToolScene()
{

}

void CToolScene::Initialize()
{
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/MapTool/MapTile.bmp", L"MapTile");

	CreateTile(10, 10);
	GET(CObjMgr)->Initialize();
	GET(CCamera)->SetLookAt(Vec2(WINCX >> 1, WINCY >> 1));
}

void CToolScene::Update()
{
	GetCursorPos(&m_ptMouse);
	ScreenToClient(g_hWnd, &m_ptMouse);
	if (GET(CKeyMgr)->Key_Down(VK_LBUTTON))
	{
		Vec2 vLookAt = GET(CCamera)->GetRealPos(m_ptMouse);
		GET(CCamera)->SetLookAt(vLookAt);
	}
	GET(CObjMgr)->Update();
	GET(CCamera)->Update();
}

void CToolScene::Late_Update()
{
	GET(CObjMgr)->Late_Update();
}

void CToolScene::Render(HDC hDC)
{
	Rectangle(hDC, 0, 0, WINCX, WINCY);
	GET(CObjMgr)->Render(hDC);
}

void CToolScene::Release()
{
	GET(CObjMgr)->DeleteLayerObj(OBJ_TILE);
}
