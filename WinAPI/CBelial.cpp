#include "pch.h"
#include "CBelial.h"

CBelial::CBelial()
{
}

CBelial::~CBelial()
{
}

void CBelial::Initialize()
{
	m_fMaxHp = 500.f;
	m_fCurHp = m_fMaxHp;

	m_tInfo.fX = 2500.f;
	m_tInfo.fY = 200.f;
	m_tInfo.fCX = 210.f;
	m_tInfo.fCY = 285.f;

	m_tFrame.iStart = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.iEnd = 9;
	m_tFrame.dwSpeed = 100.f;
	m_iFrameWidth = 210.f;
	m_iFrameHeight = 285.f;
	m_tFrame.dwTime = GetTickCount();
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/Belial/SkellBossIdle.bmp", L"BelialIdle");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/Belial/SkellBossAttack.bmp", L"BelialAttack");
	
	m_eCurState = IDLE;
	m_wsFrameKey = L"BelialIdle";
}

int CBelial::Update()
{
	__super::Update_Rect();

	if(m_eCurState != DEAD)
		Move_Frame();
	return 0;
}

void CBelial::Late_Update()
{
	Motion_Change();
}

void CBelial::Render(HDC hDC)
{
	HDC hMemDC = GET(CResourceMgr)->Find_Bmp(m_wsFrameKey);
	int ScrollX = (int)GET(CCamera)->Get_ScrollX();
	int ScrollY = (int)GET(CCamera)->Get_ScrollY();
	GdiTransparentBlt(
		hDC,
		m_tRect.left - ScrollX,
		m_tRect.top - ScrollY,
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

void CBelial::Release()
{
}

void CBelial::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iStart = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.iEnd = 9;
			m_wsFrameKey = L"BelialIdle";
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount();
			m_iFrameWidth = 210.f;
			m_iFrameHeight = 285.f;
			break;

		case ATTACK_ROTATE:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 9;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			m_wsFrameKey = L"BelialAttack";
			m_iFrameWidth = 210.f;
			m_iFrameHeight = 384.f;
			m_tInfo.fCX = m_iFrameWidth;
			m_tInfo.fCY = m_iFrameHeight;
			break;
		case DEAD:
			m_tFrame.iStart = 3;
			m_tFrame.iEnd = 3;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			m_wsFrameKey = L"BelialAttack";
			m_iFrameWidth = 210.f;
			m_iFrameHeight = 384.f;
			m_tInfo.fCX = m_iFrameWidth;
			m_tInfo.fCY = m_iFrameHeight;
			break;
		default:
			m_tFrame.iStart = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.iEnd = 9;
			m_wsFrameKey = L"BelialIdle";
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount();
			m_iFrameWidth = 210.f;
			m_iFrameHeight = 285.f;
			break;
		}
		m_ePreState = m_eCurState;
	}

}
