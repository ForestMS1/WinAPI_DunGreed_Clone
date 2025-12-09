#include "pch.h"
#include "CBansheeBullet.h"

CBansheeBullet::CBansheeBullet() :m_ePreState(END), m_eCurState(IDLE)
{
}

CBansheeBullet::~CBansheeBullet()
{
	Release();
}

void CBansheeBullet::Initialize()
{

	m_fSpeed = 5.f;
	m_fDamage = 3.f;

	m_iFrameWidth = 13;
	m_iFrameHeight = 16.f;
	m_tInfo.fCX = m_iFrameWidth * 3;
	m_tInfo.fCY = m_iFrameHeight * 3;
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 3;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100.f;
	m_tFrame.dwTime = GetTickCount();
	m_wsFrameKey = L"BansheeBullet";

	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/Banshee/BansheeBulletSprite.bmp", L"BansheeBullet");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/Banshee/BansheeBulletBoomSprite.bmp", L"BansheeBulletBoom");

}

int CBansheeBullet::Update()
{
	if (m_bIsDead)
	{
		Move_Frame_No_Loop();
		m_eCurState = DEAD;
		if (m_tFrame.iStart >= m_tFrame.iEnd)
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

void CBansheeBullet::Late_Update()
{
	Motion_Change();
}

void CBansheeBullet::Render(HDC hDC)
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

void CBansheeBullet::Release()
{
}

void CBansheeBullet::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_iFrameWidth = 13;
			m_iFrameHeight = 16.f;
			m_tInfo.fCX = m_iFrameWidth * 3;
			m_tInfo.fCY = m_iFrameHeight * 3;
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount();
			m_wsFrameKey = L"BansheeBullet";
			break;
		case DEAD:
			m_iFrameWidth = 20;
			m_iFrameHeight = 27;
			m_tInfo.fCX = m_iFrameWidth * 3;
			m_tInfo.fCY = m_iFrameHeight * 3;
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 5;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount();
			m_wsFrameKey = L"BansheeBulletBoom";
			break;
		default:
			break;
		}

		m_ePreState = m_eCurState;
	}
}