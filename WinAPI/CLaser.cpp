#include "pch.h"
#include "CLaser.h"
#include "CPlayer.h"

CLaser::CLaser() : m_pOwner(nullptr), m_pTarget(nullptr)
, isActive(false), isAttack(false), isRight(true)
{
}

CLaser::CLaser(CEnemy* pHand, bool isR) : m_pTarget(nullptr)
, isActive(false), isAttack(false), m_fDamage(0.f)
{
	m_pOwner = pHand;
	isRight = isR;
}

CLaser::~CLaser()
{
	Release();
}

void CLaser::Initialize()
{
	m_tInfo.fCX = 1000.f;
	m_tInfo.fCY = 147.f;
	__super::Update_Rect();

	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/Belial/LaserHeadL.bmp", L"LaserHeadL");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/Belial/LaserHeadR.bmp", L"LaserHeadR");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/Belial/LaserBody.bmp", L"LaserBody");


	m_tFrame.iStart = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.iEnd = 5;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();
	m_iFrameWidth = 567 / 7;
	m_iFrameHeight = 132;

	m_fDamage = 10.f;
	m_iMaxAttackCount = 1;
	m_iCurAttackCount = 0;
	m_dwDelay = GetTickCount();
}

int CLaser::Update()
{
	if (!isActive)
		return 0;

	if(isRight)
		m_tInfo.fX = m_pOwner->Get_Info()->fX - m_tInfo.fCX * 0.5f;
	else
		m_tInfo.fX = m_pOwner->Get_Info()->fX + m_tInfo.fCX * 0.5f;

	float offsetY = 20.f;
	m_tInfo.fY = m_pOwner->Get_Info()->fY + offsetY;

	//패턴시작(isActive = true)되고나서 1초뒤에 발사
	if (isAttack == false && (m_dwDelay + 1000) < GetTickCount())
	{
		isAttack = true;
		m_dwDelay = GetTickCount();
	}

	Shoot();

	__super::Update_Rect();
	return 0;
}

void CLaser::Late_Update()
{
	if (isActive && isAttack)
	{
		Move_Frame_No_Loop();
	}

	RECT rt;
	if (!GET(CObjMgr)->GetObjLayer(OBJ_PLAYER).empty())
	{
		CObj* pPlayer = GET(CObjMgr)->GetObjLayer(OBJ_PLAYER).front();
		if (m_iMaxAttackCount > m_iCurAttackCount && IntersectRect(&rt, &m_tRect, GET(CObjMgr)->GetObjLayer(OBJ_PLAYER).front()->Get_Rect()))
		{
			if (isAttack)
			{
				dynamic_cast<CPlayer*>(pPlayer)->OnDamage(m_fDamage);
				m_iCurAttackCount++;
			}
		}
	}
}

void CLaser::Render(HDC hDC)
{
	if (!isActive)
		return;
	if (!isAttack)
		return;


	int ScrollX = GET(CCamera)->Get_ScrollX();
	int ScrollY = GET(CCamera)->Get_ScrollY();

	if (isRight)
	{
		HDC hMemDC = GET(CResourceMgr)->Find_Bmp(L"LaserHeadR");
		GdiTransparentBlt(
			hDC,
			m_tRect.right - m_iFrameWidth - ScrollX,
			m_tRect.top - ScrollY,
			m_iFrameWidth,
			m_iFrameHeight,
			hMemDC,
			m_iFrameWidth * m_tFrame.iStart,
			0,
			m_iFrameWidth,
			m_iFrameHeight,
			RGB(255, 0, 255)
		);

		int cnt = (m_tRect.right - m_iFrameWidth) / m_iFrameWidth;
		float offsetY = 6.f;
		m_tFrame.iEnd = 7;
		for (int i = 2; i < 15; ++i)
		{
			HDC hBodyDC = GET(CResourceMgr)->Find_Bmp(L"LaserBody");
			GdiTransparentBlt(
				hDC,
				m_tRect.right - m_iFrameWidth * i - ScrollX,
				m_tRect.top - ScrollY - offsetY,
				m_iFrameWidth,
				m_iFrameHeight,
				hBodyDC,
				m_iFrameWidth * m_tFrame.iStart,
				0,
				m_iFrameWidth,
				m_iFrameHeight,
				RGB(255, 0, 255)
			);
		}
	}
	else
	{
		HDC hMemDC = GET(CResourceMgr)->Find_Bmp(L"LaserHeadL");
		GdiTransparentBlt(
			hDC,
			m_tRect.left - ScrollX,
			m_tRect.top - ScrollY,
			m_iFrameWidth,
			m_iFrameHeight,
			hMemDC,
			m_iFrameWidth * m_tFrame.iStart,
			0,
			m_iFrameWidth,
			m_iFrameHeight,
			RGB(255, 0, 255)
		);

		int cnt = (m_tRect.right - m_iFrameWidth) / m_iFrameWidth;
		float offsetY = 6.f;
		m_tFrame.iEnd = 7;
		for (int i = 1; i < 15; ++i)
		{
			HDC hBodyDC = GET(CResourceMgr)->Find_Bmp(L"LaserBody");
			GdiTransparentBlt(
				hDC,
				m_tRect.left + m_iFrameWidth * i - ScrollX,
				m_tRect.top - ScrollY - offsetY,
				m_iFrameWidth,
				m_iFrameHeight,
				hBodyDC,
				m_iFrameWidth * m_tFrame.iStart,
				0,
				m_iFrameWidth,
				m_iFrameHeight,
				RGB(255, 0, 255)
			);
		}
	}
}

void CLaser::Release()
{
}

void CLaser::Motion_Change()
{
}

void CLaser::Shoot()
{
	if (isAttack)
	{
		
	}
}
