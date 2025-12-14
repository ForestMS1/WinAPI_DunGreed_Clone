#include "pch.h"
#include "CAbilityFX.h"

CAbilityFX::CAbilityFX()
{
	m_eRender = EFFECT;
}

CAbilityFX::~CAbilityFX()
{
}

void CAbilityFX::Initialize()
{
	m_iFrameWidth = 24;
	m_iFrameHeight = 24;

	m_tInfo.fCX = m_iFrameWidth * 3;
	m_tInfo.fCY = m_iFrameHeight * 3;

	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 5;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();
	m_wsFrameKey = L"AbilityFX";
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/Ability/AbilityFX.bmp", L"AbilityFX");
}

int CAbilityFX::Update()
{
	__super::Update_Rect();

	Move_Frame_No_Loop();

	if (m_tFrame.iStart > m_tFrame.iEnd)
		return OBJ_DEAD;
	return 0;
}

void CAbilityFX::Late_Update()
{
}

void CAbilityFX::Render(HDC hDC)
{
	HDC hMemDC = GET(CResourceMgr)->Find_Bmp(m_wsFrameKey);
	GdiTransparentBlt(
		hDC,
		m_tRect.left,
		m_tRect.top,
		m_tInfo.fCX,
		m_tInfo.fCY,
		hMemDC,
		m_tFrame.iStart * m_iFrameWidth,
		m_tFrame.iMotion * m_iFrameHeight,
		m_iFrameWidth,
		m_iFrameHeight,
		RGB(255, 0, 255)
	);
}

void CAbilityFX::Release()
{
}
