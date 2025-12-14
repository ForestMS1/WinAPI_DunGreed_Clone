#include "pch.h"
#include "CStarBulletFX.h"

CStarBulletFX::CStarBulletFX(float fX, float fY) : m_ft(0.f), m_bAlpha(255)
{
	m_tInfo.fX = fX;
	m_tInfo.fY = fY;
	//m_eRender = EFFECT;
	m_eRender = GAMEOBJECT;
	m_dwSpawnTime = GetTickCount();
	m_dwLifeTime = 500;
}

CStarBulletFX::~CStarBulletFX()
{
}

void CStarBulletFX::Initialize()
{
	m_iFrameWidth = 14;
	m_iFrameHeight = 13;
	m_tInfo.fCX = m_iFrameWidth;
	m_tInfo.fCY = m_iFrameHeight;
	m_tFrame.iMotion = 0;
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 3;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();

	GET(CResourceMgr)->Insert_AlphaBmp(L"../Resources/Images/Item/Bullet/StarBullet.bmp", L"StarBulletBmp");
	m_wsFrameKey = L"StarBulletBmp";
}

int CStarBulletFX::Update()
{
	__super::Update_Rect();



	DWORD dwCurrentTime = GetTickCount();
	DWORD dwElapsedTime = dwCurrentTime - m_dwSpawnTime;

	if (dwElapsedTime < m_dwLifeTime)
		m_bAlpha = (BYTE)((1.f - (float)dwElapsedTime / m_dwLifeTime) * 255.f);
	else
		return OBJ_DEAD;



	return OBJ_NOEVENT;
}

void CStarBulletFX::Late_Update()
{
}

void CStarBulletFX::Render(HDC hDC)
{
	int scrollX = GET(CCamera)->Get_ScrollX();
	int scrollY = GET(CCamera)->Get_ScrollY();

	HDC hGDC = GET(CResourceMgr)->Find_Bmp(m_wsFrameKey);

	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;					// 일반적인 소스 오버 블렌딩
	bf.BlendFlags = 0;							// 예약 필드 (0으로 설정)
	bf.SourceConstantAlpha = m_bAlpha;			// 우리가 설정한 불투명도 값 (0~255)
	bf.AlphaFormat = AC_SRC_ALPHA;				// 알파 채널이 비트맵 자체에 없을 경우 (Constant Alpha 사용)


	AlphaBlend(
		hDC, // 대상 HDC
		m_tRect.left - scrollX, // 대상 X
		m_tRect.top - scrollY,  // 대상 Y
		m_tInfo.fCX,            // 대상 너비
		m_tInfo.fCY,            // 대상 높이
		hGDC,                   // 소스 HDC
		0,                      // 소스 X
		m_iFrameHeight * m_tFrame.iMotion,                      // 소스 Y
		m_iFrameWidth,          // 소스 너비
		m_iFrameHeight,         // 소스 높이
		bf                      // BLENDFUNCTION 구조체
	);
}

void CStarBulletFX::Release()
{
}
