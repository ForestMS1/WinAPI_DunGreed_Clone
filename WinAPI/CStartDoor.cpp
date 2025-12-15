#include "pch.h"
#include "CStartDoor.h"

CStartDoor::CStartDoor() : m_bPlaySound(false), m_bIsOpen(false)
{
	m_eRender = GAMEOBJECT;
}

CStartDoor::~CStartDoor()
{
}

void CStartDoor::Initialize()
{
	m_iFrameWidth = 57;
	m_iFrameHeight = 65;
	m_tInfo.fCX = m_iFrameWidth * 4;
	m_tInfo.fCY = m_iFrameHeight * 4;
	__super::Update_Rect();

	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 9;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();
	m_wsFrameKey = L"StartDoor";
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Dungeon/Door/StartDoor.bmp", L"StartDoor");
}

int CStartDoor::Update()
{
	if (!m_bIsOpen)
	{
		Move_Frame_No_Loop();
		if (m_tFrame.iStart >= m_tFrame.iEnd)
			m_tFrame.iStart = m_tFrame.iEnd;

		if (!m_bPlaySound)
		{
			GET(CSoundMgr)->PlaySoundW(L"Jail_Metal_Door_Sound_Effect.wav", SOUND_EFFECT, 1.f);
			m_bPlaySound = true;
		}
	}
	return 0;
}

void CStartDoor::Late_Update()
{
}

void CStartDoor::Render(HDC hDC)
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
		m_tFrame.iStart * m_iFrameWidth,
		m_tFrame.iMotion * m_iFrameHeight,
		m_iFrameWidth,
		m_iFrameHeight,
		RGB(255,0,255)
		);
}

void CStartDoor::Release()
{
}
