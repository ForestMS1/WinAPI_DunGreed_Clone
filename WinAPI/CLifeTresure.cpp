#include "pch.h"
#include "CLifeTresure.h"
#include "CFairy.h"
CLifeTresure::CLifeTresure() : m_bIsClear(false), m_bOpen(false), m_bCompleteDropGold(false)
{
}

CLifeTresure::~CLifeTresure()
{
	Release();
}

void CLifeTresure::Initialize()
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
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Dungeon/Tresure/BasicTresure.bmp", L"BasicTresure");

	//플레이어 감지 범위
	m_fDetectfCX = m_tInfo.fCX * 1.3;
	m_fDetectfCY = m_tInfo.fCY;

	__super::Update_Rect();
	m_ePreState = SPAWN;
	m_eCurState = SPAWN;
}

int CLifeTresure::Update()
{
	m_bIsClear = GET(CObjMgr)->GetObjLayer(OBJ_MONSTER).empty();

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
		CItem* pFairy = new CFairy(100, m_tInfo.fX, m_tInfo.fY);
		pFairy->SetDrop(true);
		pFairy->Initialize();
		GET(CObjMgr)->AddObject(OBJ_ITEM, pFairy);
		m_bCompleteDropGold = true;
		GET(CSoundMgr)->PlaySoundW(L"open_tresure.wav", SOUND_EFFECT, 1.f);
	}


	return OBJ_NOEVENT;
}

void CLifeTresure::Late_Update()
{
	if (!m_bIsClear)
		return;
	CNPC::Late_Update();
	Motion_Change();
	float py(0.f);
	GET(CLineMgr)->Collision_Line(this, &py);
	CCollisionMgr::Collision_RectTile(this, GET(CTileMgr)->GetVecTile());
}

void CLifeTresure::Render(HDC hDC)
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

void CLifeTresure::Release()
{

}

void CLifeTresure::KeyInput()
{
	if (m_bIsInPlayer)
	{
		if (GET(CKeyMgr)->Key_Down('F'))
		{
			m_bOpen = true;
		}
	}
}

void CLifeTresure::Motion_Change()
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
			m_iFrameWidth = 69;
			m_iFrameHeight = 51;
			m_tInfo.fCX = m_iFrameWidth;
			m_tInfo.fCY = m_iFrameHeight;
			m_wsFrameKey = L"BasicTresure";
			m_tFrame.dwTime = GetTickCount();
			break;
		default:
			break;
		}
		m_ePreState = m_eCurState;
	}

}

void CLifeTresure::SpawnEffect()
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