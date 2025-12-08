#include "pch.h"
#include "CBatBullet.h"

CBatBullet::CBatBullet() :m_ePreState(END), m_eCurState(IDLE)
{
}

CBatBullet::~CBatBullet()
{
	Release();
}

void CBatBullet::Initialize()
{
	m_tInfo.fCX = 42.f;
	m_tInfo.fCY = 42.f;

	m_fSpeed = 5.f;
	m_fDamage = 3.f;

	m_iFrameWidth = 210 / 5;
	m_iFrameHeight = 42.f;

	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 4;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100.f;
	m_tFrame.dwTime = GetTickCount();

	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/Bat/BatBullet.bmp", L"BatBullet");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/Bat/BatBulletHit.bmp", L"BatBulletHit");
	m_wsFrameKey = L"BatBullet";
}

int CBatBullet::Update()
{
	if (m_bIsDead)
	{
		Move_Frame_No_Loop();
		m_eCurState = DEAD;
		if(m_tFrame.iStart >= m_tFrame.iEnd)
			return OBJ_DEAD;
	}
	else
	{
		CBullet::Update();
		m_tInfo.fX += m_fSpeed * cosf(m_fAngle * PI / 180.f);
		m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * PI / 180.f);
	}
	return 0;
}

void CBatBullet::Late_Update()
{
	Motion_Change();
}

void CBatBullet::Render(HDC hDC)
{
	CBullet::Render(hDC);
	HDC hMemDC = GET(CResourceMgr)->Find_Bmp(m_wsFrameKey);
	int ScrollX = GET(CCamera)->Get_ScrollX();
	int ScrollY = GET(CCamera)->Get_ScrollY();
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

void CBatBullet::Release()
{
}

void CBatBullet::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tInfo.fCX = 42.f;
			m_tInfo.fCY = 42.f;
			m_iFrameWidth = 210 / 5;
			m_iFrameHeight = 42.f;
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 4;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount();
			m_wsFrameKey = L"BatBullet";
			break;
		case DEAD:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 6;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount();
			m_iFrameWidth = 546 / 7;
			m_iFrameHeight = 78.f;
			m_tInfo.fCX = m_iFrameWidth;
			m_tInfo.fCY = m_iFrameHeight;
			m_wsFrameKey = L"BatBulletHit";
			break;
		default:
			break;
		}

		m_ePreState = m_eCurState;
	}
}
