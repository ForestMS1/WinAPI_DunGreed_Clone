#include "pch.h"
#include "CDoor.h"

CDoor::CDoor()
{
	m_eRender = GAMEOBJECT;
}

CDoor::~CDoor()
{
	Release();
}

void CDoor::Initialize()
{
	m_iFrameWidth = 192;
	m_iFrameHeight = 58;
	m_tInfo.fCX = m_iFrameWidth;
	m_tInfo.fCY = m_iFrameHeight;
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 22;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100.f;
	m_tFrame.dwTime = GetTickCount();
	m_wsFrameKey = L"Door";
	__super::Update_Rect();
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Dungeon/Door/Door.bmp", L"Door");
}

int CDoor::Update()
{
	if (m_eCurState == IDLE)
		Move_Frame();
	else
	{
		Move_Frame_No_Loop();
		if (m_tFrame.iStart >= m_tFrame.iEnd)
			m_eCurState == IDLE;
	}
	return 0;
}

void CDoor::Late_Update()
{
	Motion_Change();
	if (m_eCurState == IDLE)
		CCollisionMgr::Collision_RectEx(GET(CPlayerMgr)->GetPlayer(), this);
}

void CDoor::Render(HDC hDC)
{
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

void CDoor::Release()
{
}

void CDoor::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case CLOSE:
			m_iFrameWidth = 192;
			m_iFrameHeight = 58;
			m_tInfo.fCX = m_iFrameWidth;
			m_tInfo.fCY = m_iFrameHeight;
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 8;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount();
			m_wsFrameKey = L"Door";
			break;
		case IDLE:
			m_iFrameWidth = 192;
			m_iFrameHeight = 58;
			m_tInfo.fCX = m_iFrameWidth;
			m_tInfo.fCY = m_iFrameHeight;
			m_tFrame.iStart = 8;
			m_tFrame.iEnd = 15;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount();
			m_wsFrameKey = L"Door";
			break;
		case OPEN:
			m_iFrameWidth = 192;
			m_iFrameHeight = 58;
			m_tInfo.fCX = m_iFrameWidth;
			m_tInfo.fCY = m_iFrameHeight;
			m_tFrame.iStart = 15;
			m_tFrame.iEnd = 22;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount();
			m_wsFrameKey = L"Door";
			break;
		default:
			break;
		}

		m_ePreState = m_eCurState;
	}
}