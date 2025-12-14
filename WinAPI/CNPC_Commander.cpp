#include "pch.h"
#include "CNPC_Commander.h"
#include "CAbilityUI.h"
CNPC_Commander::CNPC_Commander()
{
}

CNPC_Commander::~CNPC_Commander()
{
	Release();
}

void CNPC_Commander::Initialize()
{
	CNPC::Initialize();

	m_tFrame.iStart = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.iEnd = 5;
	m_tFrame.dwSpeed = 100.f;
	m_iFrameWidth = 23;
	m_iFrameHeight = 25;
	m_tInfo.fCX = m_iFrameWidth * 3;
	m_tInfo.fCY = m_iFrameHeight * 3;
	m_wsFrameKey = L"NPC_Commander";
	m_tFrame.dwTime = GetTickCount();

	//플레이어 감지 범위
	m_fDetectfCX = m_tInfo.fCX * 1.3;
	m_fDetectfCY = m_tInfo.fCY;

	__super::Update_Rect();

	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/NPC/NPC_Commander.bmp", L"NPC_Commander");

	GET(CUIMgr)->Insert_UI(L"AbilityUI", new CAbilityUI);
}

int CNPC_Commander::Update()
{
	CNPC::Update();

	__super::Update_Rect();
	Update_DetectRect();

	Move_Frame();
	KeyInput();

	return OBJ_NOEVENT;
}

void CNPC_Commander::Late_Update()
{
	CNPC::Late_Update();
}

void CNPC_Commander::Render(HDC hDC)
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

void CNPC_Commander::Release()
{

}

void CNPC_Commander::KeyInput()
{
	if (m_bIsInPlayer)
	{
		if (GET(CKeyMgr)->Key_Down('F'))
		{
			if (!GET(CUIMgr)->Find_UI(L"AbilityUI")->IsOpen())
			{
				GET(CUIMgr)->Find_UI(L"AbilityUI")->Open();
				GET(CUIMgr)->Find_UI(L"PlayerUI")->Close();
			}
			else if (GET(CUIMgr)->Find_UI(L"AbilityUI")->IsOpen())
			{
				GET(CUIMgr)->Find_UI(L"AbilityUI")->Close();
				GET(CUIMgr)->Find_UI(L"PlayerUI")->Open();

			}
		}
	}
	else if (GET(CUIMgr)->Find_UI(L"AbilityUI")->IsOpen())
	{
		GET(CUIMgr)->Find_UI(L"AbilityUI")->Close();
		GET(CUIMgr)->Find_UI(L"PlayerUI")->Open();
	}
}
