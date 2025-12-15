#include "pch.h"
#include "CGiantRedBat.h"
#include "CBatBullet.h"
CGiantRedBat::CGiantRedBat() : m_fBulletSpawnAngle(0.f), m_fBulletShootAngle(0.f)
{
}

CGiantRedBat::~CGiantRedBat()
{
	Release();
}

void CGiantRedBat::Initialize()
{
	CEnemy::Initialize();

	m_fMaxHp = 200.f;
	m_fCurHp = m_fMaxHp;

	//플레이어 감지 범위
	m_fDetectfCX = 700.f;
	m_fDetectfCY = 700.f;

	m_tFrame.iStart = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.iEnd = 14;
	m_tFrame.dwSpeed = 100.f;
	m_iFrameWidth = 124;
	m_iFrameHeight = 124;
	m_tInfo.fCX = m_iFrameWidth;
	m_tInfo.fCY = m_iFrameHeight;
	m_wsFrameKey = L"EnemySpawn";
	m_tFrame.dwTime = GetTickCount();

	__super::Update_Rect();

	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/Bat/RedGiantBat.bmp", L"RedGiantBat");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/Bat/RedGiantBatAttack.bmp", L"RedGiantBatAttack");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/EnemySpawn.bmp", L"EnemySpawn");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/EnemyDie_small.bmp", L"EnemyDie_small");


	m_dwAttackTick = GetTickCount();

	m_eCurState = SPAWN;
	m_wsFrameKey = L"EnemySpawn";
	m_iDropGold = 250;
}

int CGiantRedBat::Update()
{
	CEnemy::Update();

	__super::Update_Rect();
	Update_DetectRect();

	if (m_eCurState == SPAWN)
	{
		SpawnEffect();
		return 0;
	}

	if (m_fCurHp <= 0.f)
	{
		m_bIsDead = true;
		m_eCurState = DEAD;
		DeadEffect();
		if (m_tFrame.iStart >= m_tFrame.iEnd)
		{
			for (auto& pBullet : GET(CObjMgr)->GetObjLayer(OBJ_ENEMY_BULLET))
			{
				//GET(CObjMgr)->AddObject(OBJ_ENEMY_BULLET, pBullet);
				if (dynamic_cast<CBatBullet*>(pBullet) != nullptr)
					dynamic_cast<CBatBullet*>(pBullet)->SetMove();
			}
			return OBJ_DEAD;
		}
		else
			return 0;
	}

	Move_Frame();

	if (GET(CPlayerMgr)->GetPlayer()->Get_Info()->fX < m_tInfo.fX)
		m_tFrame.iMotion = 1;
	else
		m_tFrame.iMotion = 0;

	CEnemy::ToPlayerAngle();
	Attack_CircleBullet();


	if (m_bIsHit && m_dwLastHitTime + 10 < GetTickCount())
	{
		m_bIsHit = false;
	}

	return OBJ_NOEVENT;
}

void CGiantRedBat::Late_Update()
{
	CEnemy::Late_Update();
	Motion_Change();
}

void CGiantRedBat::Render(HDC hDC)
{
	CEnemy::Render(hDC);

	if (!m_bIsHit)
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
			m_iFrameWidth,
			m_iFrameHeight,
			hMemDC,
			m_iFrameWidth * m_tFrame.iStart,
			m_iFrameHeight * m_tFrame.iMotion,
			m_iFrameWidth,
			m_iFrameHeight,
			RGB(255, 0, 255)
		);
	}
}

void CGiantRedBat::Release()
{

}

void CGiantRedBat::Motion_Change()
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
			m_tFrame.iEnd = 6;
			m_tFrame.dwSpeed = 100.f;
			m_iFrameWidth = 177.f;
			m_iFrameHeight = 105.f;
			m_tInfo.fCX = m_iFrameWidth;
			m_tInfo.fCY = m_iFrameHeight;
			m_wsFrameKey = L"RedGiantBat";
			m_tFrame.dwTime = GetTickCount();
			break;

		case ATTACK:
			m_tFrame.iStart = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.iEnd = 9;
			m_tFrame.dwSpeed = 100.f;
			m_iFrameWidth = 177.f;
			m_iFrameHeight = 117.f;
			m_tInfo.fCX = m_iFrameWidth;
			m_tInfo.fCY = m_iFrameHeight;
			m_wsFrameKey = L"RedGiantBatAttack";
			m_tFrame.dwTime = GetTickCount();
			m_fBulletShootAngle = m_fAngle;
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

void CGiantRedBat::Attack_CircleBullet()
{
	if (m_bIsInPlayer)
	{
		if (!m_bPlaySound)
		{
			GET(CSoundMgr)->PlaySoundW(L"Bat.wav", SOUND_ENEMY_ATTACK, 1.f);
			m_bPlaySound = true;
		}
		CEnemy::ToPlayerAngle();

		//TODO : 5초에 한번씩 플레이어에게 원 총알 발사
		if (m_iShootCount < 3)
		{
			if (m_dwAttackTick + 100 < GetTickCount())
			{
				GET(CObjMgr)->AddObject(OBJ_ENEMY_BULLET,
					CAbstractFactory<CBatBullet>::CreateBullet(m_tInfo.fX, m_tInfo.fY, (m_fAngle * 180.f / PI) - 20));
				GET(CObjMgr)->AddObject(OBJ_ENEMY_BULLET,
					CAbstractFactory<CBatBullet>::CreateBullet(m_tInfo.fX, m_tInfo.fY, (m_fAngle * 180.f / PI)));
				GET(CObjMgr)->AddObject(OBJ_ENEMY_BULLET,
					CAbstractFactory<CBatBullet>::CreateBullet(m_tInfo.fX, m_tInfo.fY, (m_fAngle * 180.f / PI) + 20));
				m_dwAttackTick = GetTickCount();
				m_iShootCount++;
			}
		}
	}
	else
	{
		m_bPlaySound = false;
		m_iShootCount = 0;
	}
}
