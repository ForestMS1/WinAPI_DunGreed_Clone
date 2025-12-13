#include "pch.h"
#include "CNifleHeim.h"
#include "CPortal.h"

CNifleHeim::CNifleHeim() : m_bPlayBossBGM(false)
, m_bIntro(false), m_bAlpha(0), m_pPortal(nullptr), CompleteCreatePortal(false)
{
}

CNifleHeim::~CNifleHeim()
{
	Release();
}

void CNifleHeim::Initialize()
{
	m_fMaxHp = 1000.f;
	m_fCurHp = m_fMaxHp;

	m_iDropGold = 125 + rand() % 20;

	//플레이어 감지 범위
	m_fDetectfCX = 1500.f;
	m_fDetectfCY = 1700.f;

	m_tFrame.iStart = 0;
	m_tFrame.iMotion = 1;
	m_tFrame.iEnd = 5;
	m_tFrame.dwSpeed = 100.f;
	m_tFrame.dwTime = GetTickCount();
	m_iFrameWidth = 120;
	m_iFrameHeight = 96;
	m_tInfo.fCX = m_iFrameWidth;
	m_tInfo.fCY = m_iFrameHeight;
	m_wsFrameKey = L"NifleHeimIdle";


	m_eNifleHeimCurState = NIFLEHEIM_IDLE;

	GET(CResourceMgr)->Insert_AlphaBmp(L"../Resources/Images/Unit/Enemy/NifleHeim/Idle.bmp", L"NifleHeimIdle");
	GET(CResourceMgr)->Insert_AlphaBmp(L"../Resources/Images/Unit/Enemy/NifleHeim/die.bmp", L"NifleHeimDie");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/NifleHeim/enter.bmp", L"NifleHeimEnter");


	srand(time(0));


	m_SpawnEffectStartTime = GetTickCount();


	AddFontResource(TEXT("Aa카시오페아"));
	m_hFont = CreateFont(100, 0, 0, 0, 0, 0, 0, 0,
		HANGUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("Aa카시오페아"));
}

int CNifleHeim::Update()
{
	if (m_fCurHp <= 0.f)
	{
		m_bIsDead = true;
		m_eNifleHeimCurState = NIFLEHEIM_DEAD;

		//m_DeadEffectTime += 0.01;
		// 리턴하기전에 딜레이 줘야할듯?
		//if (m_DeadEffectTime < 3.f)
		//{
			DeadEffect();
			float py(0.f);
			GET(CLineMgr)->Collision_Line(this, &py);
		//}
		//else
		//{
			GET(CSoundMgr)->StopSound(SOUND_BGM);
			//return OBJ_DEAD;
			return OBJ_NOEVENT;
		//}
	}
	__super::Update_Rect();
	Update_DetectRect();
	if (GET(CPlayerMgr)->GetPlayer()->Get_Info()->fX < m_tInfo.fX)
		m_tFrame.iMotion = 1;
	else
		m_tFrame.iMotion = 0;


	if (m_eNifleHeimCurState != NIFLEHEIM_DEAD)
		Move_Frame();


	if (m_bIsInPlayer && m_SpawnEffectStartTime < GetTickCount() && GetTickCount() < m_SpawnEffectStartTime + 7000)
	{
		GET(CCamera)->SetTarget(nullptr);
		GET(CCamera)->SetLookAt(Vec2(m_tInfo.fX, m_tInfo.fY));
		if (!m_bPlayBossBGM)
		{
			GET(CSoundMgr)->PlaySound(L"2.IceBoss.wav", SOUND_BGM, 1.f);
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
	}

	if (m_bIsHit && m_dwLastHitTime + 10 < GetTickCount())
	{
		m_bIsHit = false;
	}

	if (m_pHpBarUI != nullptr)
		m_pHpBarUI->Update();

	return OBJ_NOEVENT;
}

void CNifleHeim::Late_Update()
{
	Motion_Change();

	if (m_pHpBarUI != nullptr)
		m_pHpBarUI->Late_Update();
}

void CNifleHeim::Render(HDC hDC)
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

	if (m_bIntro)
	{
		GET(CUIMgr)->Find_UI(L"PlayerUI")->Close();
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
		
	}

	if (m_pHpBarUI != nullptr)
		m_pHpBarUI->Render(hDC);
}

void CNifleHeim::Release()
{
	if (m_hFont)
	{
		DeleteObject(m_hFont);
		m_hFont = NULL;
	}
	RemoveFontResource(TEXT("Aa카시오페아"));
}

void CNifleHeim::Motion_Change()
{
	if (m_eNifleHeimPreState != m_eNifleHeimCurState)
	{
		switch (m_eNifleHeimCurState)
		{
		//case NIFLEHEIM_STATE::NIFLEHEIM_ENTER:
		//	m_tFrame.iStart = 0;
		//	m_tFrame.iMotion = 0;
		//	m_tFrame.iEnd = 15;
		//	m_tFrame.dwSpeed = 50.f;
		//	m_iFrameWidth = 40;
		//	m_iFrameHeight = 33;
		//	m_tInfo.fCX = m_iFrameWidth * 3;
		//	m_tInfo.fCY = m_iFrameHeight * 3;
		//	m_tFrame.dwTime = GetTickCount();
		//	m_wsFrameKey = L"NifleHeimEnter";
			break;
		case NIFLEHEIM_STATE::NIFLEHEIM_IDLE:
			m_tFrame.iStart = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.iEnd = 5;
			m_wsFrameKey = L"NifleHeimIdle";
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount();
			m_iFrameWidth = 120;
			m_iFrameHeight = 96;
			m_tInfo.fCX = m_iFrameWidth;
			m_tInfo.fCY = m_iFrameHeight;
			break;
		case NIFLEHEIM_STATE::NIFLEHEIM_DEAD:
			m_tFrame.iStart = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.iEnd = 28;
			m_wsFrameKey = L"NifleHeimDie";
			m_tFrame.dwSpeed = 50.f;
			m_tFrame.dwTime = GetTickCount();
			m_iFrameWidth = 43;
			m_iFrameHeight = 28;
			m_tInfo.fCX = m_iFrameWidth * 3;
			m_tInfo.fCY = m_iFrameHeight * 3;
			break;
		default:
			break;
		}
		m_eNifleHeimPreState = m_eNifleHeimCurState;
	}

}

void CNifleHeim::DeadEffect()
{
	if(m_tFrame.iStart < m_tFrame.iEnd)
		Move_Frame_No_Loop();

	if (m_tFrame.iStart == m_tFrame.iEnd - 1 && !CompleteCreatePortal)
	{
		m_pPortal = CAbstractFactory<CPortal>::Create(m_tInfo.fX, m_tInfo.fY);
		GET(CObjMgr)->AddObject(OBJ_NPC, m_pPortal);
		CompleteCreatePortal = true;
	}

	m_tInfo.fY += 1.f;

	if (m_bIsSpawnSound)
	{
		GET(CSoundMgr)->PlaySoundW(L"MonsterDie.wav", SOUND_EFFECT, 1.f);
		m_bIsSpawnSound = false;
	}
}