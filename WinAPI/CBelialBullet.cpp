#include "pch.h"
#include "CBelialBullet.h"

CBelialBullet::CBelialBullet()
{
}

CBelialBullet::~CBelialBullet()
{
	Release();
}

void CBelialBullet::Initialize()
{
	m_fSpeed = 5.f;
	m_fDamage = 3.f;

	m_iFrameWidth = 39;
	m_iFrameHeight = 39;
	m_tInfo.fCX = m_iFrameWidth;
	m_tInfo.fCY = m_iFrameHeight;
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 1;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100.f;
	m_tFrame.dwTime = GetTickCount();
	m_wsFrameKey = L"BossBullet";

	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/Belial/BossBullet.bmp", L"BossBullet");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/Belial/BossBulletEffect.bmp", L"BossBulletEffect");
	m_ePreState = IDLE;
	m_eCurState = IDLE;
}

int CBelialBullet::Update()
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

void CBelialBullet::Late_Update()
{
	Motion_Change();
}

void CBelialBullet::Render(HDC hDC)
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

void CBelialBullet::Release()
{
}

void CBelialBullet::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_iFrameWidth = 39;
			m_iFrameHeight = 39;
			m_tInfo.fCX = m_iFrameWidth;
			m_tInfo.fCY = m_iFrameHeight;
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 1;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount();
			m_wsFrameKey = L"BossBullet";
			break;
		case DEAD:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 7;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount();
			m_iFrameWidth = 312 / 8;
			m_iFrameHeight = 39;
			m_tInfo.fCX = m_iFrameWidth;
			m_tInfo.fCY = m_iFrameHeight;
			m_wsFrameKey = L"BossBulletEffect";
			break;
		default:
			break;
		}

		m_ePreState = m_eCurState;
	}
}
