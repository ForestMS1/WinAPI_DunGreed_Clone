#include "pch.h"
#include "CBanshee.h"
#include "CBansheeBullet.h"
CBanshee::CBanshee()
{
}

CBanshee::~CBanshee()
{
	Release();
}

void CBanshee::Initialize()
{
	CEnemy::Initialize();

	m_fMaxHp = 100.f;
	m_fCurHp = m_fMaxHp;

	//m_tInfo.fX = 700.f;
	//m_tInfo.fY = 400.f;

	//플레이어 감지 범위
	m_fDetectfCX = 700.f;
	m_fDetectfCY = 700.f;

	m_tFrame.iStart = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.iEnd = 5;
	m_tFrame.dwSpeed = 100.f;
	m_iFrameWidth = 60;
	m_iFrameHeight = 66;
	m_tInfo.fCX = m_iFrameWidth;
	m_tInfo.fCY = m_iFrameHeight;
	m_wsFrameKey = L"EnemySpawn";
	m_tFrame.dwTime = GetTickCount();

	__super::Update_Rect();

	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/Banshee/BansheeIdle.bmp", L"BansheeIdle");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/Banshee/BansheeAttack.bmp", L"BansheeAttack");


	m_dwAttackTick = GetTickCount();

	m_eCurState = SPAWN;
	m_wsFrameKey = L"EnemySpawn";
}

int CBanshee::Update()
{
	CEnemy::Update();
	if (m_eCurState == SPAWN)
	{
		SpawnEffect();
		return 0;
	}

	if (m_fCurHp <= 0.f)
	{
		//m_bIsDead = true;
		m_eCurState = DEAD;
		DeadEffect();
		if (m_tFrame.iStart >= m_tFrame.iEnd)
			return OBJ_DEAD;
		else
			return 0;
	}
	__super::Update_Rect();
	Update_DetectRect();

	Attack_CircleBullet();

	Move_Frame();

	if (GET(CPlayerMgr)->GetPlayer()->Get_Info()->fX < m_tInfo.fX)
		m_tFrame.iMotion = 1;
	else
		m_tFrame.iMotion = 0;




	if (m_bIsHit && m_dwLastHitTime + 10 < GetTickCount())
	{
		m_bIsHit = false;
	}

	return OBJ_NOEVENT;
}

void CBanshee::Late_Update()
{
	CEnemy::Late_Update();
	Motion_Change();
}

void CBanshee::Render(HDC hDC)
{
	CEnemy::Render(hDC);
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
		m_iFrameWidth,
		m_iFrameHeight,
		hMemDC,
		m_iFrameWidth * m_tFrame.iStart,
		m_iFrameHeight * m_tFrame.iMotion,
		m_iFrameWidth,
		m_iFrameHeight,
		RGB(255, 0, 255)
	);

	if (m_bIsHit)
	{
		//HDC hHitDC = GET(CResourceMgr)->Find_Bmp(L"SkellIdleHit");

		//GdiTransparentBlt(
		//	hDC,
		//	m_tRect.left - ScrollX,
		//	m_tRect.top - ScrollY,
		//	m_iFrameWidth,
		//	m_iFrameHeight,
		//	hHitDC,
		//	m_iFrameWidth * m_tFrame.iStart,
		//	m_iFrameHeight * m_tFrame.iMotion,
		//	m_iFrameWidth,
		//	m_iFrameHeight,
		//	RGB(255, 0, 255)
		//);
	}
}

void CBanshee::Release()
{

}

void CBanshee::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case SPAWN:
			m_tFrame.iStart = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.iEnd = 14;
			m_tFrame.dwSpeed = 1000.f;
			m_iFrameWidth = 124;
			m_iFrameHeight = 124;
			m_tInfo.fCX = m_iFrameWidth;
			m_tInfo.fCY = m_iFrameHeight;
			m_wsFrameKey = L"EnemySpawn";
			m_tFrame.dwTime = GetTickCount();
			break;
		case IDLE:
			m_tFrame.iStart = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.iEnd = 5;
			m_tFrame.dwSpeed = 100.f;
			m_iFrameWidth = 60;
			m_iFrameHeight = 66;
			m_tInfo.fCX = m_iFrameWidth;
			m_tInfo.fCY = m_iFrameHeight;
			m_wsFrameKey = L"BansheeIdle";
			m_tFrame.dwTime = GetTickCount();
			break;

		case ATTACK:
			m_tFrame.iStart = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.iEnd = 5;
			m_tFrame.dwSpeed = 100.f;
			m_iFrameWidth = 60;
			m_iFrameHeight = 66;
			m_tInfo.fCX = m_iFrameWidth;
			m_tInfo.fCY = m_iFrameHeight;
			m_wsFrameKey = L"BansheeAttack";
			m_tFrame.dwTime = GetTickCount();
			break;
		case DEAD:
			m_tFrame.iStart = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.iEnd = 10;
			m_tFrame.dwSpeed = 100.f;
			m_iFrameWidth = 128;
			m_iFrameHeight = 128;
			m_tInfo.fCX = m_iFrameWidth;
			m_tInfo.fCY = m_iFrameHeight;
			m_wsFrameKey = L"EnemyDie_small";
			m_tFrame.dwTime = GetTickCount();
			break;
		default:
			break;
		}
		m_ePreState = m_eCurState;
	}

}

void CBanshee::Attack_CircleBullet()
{
	static float angle[8] = { 0.f, 45.f, 90.f, 135.f, 180.f, 225.f, 270.f, 315.f };

	if (m_bIsInPlayer)
	{
		CEnemy::ToPlayerAngle();
		m_eCurState = ATTACK;
		//TODO : 5초에 한번씩 플레이어에게 원 총알 발사
		if (m_dwAttackTick + 5000 < GetTickCount())
		{
			for (size_t i = 0; i < 8; ++i)
			{
				GET(CObjMgr)->AddObject(OBJ_ENEMY_BULLET,
					CAbstractFactory<CBansheeBullet>::CreateBullet(m_tInfo.fX, m_tInfo.fY, angle[i]));
			}
			GET(CSoundMgr)->PlaySoundW(L"Banshee_ATK.wav", SOUND_ENEMY_ATTACK, 1.f);
			m_dwAttackTick = GetTickCount();
		}
	}
}