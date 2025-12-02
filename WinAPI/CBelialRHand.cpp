#include "pch.h"
#include "CBelialRHand.h"
#include "CBelial.h"

CBelialRHand::CBelialRHand() : m_pOwner(nullptr)
{
}

CBelialRHand::CBelialRHand(CEnemy* pBelial)
{
	m_pOwner = pBelial;
}

CBelialRHand::~CBelialRHand()
{
	Release();
}

void CBelialRHand::Initialize()
{
	float offsetX = 320.f;
	float offsetY = 100.f;
	m_tInfo.fX = m_pOwner->Get_Info()->fX + offsetX;
	m_tInfo.fY = m_pOwner->Get_Info()->fY + offsetY;
	m_tInfo.fCX = 171.f;
	m_tInfo.fCY = 378 * 0.5f;

	m_tFrame.iStart = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.iEnd = 9;
	m_tFrame.dwSpeed = 50.f;
	m_iFrameWidth = 171.f;
	m_iFrameHeight = 378.f * 0.5f;
	m_tFrame.dwTime = GetTickCount();
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/Belial/SkellBossHandIdle.bmp", L"HandIdle");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/Belial/SkellBossHandAttack.bmp", L"HandAttack");
	m_wsFrameKey = L"HandIdle";
}

int CBelialRHand::Update()
{
	__super::Update_Rect();
	if(m_eCurState != BELIAL_STATE::DEAD)
		Move_Frame();
	return 0;
}

void CBelialRHand::Late_Update()
{
	m_eCurState = dynamic_cast<CBelial*>(m_pOwner)->GetCurState();
	Motion_Change();
}

void CBelialRHand::Render(HDC hDC)
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

void CBelialRHand::Release()
{
}

void CBelialRHand::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case BELIAL_STATE::IDLE:
			m_tFrame.iStart = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.iEnd = 9;
			m_wsFrameKey = L"HandIdle";
			m_tFrame.dwSpeed = 50.f;
			m_iFrameWidth = 171.f;
			m_iFrameHeight = 378.f * 0.5f;
			m_tFrame.dwTime = GetTickCount();
			break;

		case BELIAL_STATE::ATTACK_ROTATE:
			m_tFrame.iStart = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.iEnd = 9;
			m_wsFrameKey = L"HandIdle";
			m_tFrame.dwSpeed = 50.f;
			m_iFrameWidth = 171.f;
			m_iFrameHeight = 378.f * 0.5f;
			m_tInfo.fCX = m_iFrameWidth;
			m_tInfo.fCY = m_iFrameHeight;
			m_tFrame.dwTime = GetTickCount();
			break;
		case BELIAL_STATE::ATTACK_HAND:
			m_tFrame.iStart = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.iEnd = 9;
			m_wsFrameKey = L"HandAttack";
			m_tFrame.dwSpeed = 50.f;
			m_iFrameWidth = 195.f;
			m_iFrameHeight = 426.f * 0.5f;
			m_tInfo.fCX = m_iFrameWidth;
			m_tInfo.fCY = m_iFrameHeight;
			m_tFrame.dwTime = GetTickCount();
			break;
		case BELIAL_STATE::DEAD:
			m_tFrame.iStart = 9;
			m_tFrame.iMotion = 0;
			m_tFrame.iEnd = 9;
			m_wsFrameKey = L"HandAttack";
			m_tFrame.dwSpeed = 50.f;
			m_iFrameWidth = 195.f;
			m_iFrameHeight = 426.f * 0.5f;
			m_tInfo.fCX = m_iFrameWidth;
			m_tInfo.fCY = m_iFrameHeight;
			m_tFrame.dwTime = GetTickCount();
			break;
		default:
			m_tFrame.iStart = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.iEnd = 9;
			m_wsFrameKey = L"HandIdle";
			m_tFrame.dwSpeed = 50.f;
			m_iFrameWidth = 171.f;
			m_iFrameHeight = 378.f * 0.5f;
			m_tFrame.dwTime = GetTickCount();
			m_tInfo.fCX = m_iFrameWidth;
			m_tInfo.fCY = m_iFrameHeight;
			break;
		}
		m_ePreState = m_eCurState;
	}
}
