#include "pch.h"
#include "CBelial.h"
#include "CBelialBullet.h"
#include "CBelialUI.h"

CBelial::CBelial() : m_pRHand(nullptr), m_pLHand(nullptr), m_dwRotateAttackTick(GetTickCount())
, m_pSpearMgr(nullptr), m_dwHandAttackTick(GetTickCount()), HandAttack(false), m_bPlayBossBGM(false)
, m_bIntro(false), m_pHpBarUI(nullptr), m_bAlpha(0)
{
}

CBelial::~CBelial()
{
	Release();
}

void CBelial::Initialize()
{
	m_fMaxHp = 1000.f;
	m_fCurHp = m_fMaxHp;

	m_iDropGold = 125 + rand() % 20;

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
	m_tInfo.fCX = m_iFrameWidth;
	m_tInfo.fCY = m_iFrameHeight;
	m_tFrame.dwTime = GetTickCount();
	GET(CResourceMgr)->Insert_AlphaBmp(L"../Resources/Images/Unit/Enemy/Belial/SkellBossIdle.bmp", L"BelialIdle");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/Belial/SkellBossAttack.bmp", L"BelialAttack");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/Belial/SkellBossBack.bmp", L"SkellBossBack");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/Belial/SkellBossIdleHit.bmp", L"SkellIdleHit");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/Belial/SkellBossAttackHit.bmp", L"SkellBossAttackHit");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/Belial/SkellBossDead.bmp", L"SkellBossDead");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/BossIntro.bmp", L"BossIntro");


	srand(time(0));
	m_dwChangePattern = GetTickCount();

	m_eBelialCurState = BELAIL_IDLE;
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

	//UI
	if (m_pHpBarUI == nullptr)
		m_pHpBarUI = new CBelialUI(this);
	m_pHpBarUI->Initialize();
	if (m_pHpBarUI != nullptr)
		m_pHpBarUI->Close();

	// 백
	if (m_vecBack.empty())
	{
		CBelialBack* pBack = new CBelialBack(this, 0, 0);
		m_vecBack.push_back(pBack);
		pBack = new CBelialBack(this, 20, 100);
		m_vecBack.push_back(pBack);
		pBack = new CBelialBack(this, 80, 50);
		m_vecBack.push_back(pBack);
		pBack = new CBelialBack(this, 60, 75);
		m_vecBack.push_back(pBack);
	}
	for (auto& pBack : m_vecBack)
	{
		if (pBack != nullptr)
			pBack->Initialize();
	}

	AddFontResource(TEXT("Aa카시오페아"));
	m_hFont = CreateFont(100, 0, 0, 0, 0, 0, 0, 0,
		HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("Aa카시오페아"));
}

