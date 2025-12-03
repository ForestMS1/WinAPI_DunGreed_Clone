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
	m_tInfo.fCX = 39.f;
	m_tInfo.fCY = 39.f;

	m_fSpeed = 5.f;
	m_fDamage = 10.f;

	m_iFrameWidth = 39.f;
	m_iFrameHeight = 39.f;

	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 1;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100.f;
	m_tFrame.dwTime = GetTickCount();

	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/Belial/BossBullet.bmp", L"BossBullet");
	m_wsFrameKey = L"BossBullet";
}

int CBelialBullet::Update()
{
	CBullet::Update();
	m_tInfo.fX += m_fSpeed * cosf(m_fAngle * PI /180.f);
	m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * PI / 180.f);
	if (m_bIsDead)
		return OBJ_DEAD;
	return 0;
}

void CBelialBullet::Late_Update()
{
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
