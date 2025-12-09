#include "pch.h"
#include "CBelial.h"
#include "CBelialBullet.h"

CBelial::CBelial() : m_pRHand(nullptr), m_pLHand(nullptr), m_dwRotateAttackTick(GetTickCount())
, m_pSpearMgr(nullptr), m_dwHandAttackTick(GetTickCount()), HandAttack(false), m_bPlayBossBGM(false)
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

	m_tInfo.fX = 1400.f;
	m_tInfo.fY = 500.f;
	m_tInfo.fCX = 210.f;
	m_tInfo.fCY = 285.f;

	//플레이어 감지 범위
	m_fDetectfCX = 1700.f;
	m_fDetectfCY = 1700.f;

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
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/Belial/SkellBossIdleHit.bmp", L"SkellIdleHit");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/Belial/SkellBossAttackHit.bmp", L"SkellBossAttackHit");


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

	m_SpawnEffectStartTime = GetTickCount();
}

int CBelial::Update()
{
	if (m_fCurHp <= 0.f)
	{
		m_bIsDead = true;
		m_eCurState = DEAD;

		// 리턴하기전에 딜레이 줘야할듯?
		
		//return OBJ_NOEVENT;
		GET(CSoundMgr)->StopSound(SOUND_BGM);
		return OBJ_DEAD;
	}
	__super::Update_Rect();
	Update_DetectRect();
	Attack_Rotate();
	Attack_Hand();

	if(m_eCurState != DEAD)
		Move_Frame();


	if (m_pRHand != nullptr)
		m_pRHand->Update();
	if (m_pLHand != nullptr)
		m_pLHand->Update();
	if (m_pSpearMgr != nullptr)
		m_pSpearMgr->Update();

	if (m_bIsInPlayer && m_SpawnEffectStartTime < GetTickCount() && GetTickCount() < m_SpawnEffectStartTime + 7000)
	{
		GET(CCamera)->SetTarget(nullptr);
		GET(CCamera)->SetLookAt(Vec2(1400, 500));
		if (!m_bPlayBossBGM)
		{
			GET(CSoundMgr)->PlaySound(L"JailBoss.wav", SOUND_BGM, 1.f);
			//GET(CSoundMgr)->PlaySound(L"2.IceBoss.wav", SOUND_BGM, 1.f);
			m_bPlayBossBGM = true;
		}
		return 0;
	}
	else
	{
		GET(CCamera)->SetTarget(GET(CPlayerMgr)->GetPlayer());
	}

	if (m_SpawnEffectStartTime + 9000 < GetTickCount() && m_dwChangePattern + 7000 < GetTickCount())
	{
		m_ePreState = m_eCurState;
		do
		{
			m_eCurState = BELIAL_STATE((rand() % 3) + 1);
		} while (m_ePreState == m_eCurState);
		m_dwChangePattern = GetTickCount();
	}

	if (m_bIsHit && m_dwLastHitTime + 10 < GetTickCount())
	{
		m_bIsHit = false;
	}

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

	if (m_bIsHit)
	{
		if (m_eCurState == ATTACK_ROTATE)
		{
			HDC hHitDC = GET(CResourceMgr)->Find_Bmp(L"SkellBossAttackHit");

			GdiTransparentBlt(
				hDC,
				m_tRect.left - ScrollX,
				m_tRect.top - ScrollY,
				m_tInfo.fCX,
				m_tInfo.fCY,
				hHitDC,
				m_iFrameWidth * m_tFrame.iStart,
				m_iFrameHeight * m_tFrame.iMotion,
				m_iFrameWidth,
				m_iFrameHeight,
				RGB(255, 0, 255)
			);
		}
		else
		{
			HDC hHitDC = GET(CResourceMgr)->Find_Bmp(L"SkellIdleHit");

			GdiTransparentBlt(
				hDC,
				m_tRect.left - ScrollX,
				m_tRect.top - ScrollY,
				m_tInfo.fCX,
				m_tInfo.fCY,
				hHitDC,
				m_iFrameWidth * m_tFrame.iStart,
				m_iFrameHeight * m_tFrame.iMotion,
				m_iFrameWidth,
				m_iFrameHeight,
				RGB(255, 0, 255)
			);
		}
	}

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
			m_tFrame.iStart = 0;
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
		case BELIAL_STATE::ATTACK_HAND:
			m_tFrame.iStart = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.iEnd = 9;
			m_wsFrameKey = L"BelialIdle";
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount();
			m_iFrameWidth = 210.f;
			m_iFrameHeight = 285.f;
			break;
		case BELIAL_STATE::ATTACK_SPEAR:
			m_tFrame.iStart = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.iEnd = 9;
			m_wsFrameKey = L"BelialIdle";
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount();
			m_iFrameWidth = 210.f;
			m_iFrameHeight = 285.f;
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
			GET(CSoundMgr)->PlaySoundW(L"BelialBullet.wav", SOUND_ENEMY_ATTACK, 1.f);
		}
	}
}

void CBelial::Attack_Hand()
{
	if (m_eCurState == ATTACK_HAND && m_dwHandAttackTick + 2000 < GetTickCount())
	{
		isRightHandOn = !isRightHandOn;
		m_pRHand->SetActive(isRightHandOn);
		m_pLHand->SetActive(!isRightHandOn);
		m_dwHandAttackTick = GetTickCount();
	}
}
