#include "pch.h"
#include "CDungeonEat.h"
#include "CPlayer.h"

CDungeonEat::CDungeonEat() : m_bIsCompleteEat(false), m_bIsPlaySoundFirst(false), m_bIsPlaySoundSecond(false)
{
	m_eRender = GAMEOBJECT;
}

CDungeonEat::~CDungeonEat()
{
}

void CDungeonEat::Initialize()
{
	m_iFrameWidth = 351; // 28
	m_iFrameHeight = 255;
	m_tInfo.fCX = m_iFrameWidth;
	m_tInfo.fCY = m_iFrameHeight;

	//플레이어 감지 범위
	m_fDetectfCX = m_tInfo.fCX * 1.3;
	m_fDetectfCY = m_tInfo.fCY;

	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 27;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();
	
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Town/DungeonEat.bmp", L"DungeonEat");

}

int CDungeonEat::Update()
{
	CNPC::Update();
	__super::Update_Rect();
	//Update_DetectRect();
	m_tDetectRect.left = m_tInfo.fX - m_fDetectfCX * 0.5f;
	m_tDetectRect.top = m_tInfo.fY + m_fDetectfCY * 0.5f - 20;
	m_tDetectRect.right = m_tInfo.fX + m_fDetectfCX * 0.5f;
	m_tDetectRect.bottom = m_tInfo.fY + m_fDetectfCY * 0.5f;

	if (m_bIsInPlayer)
	{
		Move_Frame_No_Loop();
		CObj* pPlayer = GET(CPlayerMgr)->GetPlayer();
		if (dynamic_cast<CPlayer*>(pPlayer) != nullptr)
			dynamic_cast<CPlayer*>(pPlayer)->SetNoPlayerKeyInput();

		if (!m_bIsPlaySoundFirst)
		{
			GET(CSoundMgr)->PlaySoundW(L"DungeonEat.wav",SOUND_EFFECT, 1.f);
			m_bIsPlaySoundFirst = true;
		}
		if (m_tFrame.iStart == 10 && !m_bIsPlaySoundSecond)
		{
			GET(CSoundMgr)->PlaySoundW(L"DungeonEat2.wav", SOUND_EFFECT, 1.f);
			m_bIsPlaySoundSecond = true;
		}
	}
	return 0;
}

void CDungeonEat::Late_Update()
{
	CNPC::Late_Update();

	CObj* pPlayer = GET(CPlayerMgr)->GetPlayer();

	// 플레이어렌더x
	if (m_bIsInPlayer == true && m_tFrame.iStart == 9)
	{
		if (dynamic_cast<CPlayer*>(pPlayer) != nullptr)
		{
			dynamic_cast<CPlayer*>(pPlayer)->SetNoPlayerRender();
		}
	}

	//씬 전환
	if (m_bIsInPlayer == true && m_tFrame.iStart >= m_tFrame.iEnd)
		m_bIsCompleteEat = true;

}

void CDungeonEat::Render(HDC hDC)
{
	if (!m_bIsInPlayer)
		return;


	int scrollX = GET(CCamera)->Get_ScrollX();
	int scrollY = GET(CCamera)->Get_ScrollY();
	HDC hMemDC = GET(CResourceMgr)->Find_Bmp(L"DungeonEat");
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

void CDungeonEat::Release()
{
}
