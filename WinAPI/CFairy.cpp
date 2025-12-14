#include "pch.h"
#include "CFairy.h"
#include "CPlayer.h"

CFairy::CFairy() : m_fSpeed(2.5f), m_bIsGot(false)
{
}

CFairy::CFairy(int reHp, float fX, float fY) : m_fSpeed(5.f), m_bIsGot(false)
{
	m_iReHp = reHp;
	m_tInfo.fX = fX;
	m_tInfo.fY = fY;

	m_fBurstAngle = (float)(rand() % 360);
	m_fBurstSpeed = (float)(rand() % 3 + 10);
	m_dwBurstEnd = GetTickCount() + 300;

}

CFairy::~CFairy()
{
}

void CFairy::Initialize()
{
	m_iFrameWidth = 27;
	m_iFrameHeight = 33;
	m_tInfo.fCX = m_iFrameWidth;
	m_tInfo.fCY = m_iFrameHeight;

	//플레이어 감지 범위
	m_fDetectfCX = m_tInfo.fCX * 2;
	m_fDetectfCY = m_tInfo.fCY * 2;

	m_tFrame.iStart = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.iEnd = 15;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();

	__super::Update_Rect();

	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Object/FairyS.bmp", L"FairyS");
	m_wsFrameKey = L"FairyS";
}

int CFairy::Update()
{
	if (m_bIsGot)
		return OBJ_DEAD;

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

void CFairy::Late_Update()
{
	CItem::Late_Update();
	if (m_bIsInPlayer)
	{
		CObj* pPlayer = GET(CPlayerMgr)->GetPlayer();
		if (CCollisionMgr::Check_Rect(pPlayer, this))
		{
			//dynamic_cast<CPlayer*>(pPlayer)->GetDropGold(m_iGold);
			dynamic_cast<CPlayer*>(pPlayer)->RestoreHp(m_iReHp);
			m_bIsGot = true;
		}
	}
}

void CFairy::Render(HDC hDC)
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

void CFairy::Release()
{
}

CItem* CFairy::Clone()
{
	CFairy* pFairy = new CFairy(*this);
	return pFairy;
}
