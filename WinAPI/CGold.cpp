#include "pch.h"
#include "CGold.h"
#include "CPlayer.h"

CGold::CGold() : m_fSpeed(2.5f), m_bIsGot(false)
{
}

CGold::CGold(int gold, float fX, float fY) : m_fSpeed(5.f), m_bIsGot(false)
{
	m_iGold = gold;
	m_tInfo.fX = fX;
	m_tInfo.fY = fY;

	m_fBurstAngle = (float)(rand() % 360);
	m_fBurstSpeed = (float)(rand() % 3 + 10);
	m_dwBurstEnd = GetTickCount() + 300;

}

CGold::~CGold()
{
}

void CGold::Initialize()
{
	m_iFrameWidth = 21;
	m_iFrameHeight = 21;
	m_tInfo.fCX = m_iFrameWidth;
	m_tInfo.fCY = m_iFrameHeight;

	//플레이어 감지 범위
	m_fDetectfCX = m_tInfo.fCX * 4;
	m_fDetectfCY = m_tInfo.fCY * 4;

	m_tFrame.iStart = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.iEnd = 7;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();

	__super::Update_Rect();

	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Item/Gold/Coin.bmp", L"Coin");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Item/Gold/Bullion.bmp", L"Bullion");
	m_wsFrameKey = L"Coin";

	if (m_iGold > 100)
	{
		m_wsFrameKey = L"Bullion";

		m_iFrameWidth = 60;
		m_iFrameHeight = 27;
		m_tInfo.fCX = m_iFrameWidth;
		m_tInfo.fCY = m_iFrameHeight;

		m_tFrame.iStart = 0;
		m_tFrame.iMotion = 0;
		m_tFrame.iEnd = 6;
		m_tFrame.dwSpeed = 100;
		m_tFrame.dwTime = GetTickCount();
	}
}

int CGold::Update()
{
	if (m_bIsGot)
		return OBJ_DEAD;

	if (GetTickCount() < m_dwBurstEnd)
	{
		float fRad = m_fBurstAngle * PI / 180.f;
		m_tInfo.fX += m_fBurstSpeed * cosf(fRad);
		m_tInfo.fY -= m_fBurstSpeed * sinf(fRad);
	}

	CItem::Update();


	ToPlayerAngle();

	if (m_bIsInPlayer)
	{
		m_tInfo.fX += m_fSpeed * cosf(m_fAngle);
		m_tInfo.fX -= m_fSpeed * sinf(m_fAngle);
	}

	__super::Update_Rect();
	Move_Frame();
	return 0;
}

void CGold::Late_Update()
{
	CItem::Late_Update();
	if (m_bIsInPlayer)
	{
		CObj* pPlayer = GET(CPlayerMgr)->GetPlayer();
		if (CCollisionMgr::Check_Rect(pPlayer, this))
		{
			dynamic_cast<CPlayer*>(pPlayer)->GetDropGold(m_iGold);
			m_bIsGot = true;
		}
	}
}

void CGold::Render(HDC hDC)
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
		m_iFrameHeight * 0,
		m_iFrameWidth,
		m_iFrameHeight,
		RGB(255, 0, 255)
	);
}

void CGold::Release()
{
}

CItem* CGold::Clone()
{
	CGold* pGold = new CGold(*this);
	return pGold;
}
