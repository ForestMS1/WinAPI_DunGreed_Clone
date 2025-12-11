#include "pch.h"
#include "CDoor.h"

CDoor::CDoor() : m_bIsPlaySound(false)
{
	m_eRender = GAMEOBJECT;
}

CDoor::~CDoor()
{
	Release();
}

void CDoor::Initialize()
{
	m_iFrameWidth = 58;
	m_iFrameHeight = 192;
	m_tInfo.fCX = m_iFrameWidth;
	m_tInfo.fCY = m_iFrameHeight;
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 22;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100.f;
	m_tFrame.dwTime = GetTickCount();
	m_wsFrameKey = L"Door_Left";
	__super::Update_Rect();
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Dungeon/Door/Door.bmp", L"Door");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Dungeon/Door/Door_Left.bmp", L"Door_Left");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Dungeon/Door/Door_Right.bmp", L"Door_Right");

	m_ePreState = END;
	m_eCurState = CLOSE_LEFT;
}

int CDoor::Update()
{
	__super::Update_Rect();
	if (m_eCurState == IDLE_LEFT || m_eCurState == IDLE_BOTTOM || m_eCurState == IDLE_RIGHT)
	{
		Move_Frame(9);
		m_bIsPlaySound = false;
	}
	if(m_eCurState == CLOSE_LEFT || m_eCurState == OPEN_LEFT
		|| m_eCurState == CLOSE_BOTTOM || m_eCurState == OPEN_BOTTOM
		|| m_eCurState == CLOSE_RIGHT || m_eCurState == OPEN_RIGHT)
	{
		Move_Frame_No_Loop();
		if (!m_bIsPlaySound)
		{
			GET(CSoundMgr)->PlaySoundW(L"Door_move.wav", SOUND_EFFECT, 1.f);
			m_bIsPlaySound = true;
		}
		if (m_tFrame.iStart >= m_tFrame.iEnd)
		{
			if (m_eCurState == CLOSE_LEFT)
				m_eCurState = IDLE_LEFT;
			else if (m_eCurState == CLOSE_BOTTOM)
				m_eCurState = IDLE_BOTTOM;
			else if (m_eCurState == CLOSE_RIGHT)
				m_eCurState = IDLE_RIGHT;
		}
	}
	return 0;
}

void CDoor::Late_Update()
{
	Motion_Change();
	if (m_eCurState == IDLE_LEFT || m_eCurState == IDLE_BOTTOM || m_eCurState == IDLE_RIGHT)
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
		case CLOSE_LEFT:
			m_iFrameWidth = 58;
			m_iFrameHeight = 192;
			m_tInfo.fCX = m_iFrameWidth;
			m_tInfo.fCY = m_iFrameHeight;
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 8;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount();
			m_wsFrameKey = L"Door_Left";
			break;
		case IDLE_LEFT:
			m_iFrameWidth = 58;
			m_iFrameHeight = 192;
			m_tInfo.fCX = m_iFrameWidth;
			m_tInfo.fCY = m_iFrameHeight;
			m_tFrame.iStart = 8;
			m_tFrame.iEnd = 15;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount();
			m_wsFrameKey = L"Door_Left";
			break;
		case OPEN_LEFT:
			m_iFrameWidth = 58;
			m_iFrameHeight = 192;
			m_tInfo.fCX = m_iFrameWidth;
			m_tInfo.fCY = m_iFrameHeight;
			m_tFrame.iStart = 15;
			m_tFrame.iEnd = 22;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount();
			m_wsFrameKey = L"Door_Left";
			break;
		case CLOSE_BOTTOM:
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
		case IDLE_BOTTOM:
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
		case OPEN_BOTTOM:
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
		case CLOSE_RIGHT:
			m_iFrameWidth = 58;
			m_iFrameHeight = 192;
			m_tInfo.fCX = m_iFrameWidth;
			m_tInfo.fCY = m_iFrameHeight;
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 8;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount();
			m_wsFrameKey = L"Door_Right";
			break;
		case IDLE_RIGHT:
			m_iFrameWidth = 58;
			m_iFrameHeight = 192;
			m_tInfo.fCX = m_iFrameWidth;
			m_tInfo.fCY = m_iFrameHeight;
			m_tFrame.iStart = 8;
			m_tFrame.iEnd = 15;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount();
			m_wsFrameKey = L"Door_Right";
			break;
		case OPEN_RIGHT:
			m_iFrameWidth = 58;
			m_iFrameHeight = 192;
			m_tInfo.fCX = m_iFrameWidth;
			m_tInfo.fCY = m_iFrameHeight;
			m_tFrame.iStart = 15;
			m_tFrame.iEnd = 22;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount();
			m_wsFrameKey = L"Door_Right";
			break;
		default:
			break;
		}

		m_ePreState = m_eCurState;
	}
}