#include "pch.h"
#include "CNPC_Inn.h"
#include "CShopUI.h"
CNPC_Inn::CNPC_Inn()
{
}

CNPC_Inn::~CNPC_Inn()
{
	Release();
}

void CNPC_Inn::Initialize()
{
	CNPC::Initialize();

	m_tFrame.iStart = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.iEnd = 5;
	m_tFrame.dwSpeed = 100.f;
	m_iFrameWidth = 15;
	m_iFrameHeight = 23;
	m_tInfo.fCX = m_iFrameWidth * 2;
	m_tInfo.fCY = m_iFrameHeight * 2;
	m_wsFrameKey = L"NPC_Inn";
	m_tFrame.dwTime = GetTickCount();

	//플레이어 감지 범위
	m_fDetectfCX = m_tInfo.fCX * 1.3;
	m_fDetectfCY = m_tInfo.fCY;

	__super::Update_Rect();

	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/NPC/NPC_Inn.bmp", L"NPC_Inn");

	//GET(CUIMgr)->Insert_UI(L"ShopUI", new CShopUI);
}

int CNPC_Inn::Update()
{
	CNPC::Update();

	__super::Update_Rect();
	Update_DetectRect();

	Move_Frame();
	KeyInput();

	return OBJ_NOEVENT;
}

void CNPC_Inn::Late_Update()
{
	CNPC::Late_Update();
}

void CNPC_Inn::Render(HDC hDC)
{
	CNPC::Render(hDC);
	int scrollX = GET(CCamera)->Get_ScrollX();
	int scrollY = GET(CCamera)->Get_ScrollY();

	HDC hMemDC = GET(CResourceMgr)->Find_Bmp(m_wsFrameKey);
	GdiTransparentBlt(
		hDC,
		m_tRect.left - scrollX,
		m_tRect.top - scrollY,
		m_tInfo.fCX,
		m_tInfo.fCY,
		hMemDC,
		m_iFrameWidth * m_tFrame.iStart,
		m_iFrameHeight * m_tFrame.iMotion,
		m_iFrameWidth,
		m_iFrameHeight,
		RGB(255, 0, 255)
	);
}

void CNPC_Inn::Release()
{

}

void CNPC_Inn::KeyInput()
{
	if (m_bIsInPlayer)
	{
		if (GET(CKeyMgr)->Key_Down('F'))
		{
			if (!GET(CUIMgr)->Find_UI(L"ShopUI")->IsOpen())
			{
				GET(CUIMgr)->Find_UI(L"ShopUI")->Open();
				GET(CUIMgr)->Find_UI(L"InventoryUI")->Open();
			}
			else if (GET(CUIMgr)->Find_UI(L"ShopUI")->IsOpen())
			{
				GET(CUIMgr)->Find_UI(L"ShopUI")->Close();
				GET(CUIMgr)->Find_UI(L"InventoryUI")->Close();
			}
		}
	}
	else if (GET(CUIMgr)->Find_UI(L"ShopUI")->IsOpen())
	{
		GET(CUIMgr)->Find_UI(L"ShopUI")->Close();
		GET(CUIMgr)->Find_UI(L"InventoryUI")->Close();
	}
}
