#include "pch.h"
#include "CBelialLHand.h"
#include "CBelial.h"
CBelialLHand::CBelialLHand() : m_pOwner(nullptr), m_pLaser(nullptr), m_fAtackDuration(0.f), m_fMoveDuration(0.f), m_bMoveEnd(false)
, m_isActive(false)
{

}

CBelialLHand::CBelialLHand(CEnemy* pBelial) : m_pLaser(nullptr), m_fAtackDuration(0.f), m_fMoveDuration(0.f), m_bMoveEnd(false)
, m_isActive(false)
{
	m_pOwner = pBelial;
}

CBelialLHand::~CBelialLHand()
{
	Release();
}

void CBelialLHand::Initialize()
{
	float offsetX = 280.f;
	float offsetY = 100.f;
	m_tInfo.fX = m_pOwner->Get_Info()->fX - offsetX;
	m_tInfo.fY = m_pOwner->Get_Info()->fY + offsetY;
	m_tInfo.fCX = 171.f;
	m_tInfo.fCY = 378 * 0.5f;

	m_tFrame.iStart = 0;
	m_tFrame.iMotion = 1;
	m_tFrame.iEnd = 9;
	m_tFrame.dwSpeed = 50.f;
	m_iFrameWidth = 171.f;
	m_iFrameHeight = 378.f * 0.5f;
	m_tFrame.dwTime = GetTickCount();
	//GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/Belial/SkellBossHandIdle.bmp", L"HandIdle");
	//GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/Belial/SkellBossHandAttack.bmp", L"HandAttack");
	m_wsFrameKey = L"HandIdle";

	if (m_pLaser == nullptr)
	{
		m_pLaser = new CLaser(this, false);
	}
	m_pLaser->Initialize();

	m_eBelailPreState = BELIAL_STATE::BELAIL_IDLE;
}

int CBelialLHand::Update()
{
	m_bIntro = dynamic_cast<CBelial*>(m_pOwner)->IsIntro();
	m_bAlpha = dynamic_cast<CBelial*>(m_pOwner)->GetAlpha();
	m_eBelialCurState = dynamic_cast<CBelial*>(m_pOwner)->GetCurState();
	__super::Update_Rect();
	if (m_eBelialCurState != BELIAL_STATE::BELIAL_DEAD)
		Move_Frame();

	if (!m_bMoveEnd && m_eBelialCurState == BELIAL_STATE::ATTACK_HAND && m_fMoveDuration < 1.25f)
	{
		MoveToPlayer();
		m_fMoveDuration += 0.01f;
	}
	if (m_fMoveDuration >= 1.25f)
	{
		m_fMoveDuration = 0.f;
		m_bMoveEnd = true;
	}

	if (!m_isActive)
		return 0;
	if (m_bMoveEnd && m_eBelialCurState == BELIAL_STATE::ATTACK_HAND && m_fAtackDuration < 1.25f)
	{
		m_pLaser->SetActive(true);
		m_pLaser->Update();
		m_fAtackDuration += 0.01f;
	}
	if (m_fAtackDuration >= 1.25f)
	{
		m_pLaser->Initialize();
		m_pLaser->SetActive(false);
		m_fAtackDuration = 0.f;
		m_bMoveEnd = false;
	}
	return 0;
}

void CBelialLHand::Late_Update()
{
	Motion_Change();
	if (m_pLaser != nullptr)
	{
		m_pLaser->Late_Update();
	}
}

