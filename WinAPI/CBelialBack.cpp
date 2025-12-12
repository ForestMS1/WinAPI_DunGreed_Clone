#include "pch.h"
#include "CBelialBack.h"

CBelialBack::CBelialBack() : m_bAlpha(0), m_bIntro(false)
{
	m_pOwner = nullptr;
}

CBelialBack::CBelialBack(CEnemy* pBelial, float fX, float fY) : m_bAlpha(0), m_bIntro(false), offsetX(fX), offsetY(fY)
{
	m_pOwner = pBelial;
}

CBelialBack::~CBelialBack()
{
}

void CBelialBack::Initialize()
{
	m_tInfo.fX = m_pOwner->Get_Info()->fX + offsetX;
	m_tInfo.fY = m_pOwner->Get_Info()->fY + offsetY;

	m_tFrame.iStart = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.iEnd = 9;
	m_tFrame.dwSpeed = 100.f;
	m_iFrameWidth = 147;
	m_iFrameHeight = 144;
	m_tInfo.fCX = m_iFrameWidth;
	m_tInfo.fCY = m_iFrameHeight;
	m_tFrame.dwTime = GetTickCount();
	GET(CResourceMgr)->Insert_AlphaBmp(L"../Resources/Images/Unit/Enemy/Belial/SkellBossBack.bmp", L"SkellBossBack");

	m_wsFrameKey = L"SkellBossBack";
}

int CBelialBack::Update()
{
	__super::Update_Rect();
	Move_Frame();
	return 0;
}

void CBelialBack::Late_Update()
{
}

void CBelialBack::Render(HDC hDC)
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
}

void CBelialBack::Release()
{
}

void CBelialBack::Motion_Change()
{
}
