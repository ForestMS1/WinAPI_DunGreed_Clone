#include "pch.h"
#include "CBelial.h"
#include "CBelialBullet.h"

CBelial::CBelial() : m_pRHand(nullptr), m_pLHand(nullptr), m_dwRotateAttackTick(GetTickCount())
, m_pSpearMgr(nullptr)
{
}

CBelial::~CBelial()
{
	Release();
}

void CBelial::Initialize()
{
	m_fMaxHp = 100.f;
	m_fCurHp = m_fMaxHp;

	m_tInfo.fX = 1700.f;
	m_tInfo.fY = 400.f;
	m_tInfo.fCX = 210.f;
	m_tInfo.fCY = 285.f;

	//플레이어 감지 범위
	m_fDetectfCX = 700.f;
	m_fDetectfCY = 700.f;

	m_tFrame.iStart = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.iEnd = 9;
	m_tFrame.dwSpeed = 100.f;
	m_iFrameWidth = 210.f;
	m_iFrameHeight = 285.f;
	m_tFrame.dwTime = GetTickCount();
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/Belial/SkellBossIdle.bmp", L"BelialIdle");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/Belial/SkellBossAttack.bmp", L"BelialAttack");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/Belial/SkellBossBack.bmp", L"SkellBossBack");

	srand(time(0));
	m_dwChangePattern = GetTickCount();

	m_eCurState = IDLE;
	m_wsFrameKey = L"BelialIdle";

	//손 생성
	if (m_pRHand == nullptr)
	{
		m_pRHand = new CBelialRHand(this);
		m_pRHand->Initialize();
	}
	if (m_pLHand == nullptr)
	{
		m_pLHand = new CBelialLHand(this);
		m_pLHand->Initialize();
	}

	//창
	if (m_pSpearMgr == nullptr)
	{
		m_pSpearMgr = new SpearMgr(this);
		m_pSpearMgr->Initialize();
	}
}

int CBelial::Update()
{
	if (m_fCurHp <= 0.f)
	{
		m_bIsDead = true;
		m_eCurState = DEAD;

		// 리턴하기전에 딜레이 줘야할듯?
		
		//return OBJ_NOEVENT;
		return OBJ_DEAD;
	}
	__super::Update_Rect();
	Update_DetectRect();
	Attack_Rotate();

	if(m_eCurState != DEAD)
		Move_Frame();

	if (m_bIsInPlayer)
		m_eCurState = ATTACK_SPEAR;
	else
		m_eCurState = ATTACK_HAND;


	if (m_pRHand != nullptr)
		m_pRHand->Update();
	if (m_pLHand != nullptr)
		m_pLHand->Update();
	if (m_pSpearMgr != nullptr)
		m_pSpearMgr->Update();

	return OBJ_NOEVENT;
}

void CBelial::Late_Update()
{
	Motion_Change();

	if (m_pRHand != nullptr)
		m_pRHand->Late_Update();
	if (m_pLHand != nullptr)
		m_pLHand->Late_Update();
	if (m_pSpearMgr != nullptr)
		m_pSpearMgr->Late_Update();
}

void CBelial::Render(HDC hDC)
{
	int ScrollX = (int)GET(CCamera)->Get_ScrollX();
	int ScrollY = (int)GET(CCamera)->Get_ScrollY();
	if (g_bDebugMod)
	{
		Rectangle(hDC, m_tRect.left - ScrollX, m_tRect.top - ScrollY, m_tRect.right - ScrollX, m_tRect.bottom - ScrollY);

		HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
		hPen = (HPEN)SelectObject(hDC, hPen);
		MoveToEx(hDC, m_tDetectRect.left - ScrollX, m_tDetectRect.top - ScrollY, nullptr);
		LineTo(hDC, m_tDetectRect.right - ScrollX, m_tDetectRect.top - ScrollY);
		LineTo(hDC, m_tDetectRect.right - ScrollX, m_tDetectRect.bottom - ScrollY);
		LineTo(hDC, m_tDetectRect.left - ScrollX, m_tDetectRect.bottom - ScrollY);
		LineTo(hDC, m_tDetectRect.left - ScrollX, m_tDetectRect.top - ScrollY);
		hPen = (HPEN)SelectObject(hDC, hPen);
		DeleteObject(hPen);
	}

	HDC hMemDC = GET(CResourceMgr)->Find_Bmp(m_wsFrameKey);

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

	if (m_pRHand != nullptr)
		m_pRHand->Render(hDC);
	if (m_pLHand != nullptr)
		m_pLHand->Render(hDC);
	if (m_pSpearMgr != nullptr)
		m_pSpearMgr->Render(hDC);
}

void CBelial::Release()
{
	Safe_Delete(m_pRHand);
	Safe_Delete(m_pLHand);
	Safe_Delete(m_pSpearMgr);
}

void CBelial::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case BELIAL_STATE::IDLE:
			m_tFrame.iStart = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.iEnd = 9;
			m_wsFrameKey = L"BelialIdle";
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount();
			m_iFrameWidth = 210.f;
			m_iFrameHeight = 285.f;
			m_tInfo.fCX = m_iFrameWidth;
			m_tInfo.fCY = m_iFrameHeight;
			break;

		case BELIAL_STATE::ATTACK_ROTATE:
			m_tFrame.iStart = 2;
			m_tFrame.iEnd = 9;
			m_tFrame.dwSpeed = 500;
			m_tFrame.dwTime = GetTickCount();
			m_wsFrameKey = L"BelialAttack";
			m_iFrameWidth = 210.f;
			m_iFrameHeight = 384.f;
			m_tInfo.fCX = m_iFrameWidth;
			m_tInfo.fCY = m_iFrameHeight;
			break;
		case BELIAL_STATE::DEAD:
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

void CBelial::Attack_Rotate()
{
	static float RightAngle = 0.f;
	static float ToptAngle = 90.f;
	static float LefttAngle = 180.f;
	static float DownAngle = 270.f;
	if (m_eCurState == ATTACK_ROTATE && m_tFrame.iStart <= m_tFrame.iEnd)
	{
		if (m_dwRotateAttackTick + 100 < GetTickCount())
		{
			float offsetX = 20.f;
			float offsetY = 100.f;
			GET(CObjMgr)->AddObject(OBJ_ENEMY_BULLET, CAbstractFactory<CBelialBullet>::CreateBullet(m_tInfo.fX+offsetX, m_tInfo.fY+offsetY, RightAngle));
			GET(CObjMgr)->AddObject(OBJ_ENEMY_BULLET, CAbstractFactory<CBelialBullet>::CreateBullet(m_tInfo.fX+offsetX, m_tInfo.fY+offsetY, ToptAngle));
			GET(CObjMgr)->AddObject(OBJ_ENEMY_BULLET, CAbstractFactory<CBelialBullet>::CreateBullet(m_tInfo.fX+offsetX, m_tInfo.fY+offsetY, LefttAngle));
			GET(CObjMgr)->AddObject(OBJ_ENEMY_BULLET, CAbstractFactory<CBelialBullet>::CreateBullet(m_tInfo.fX+offsetX, m_tInfo.fY+offsetY, DownAngle));
			RightAngle +=	5.f;
			ToptAngle  +=	5.f;
			LefttAngle +=	5.f;
			DownAngle  +=	5.f;
			m_dwRotateAttackTick = GetTickCount();

		}
	}
	else
	{
		m_eCurState = IDLE;
	}
}
