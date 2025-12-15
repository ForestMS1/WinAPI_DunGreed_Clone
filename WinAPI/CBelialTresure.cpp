#include "pch.h"
#include "CBelialTresure.h"
#include "CFairy.h"
#include "CBelial.h"
#include "CCosSword.h"
CBelialTresure::CBelialTresure() : m_bIsClear(false), m_bOpen(false), m_bCompleteDropGold(false)
{
}

CBelialTresure::~CBelialTresure()
{
	Release();
}

void CBelialTresure::Initialize()
{
	CNPC::Initialize();

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

	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/EnemySpawn.bmp", L"EnemySpawn");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Dungeon/Tresure/BossTresure.bmp", L"BossTresure");

	//플레이어 감지 범위
	m_fDetectfCX = m_tInfo.fCX * 1.3;
	m_fDetectfCY = m_tInfo.fCY;

	__super::Update_Rect();
	m_ePreState = SPAWN;
	m_eCurState = SPAWN;
}

int CBelialTresure::Update()
{
	if (!GET(CObjMgr)->GetObjLayer(OBJ_MONSTER).empty())
	{
		if (dynamic_cast<CBelial*>(GET(CObjMgr)->GetObjLayer(OBJ_MONSTER).front()) != nullptr)
		{
			m_bIsClear = GET(CObjMgr)->GetObjLayer(OBJ_MONSTER).front()->IsDead();
		}
	}
	//m_bIsClear = GET(CObjMgr)->GetObjLayer(OBJ_MONSTER).empty();

	if (!m_bIsClear)
		return 0;


	m_tInfo.fY += GRAVITY;

	CNPC::Update();

	__super::Update_Rect();
	Update_DetectRect();

	SpawnEffect();

	KeyInput();

	if (m_bOpen && !m_bCompleteDropGold)
	{
		Move_Frame_No_Loop();
		//TODO : 아이템드랍
		CItem* pCosSword = new CCosSword(m_tInfo.fX, m_tInfo.fY);
		pCosSword->SetDrop(true);
		pCosSword->Initialize();
		GET(CObjMgr)->AddObject(OBJ_ITEM, pCosSword);
		m_bCompleteDropGold = true;
		GET(CSoundMgr)->PlaySoundW(L"open_tresure.wav", SOUND_EFFECT, 1.f);
	}


	return OBJ_NOEVENT;
}

void CBelialTresure::Late_Update()
{
	if (!m_bIsClear)
		return;
	CNPC::Late_Update();
	Motion_Change();
	float py(0.f);
	GET(CLineMgr)->Collision_Line(this, &py);
	CCollisionMgr::Collision_RectTile(this, GET(CTileMgr)->GetVecTile());
}

void CBelialTresure::Render(HDC hDC)
{
	if (!m_bIsClear)
		return;

	CNPC::Render(hDC);
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
		m_iFrameHeight * m_tFrame.iMotion,
		m_iFrameWidth,
		m_iFrameHeight,
		RGB(255, 0, 255)
	);
}

void CBelialTresure::Release()
{

}

void CBelialTresure::KeyInput()
{
	if (m_bIsInPlayer)
	{
		if (GET(CKeyMgr)->Key_Down('F'))
		{
			m_bOpen = true;
		}
	}
}

void CBelialTresure::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case SPAWN:
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
			break;
		case IDLE:
			m_tFrame.iStart = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.iEnd = 1;
			m_tFrame.dwSpeed = 100.f;
			m_iFrameWidth = 129;
			m_iFrameHeight = 90;
			m_tInfo.fCX = m_iFrameWidth;
			m_tInfo.fCY = m_iFrameHeight;
			m_wsFrameKey = L"BossTresure";
			m_tFrame.dwTime = GetTickCount();
			break;
		default:
			break;
		}
		m_ePreState = m_eCurState;
	}

}

void CBelialTresure::SpawnEffect()
{
	if (m_eCurState == SPAWN)
		Move_Frame_No_Loop();

	if (!m_bIsSpawnSound)
	{
		GET(CSoundMgr)->PlaySoundW(L"SpawnMonster.wav", SOUND_EFFECT, 1.f);
		m_bIsSpawnSound = true;
	}
	if (m_tFrame.iStart >= m_tFrame.iEnd)
		m_eCurState = IDLE;
}