void CBelialLHand::Render(HDC hDC)
{
	HDC hMemDC = GET(CResourceMgr)->Find_Bmp(m_wsFrameKey);

	int ScrollX = (int)GET(CCamera)->Get_ScrollX();
	int ScrollY = (int)GET(CCamera)->Get_ScrollY();
	if (m_bIntro)
	{
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
			m_iFrameHeight * m_tFrame.iMotion,                    // 소스 Y
			m_iFrameWidth,          // 소스 너비
			m_iFrameHeight,         // 소스 높이
			bf                      // BLENDFUNCTION 구조체
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
	if (m_pLaser != nullptr)
	{
		m_pLaser->Render(hDC);
	}
}

void CBelialLHand::Release()
{
	Safe_Delete(m_pLaser);
}

void CBelialLHand::Motion_Change()
{
	if (m_eBelailPreState != m_eBelialCurState)
	{
		switch (m_eBelialCurState)
		{
		case BELIAL_STATE::BELAIL_IDLE:
			m_tFrame.iStart = 0;
			m_tFrame.iMotion = 1;
			m_tFrame.iEnd = 9;
			m_wsFrameKey = L"HandIdle";
			m_tFrame.dwSpeed = 50.f;
			m_iFrameWidth = 171.f;
			m_iFrameHeight = 378.f * 0.5f;
			m_tFrame.dwTime = GetTickCount();
			break;

		case BELIAL_STATE::ATTACK_ROTATE:
			m_tFrame.iStart = 0;
			m_tFrame.iMotion = 1;
			m_tFrame.iEnd = 9;
			m_wsFrameKey = L"HandIdle";
			m_tFrame.dwSpeed = 50.f;
			m_iFrameWidth = 171.f;
			m_iFrameHeight = 378.f * 0.5f;
			m_tInfo.fCX = m_iFrameWidth;
			m_tInfo.fCY = m_iFrameHeight;
			m_tFrame.dwTime = GetTickCount();
			break;
		case BELIAL_STATE::ATTACK_HAND:
			m_tFrame.iStart = 0;
			m_tFrame.iMotion = 1;
			m_tFrame.iEnd = 9;
			m_wsFrameKey = L"HandAttack";
			m_tFrame.dwSpeed = 50.f;
			m_iFrameWidth = 195.f;
			m_iFrameHeight = 426.f * 0.5f;
			m_tInfo.fCX = m_iFrameWidth;
			m_tInfo.fCY = m_iFrameHeight;
			m_tFrame.dwTime = GetTickCount();
			break;
		case BELIAL_STATE::BELIAL_DEAD:
			m_tFrame.iStart = 9;
			m_tFrame.iMotion = 1;
			m_tFrame.iEnd = 9;
			m_wsFrameKey = L"HandAttack";
			m_tFrame.dwSpeed = 50.f;
			m_iFrameWidth = 195.f;
			m_iFrameHeight = 426.f * 0.5f;
			m_tInfo.fCX = m_iFrameWidth;
			m_tInfo.fCY = m_iFrameHeight;
			m_tFrame.dwTime = GetTickCount();
			break;
		default:
			m_tFrame.iStart = 0;
			m_tFrame.iMotion = 1;
			m_tFrame.iEnd = 9;
			m_wsFrameKey = L"HandIdle";
			m_tFrame.dwSpeed = 50.f;
			m_iFrameWidth = 171.f;
			m_iFrameHeight = 378.f * 0.5f;
			m_tFrame.dwTime = GetTickCount();
			m_tInfo.fCX = m_iFrameWidth;
			m_tInfo.fCY = m_iFrameHeight;
			break;
		}
		m_eBelailPreState = m_eBelialCurState;
	}
}
void CBelialLHand::MoveToPlayer()
{
	if (!GET(CObjMgr)->GetObjLayer(OBJ_PLAYER).empty())
	{
		CObj* pPlayer = GET(CObjMgr)->GetObjLayer(OBJ_PLAYER).front();

		diffY = m_tInfo.fY - pPlayer->Get_Info()->fY;
		//플레이어가 더 위에
		if (diffY > 0.f)
		{
			m_tInfo.fY -= 5.f;
		}
		else
		{
			m_tInfo.fY += 5.f;

		}
		if (fabsf(diffY) < 5.f)
		{
			m_bMoveEnd = true;
		}
	}

}