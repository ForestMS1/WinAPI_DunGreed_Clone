#include "pch.h"
#include "CEnemy.h"
#include "CEnemyHpBarUI.h"
#include "CGold.h"
CEnemy::CEnemy() : m_fDetectfCX(0.f), m_fDetectfCY(0.f), m_bIsInPlayer(false), m_fAngle(0.f)
, m_pHpBarUI(nullptr), m_bIsSpawnSound(false), m_iDropGold(0)
{
	ZeroMemory(&m_tDetectRect, sizeof(RECT));
	m_eRender = GAMEOBJECT;
}

CEnemy::~CEnemy()
{
	Release();
}

void CEnemy::Initialize()
{
	if(m_pHpBarUI == nullptr)
		m_pHpBarUI = new CEnemyHpBarUI(this);
	m_pHpBarUI->Initialize();
}

int CEnemy::Update()
{
	if (m_pHpBarUI != nullptr)
		m_pHpBarUI->Update();
	return 0;
}

void CEnemy::Late_Update()
{
	if (m_pHpBarUI != nullptr)
		m_pHpBarUI->Late_Update();
}

void CEnemy::Render(HDC hDC)
{
	if (m_pHpBarUI != nullptr)
		m_pHpBarUI->Render(hDC);
}

void CEnemy::Release()
{
	Safe_Delete(m_pHpBarUI);
}

void CEnemy::ToPlayerAngle()
{
	float	fWidth(0.f), fHeight(0.f), fDiagonal(0.f);

	fWidth = GET(CPlayerMgr)->GetPlayer()->Get_Info()->fX - m_tInfo.fX;
	fHeight = GET(CPlayerMgr)->GetPlayer()->Get_Info()->fY - m_tInfo.fY;

	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	m_fAngle = acosf(fWidth / fDiagonal);
	if (GET(CPlayerMgr)->GetPlayer()->Get_Info()->fY > m_tInfo.fY)
		m_fAngle = 2.f * PI - m_fAngle;
}

void CEnemy::Update_DetectRect()
{
	m_tDetectRect.left = m_tInfo.fX - m_fDetectfCX * 0.5f;
	m_tDetectRect.top = m_tInfo.fY - m_fDetectfCY * 0.5f;
	m_tDetectRect.right = m_tInfo.fX + m_fDetectfCX * 0.5f;
	m_tDetectRect.bottom = m_tInfo.fY + m_fDetectfCY * 0.5f;
}

void CEnemy::SpawnEffect()
{
	Move_Frame_No_Loop();
	if (!m_bIsSpawnSound)
	{
		GET(CSoundMgr)->PlaySoundW(L"SpawnMonster.wav", SOUND_EFFECT, 1.f);
		m_bIsSpawnSound = true;
	}
	if (m_tFrame.iStart >= m_tFrame.iEnd)
		m_eCurState = IDLE;
}

void CEnemy::DeadEffect()
{
	Move_Frame_No_Loop();
	if (m_bIsSpawnSound)
	{
		GET(CSoundMgr)->PlaySoundW(L"MonsterDie.wav", SOUND_EFFECT, 1.f);
		m_bIsSpawnSound = false;
	}
}

void CEnemy::DropGold()
{
	if (m_bIsDead)
	{
		//for (size_t i = 0; i < 5; ++i)
		//{
			CItem* pGold = new CGold(m_iDropGold, m_tInfo.fX, m_tInfo.fY);
			pGold->SetDrop(true);
			pGold->Initialize();
			GET(CObjMgr)->AddObject(OBJ_ITEM, pGold);
		//}
	}
}
