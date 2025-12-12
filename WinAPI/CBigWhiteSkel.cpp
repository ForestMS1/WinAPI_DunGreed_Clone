#include "pch.h"
#include "CBat.h"
#include "CBigWhiteSkel.h"
#include "CPlayer.h"
CBigWhiteSkel::CBigWhiteSkel() : m_bJump(false)
, m_ft(0.f), m_v0(0.f), m_fAcct(0.3f), m_iAttack(5)
{
}

CBigWhiteSkel::~CBigWhiteSkel()
{
	Release();
}

void CBigWhiteSkel::Initialize()
{
	CEnemy::Initialize();

	m_fMaxHp = 300.f;
	m_fCurHp = m_fMaxHp;

	m_fSpeed = 4.f;

	//플레이어 감지 범위
	m_fDetectfCX = 700;
	m_fDetectfCY = 700;

	m_tFrame.iStart = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.iEnd = 14;
	m_tFrame.dwSpeed = 100.f;
	m_iFrameWidth = 124;
	m_iFrameHeight = 124;
	m_tInfo.fCX = m_iFrameWidth;
	m_tInfo.fCY = m_iFrameHeight;
	//m_fDetectfCX = m_tInfo.fCX;
	//m_fDetectfCY = m_tInfo.fCY;
	m_wsFrameKey = L"EnemySpawn";
	m_tFrame.dwTime = GetTickCount();

	__super::Update_Rect();

	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/BigSkel/BigWhiteSkelIdle.bmp", L"BigWhiteSkelIdle");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/BigSkel/BigWhiteSkelMove.bmp", L"BigWhiteSkelMove");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/BigSkel/BigWhiteSkelAttack.bmp", L"BigWhiteSkelAttack");


	m_dwAttackDelay = GetTickCount();

	m_eCurState = SPAWN;
	m_wsFrameKey = L"EnemySpawn";
	srand(time(0));
	m_iDropGold = 200 + (rand() % 10);
}

int CBigWhiteSkel::Update()
{
	CEnemy::Update();

	if(!m_bJump)
		m_tInfo.fY += GRAVITY;

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
			return OBJ_DEAD;
		else
			return 0;
	}

	if (m_bIsInPlayer && m_eCurState != ATTACK)
	{
		CEnemy::ToPlayerAngle();
		m_eCurState = MOVE;
		if (fabsf(GET(CPlayerMgr)->GetPlayer()->Get_Pos().fX - m_tInfo.fX) > 50)
			m_tInfo.fX += m_fSpeed * cosf(m_fAngle); //* 180.f / PI);
		//m_tInfo.fY -= m_fSpeed * sinf(m_fAngle); //* 180.f / PI);
	}



	if (GET(CPlayerMgr)->GetPlayer()->Get_Info()->fX < m_tInfo.fX)
		m_tFrame.iMotion = 1;
	else
		m_tFrame.iMotion = 0;


	Move_Frame();

	if (m_bIsHit && m_dwLastHitTime + 10 < GetTickCount())
	{
		m_bIsHit = false;
	}

	return OBJ_NOEVENT;
}

void CBigWhiteSkel::Late_Update()
{
	CEnemy::Late_Update();

	if (CCollisionMgr::Check_Rect(this, GET(CPlayerMgr)->GetPlayer()))
	{
		//if (m_dwAttackDelay + 1000 < GetTickCount())
		//{
			m_eCurState = ATTACK;
			//m_dwAttackDelay = GetTickCount();
			if (m_eCurState == ATTACK && ((m_tFrame.iStart == 2 && m_tFrame.iMotion == 0) ||
				(m_tFrame.iStart == 2 && m_tFrame.iMotion == 1)))
			{
				dynamic_cast<CPlayer*>(GET(CPlayerMgr)->GetPlayer())->OnDamage(m_iAttack);
			}
		//}
	}
	else if(m_eCurState == ATTACK && ((m_tFrame.iStart == 11 && m_tFrame.iMotion == 0) ||
		(m_tFrame.iStart == 0 && m_tFrame.iMotion == 1)))
		m_eCurState = IDLE;

	//if (m_eCurState == ATTACK && ((m_tFrame.iStart == 11 && m_tFrame.iMotion == 0) ||
	//	(m_tFrame.iStart == 0 && m_tFrame.iMotion == 1)))
	//{
	//	m_eCurState = IDLE;
	//}

	Motion_Change();
	CCollisionMgr::Collision_RectTile(this, GET(CTileMgr)->GetVecTile());
	float py(0.f);
	GET(CLineMgr)->Collision_Line(this, &py);
}

