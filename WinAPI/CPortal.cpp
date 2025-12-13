#include "pch.h"
#include "CPortal.h"
CPortal::CPortal() : GoNextScene(false)
{
}

CPortal::~CPortal()
{
	Release();
}

void CPortal::Initialize()
{
	CNPC::Initialize();

	m_tFrame.iStart = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.iEnd = 7;
	m_tFrame.dwSpeed = 100.f;
	m_iFrameWidth = 69;
	m_iFrameHeight = 84;
	m_tInfo.fCX = m_iFrameWidth * 2;
	m_tInfo.fCY = m_iFrameHeight * 2;
	m_wsFrameKey = L"Portal";
	m_tFrame.dwTime = GetTickCount();

	//플레이어 감지 범위
	m_fDetectfCX = m_tInfo.fCX * 1.3;
	m_fDetectfCY = m_tInfo.fCY;

	__super::Update_Rect();

	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/NifleHeim/Portal.bmp", L"Portal");

}

int CPortal::Update()
{
	CNPC::Update();

	__super::Update_Rect();
	Update_DetectRect();

	Move_Frame();
	KeyInput();

	return OBJ_NOEVENT;
}

void CPortal::Late_Update()
{
	CNPC::Late_Update();
}

void CPortal::Render(HDC hDC)
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

void CPortal::Release()
{

}

void CPortal::KeyInput()
{
	if (m_bIsInPlayer)
	{
		if (GET(CKeyMgr)->Key_Down('F'))
		{
			GoNextScene = true;
		}
	}
}