int CBelial::Update()
{
	if (m_fCurHp <= 0.f)
	{
		m_bIsDead = true;
		m_eBelialCurState = BELIAL_DEAD;

		m_DeadEffectTime += 0.01;
		// 리턴하기전에 딜레이 줘야할듯?
		if (m_DeadEffectTime < 3.f)
		{
			DeadEffect();
			float py(0.f);
			GET(CLineMgr)->Collision_Line(this, &py);
		}
		else
		{
			GET(CSoundMgr)->StopSound(SOUND_BGM);
			return OBJ_DEAD;
		}
	}
	__super::Update_Rect();
	Update_DetectRect();
	Attack_Rotate();
	Attack_Hand();

	if(m_eBelialCurState != BELIAL_DEAD)
		Move_Frame();


	if (m_pRHand != nullptr)
		m_pRHand->Update();
	if (m_pLHand != nullptr)
		m_pLHand->Update();
	if (m_pSpearMgr != nullptr)
		m_pSpearMgr->Update();
	for (auto& pBack : m_vecBack)
	{
		if (pBack != nullptr)
			pBack->Update();
	}

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
		m_bIntro = true;

		DWORD dwCurrentTime = GetTickCount();
		DWORD dwElapsedTime = dwCurrentTime - m_SpawnEffectStartTime;

		if (dwElapsedTime < 2500)
			m_bAlpha = (BYTE)(((float)dwElapsedTime / 2500) * 255.f);

		return 0;
	}
	else
	{
		GET(CCamera)->SetTarget(GET(CPlayerMgr)->GetPlayer());
		m_bIntro = false;
		//if (m_pHpBarUI != nullptr)
		//	m_pHpBarUI->Open();
	}

	if (m_SpawnEffectStartTime + 9000 < GetTickCount() && m_dwChangePattern + 7000 < GetTickCount())
	{
		m_eBelailPreState = m_eBelialCurState;
		do
		{
			m_eBelialCurState = BELIAL_STATE((rand() % 3) + 1);
		} while (m_eBelailPreState == m_eBelialCurState);
		m_dwChangePattern = GetTickCount();
	}

	if (m_bIsHit && m_dwLastHitTime + 10 < GetTickCount())
	{
		m_bIsHit = false;
	}

	if (m_pHpBarUI != nullptr)
		m_pHpBarUI->Update();

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
	if (m_pHpBarUI != nullptr)
		m_pHpBarUI->Late_Update();
	for (auto& pBack : m_vecBack)
	{
		if (pBack != nullptr)
			pBack->Late_Update();
	}
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

	for (auto& pBack : m_vecBack)
	{
		if (pBack != nullptr)
			pBack->Render(hDC);
	}

	if (m_bIntro)
	{
		GET(CUIMgr)->Find_UI(L"PlayerUI")->Close();
		m_pHpBarUI->Close();
		//HFONT hOldFont = (HFONT)SelectObject(hDC, m_hFont);
		//wstring text = L"벨 리 알";
		//SetBkMode(hDC, TRANSPARENT);
		//SetTextColor(hDC, RGB(255, 255, 255));
		//TextOut(hDC, 200, WINCY - 200, text.c_str(), (int)text.size());
		//SelectObject(hDC, hOldFont);
		HDC hMemDC = GET(CResourceMgr)->Find_Bmp(m_wsFrameKey);

		BLENDFUNCTION bf = {};
		bf.BlendOp = AC_SRC_OVER;					// 일반적인 소스 오버 블렌딩
		bf.BlendFlags = 0;							// 예약 필드 (0으로 설정)
		bf.SourceConstantAlpha = m_bAlpha;			// 우리가 설정한 불투명도 값 (0~255)
		bf.AlphaFormat = AC_SRC_ALPHA;				// 알파 채널이 비트맵 자체에 없을 경우 (Constant Alpha 사용)


		AlphaBlend(
			hDC, // 대상 HDC
			m_tRect.left - ScrollX, // 대상 X
			m_tRect.top - ScrollY,  // 대상 Y
			m_tInfo.fCX,            // 대상 너비
			m_tInfo.fCY,            // 대상 높이
			hMemDC,                   // 소스 HDC
			m_iFrameWidth * m_tFrame.iStart,
			m_iFrameHeight * 0,                    // 소스 Y
			m_iFrameWidth,          // 소스 너비
			m_iFrameHeight,         // 소스 높이
			bf                      // BLENDFUNCTION 구조체
		);
	}
	else
	{
		GET(CUIMgr)->Find_UI(L"PlayerUI")->Open();
		if (m_SpawnEffectStartTime + 7000 < GetTickCount())
			m_pHpBarUI->Open();
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
	}


	if (m_bIsHit)
	{
		if (m_eBelialCurState == ATTACK_ROTATE)
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

	if (m_pHpBarUI != nullptr)
		m_pHpBarUI->Render(hDC);
}

void CBelial::Release()
{
	Safe_Delete(m_pRHand);
	Safe_Delete(m_pLHand);
	Safe_Delete(m_pSpearMgr);
	if (m_hFont)
	{
		DeleteObject(m_hFont);
		m_hFont = NULL;
	}
	RemoveFontResource(TEXT("Aa카시오페아"));
}

void CBelial::Motion_Change()
{
	if (m_eBelailPreState != m_eBelialCurState)
	{
		switch (m_eBelialCurState)
		{
		case BELIAL_STATE::BELAIL_IDLE:
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
		case BELIAL_STATE::BELIAL_DEAD:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 0;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			m_wsFrameKey = L"SkellBossDead";
			m_iFrameWidth = 210;
			m_iFrameHeight = 231;
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
			m_tInfo.fCX = m_iFrameWidth;
			m_tInfo.fCY = m_iFrameHeight;
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
			m_tInfo.fCX = m_iFrameWidth;
			m_tInfo.fCY = m_iFrameHeight;
			break;
		default:
			m_tFrame.iStart = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.iEnd = 9;
			m_tFrame.dwSpeed = 100.f;
			m_iFrameWidth = 210.f;
			m_iFrameHeight = 285.f;
			m_wsFrameKey = L"BelialIdle";
			m_tInfo.fCX = m_iFrameWidth;
			m_tInfo.fCY = m_iFrameHeight;
			break;
		}
		m_eBelailPreState = m_eBelialCurState;
	}

}

void CBelial::Attack_Rotate()
{
	static float RightAngle = 0.f;
	static float ToptAngle = 90.f;
	static float LefttAngle = 180.f;
	static float DownAngle = 270.f;
	if (m_eBelialCurState == ATTACK_ROTATE && m_tFrame.iStart <= m_tFrame.iEnd)
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
	if (m_eBelialCurState == ATTACK_HAND && m_dwHandAttackTick + 2000 < GetTickCount())
	{
		isRightHandOn = !isRightHandOn;
		m_pRHand->SetActive(isRightHandOn);
		m_pLHand->SetActive(!isRightHandOn);
		m_dwHandAttackTick = GetTickCount();
	}
}

void CBelial::DeadEffect()
{

	m_tInfo.fY += 1.f;

	if (m_bIsSpawnSound)
	{
		GET(CSoundMgr)->PlaySoundW(L"MonsterDie.wav", SOUND_EFFECT, 1.f);
		m_bIsSpawnSound = false;
	}
}