void CBigWhiteSkel::Render(HDC hDC)
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

		if (m_eCurState == ATTACK && m_tFrame.iMotion == 1)
		{
			GdiTransparentBlt(
				hDC,
				m_tRect.left - ScrollX,
				m_tRect.top - ScrollY,
				m_tInfo.fCX,
				m_tInfo.fCY,
				hMemDC,
				m_iFrameWidth * (11-m_tFrame.iStart),
				m_iFrameHeight * m_tFrame.iMotion,
				m_iFrameWidth,
				m_iFrameHeight,
				RGB(255, 0, 255)
			);
		}
		else
		{
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
	}
}

void CBigWhiteSkel::Release()
{

}

void CBigWhiteSkel::Motion_Change()
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
			m_tInfo.fCX = m_iFrameWidth * 0.5;
			m_tInfo.fCY = m_iFrameHeight * 0.5;
			m_wsFrameKey = L"EnemySpawn";
			m_tFrame.dwTime = GetTickCount();
			break;
		case IDLE:
			m_tFrame.iStart = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.iEnd = 5;
			m_tFrame.dwSpeed = 100.f;
			m_iFrameWidth = 99;
			m_iFrameHeight = 144;
			m_tInfo.fCX = m_iFrameWidth;
			m_tInfo.fCY = m_iFrameHeight;
			m_wsFrameKey = L"BigWhiteSkelIdle";
			m_tFrame.dwTime = GetTickCount();
			break;
		case MOVE:
			m_tFrame.iStart = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.iEnd = 5;
			m_tFrame.dwSpeed = 100.f;
			m_iFrameWidth = 99;
			m_iFrameHeight = 144;
			m_tInfo.fCX = m_iFrameWidth;
			m_tInfo.fCY = m_iFrameHeight;
			m_wsFrameKey = L"BigWhiteSkelMove";
			m_tFrame.dwTime = GetTickCount();
			break;
		case ATTACK:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 11;
			m_tFrame.dwSpeed = 100.f;
			m_iFrameWidth = 183;
			m_iFrameHeight = 144;
			m_tInfo.fCX = m_iFrameWidth;
			m_tInfo.fCY = m_iFrameHeight;
			m_wsFrameKey = L"BigWhiteSkelAttack";
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

void CBigWhiteSkel::Attack_CircleBullet()
{
	if (m_bIsInPlayer)
	{
		CEnemy::ToPlayerAngle();

		//TODO : 5초에 한번씩 플레이어에게 원 총알 발사
		if (m_dwAttackDelay + 500 < GetTickCount())
		{
			//GET(CObjMgr)->AddObject(OBJ_ENEMY_BULLET,
			//	CAbstractFactory<CBatBullet>::CreateBullet(m_tInfo.fX, m_tInfo.fY, m_fAngle * 180.f / PI));
			//m_dwAttackTick = GetTickCount();
		}
	}
}
void CBigWhiteSkel::Jump()
{
	if (m_bJump && m_ft < m_fAcct)
	{
		m_ft += 0.01f;
		if (m_ft >= 0.4f)
			m_tInfo.fY -= -(GRAVITY * 0.5f) * m_ft * m_ft;//m_v0* (m_fDashAcct - m_fDasht) + 2 - (7 * 0.5f) * m_ft * m_ft;
		else
			m_tInfo.fY -= m_v0 * (0.4 - m_ft);
	}
	else
	{
		m_ft = 0.f;
		m_bJump = false;
	}
}