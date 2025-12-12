#include "pch.h"
#include "CDamageText.h"

CDamageText::CDamageText(int damage, float fX, float fY) : m_ft(0.f) , m_bAlpha(255)
{
	m_iDamage = damage;
	m_tInfo.fX = fX;
	m_tInfo.fY = fY;
	m_eRender = EFFECT;
	m_dwSpawnTime = GetTickCount();
	m_dwLifeTime = 500;
}

CDamageText::~CDamageText()
{
}

void CDamageText::Initialize()
{
	m_fSpeed = 5.f;
	m_iFrameWidth = 6;
	m_iFrameHeight = 11;
	m_tInfo.fCX = m_iFrameWidth * 4;
	m_tInfo.fCY = m_iFrameHeight * 4;
	GET(CResourceMgr)->Insert_AlphaBmp(L"../Resources/Images/UI/Font/DamageFont.bmp", L"DamageFont");
}

int CDamageText::Update()
{
	m_ft += 0.05f;
	__super::Update_Rect();
	m_tInfo.fX += m_fSpeed * cosf(60.f * PI / 180) * m_ft;
	m_tInfo.fY -= m_fSpeed*m_ft - m_fSpeed * sinf(60.f * PI / 180) * m_ft * m_ft;

	DWORD dwCurrentTime = GetTickCount();
	DWORD dwElapsedTime = dwCurrentTime - m_dwSpawnTime;

	if (dwElapsedTime < m_dwLifeTime)
		m_bAlpha = (BYTE)((1.f - (float)dwElapsedTime / m_dwLifeTime) * 255.f);
	else
		return OBJ_DEAD;

	return OBJ_NOEVENT;
}

void CDamageText::Late_Update()
{

}

void CDamageText::Render(HDC hDC)
{
	int scrollX = GET(CCamera)->Get_ScrollX();
	int scrollY = GET(CCamera)->Get_ScrollY();
	wstring wsDamage = to_wstring(m_iDamage);

	for (size_t i = 0; i < wsDamage.size(); ++i)
	{
		m_tFrame.iStart = wsDamage[i] - L'0';


		HDC hMemDC = GET(CResourceMgr)->Find_Bmp(L"DamageFont");

		BLENDFUNCTION bf = {};
		bf.BlendOp = AC_SRC_OVER;					// 일반적인 소스 오버 블렌딩
		bf.BlendFlags = 0;							// 예약 필드 (0으로 설정)
		bf.SourceConstantAlpha = m_bAlpha;			// 우리가 설정한 불투명도 값 (0~255)
		bf.AlphaFormat = AC_SRC_ALPHA;				// 알파 채널이 비트맵 자체에 없을 경우 (Constant Alpha 사용)


		AlphaBlend(
			hDC, // 대상 HDC
			m_tRect.left + (m_iFrameWidth * 4 * i) - scrollX, // 대상 X
			m_tRect.top - scrollY,  // 대상 Y
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
}

void CDamageText::Release()
{
}
