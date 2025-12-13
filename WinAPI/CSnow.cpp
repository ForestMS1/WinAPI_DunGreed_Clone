#include "pch.h"
#include "CSnow.h"

CSnow::CSnow()
{
	m_eRender = EFFECT;
}

CSnow::~CSnow()
{
	Release();
}

void CSnow::Initialize()
{
	m_fSpeed = 10.f;
	m_tInfo.fCX = WINCX;
	m_tInfo.fCY = WINCY;
	m_tInfo.fX = WINCX >> 1;
	m_tInfo.fY = WINCY >> 1;

	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Background/Snow.bmp", L"Snow");
}

int CSnow::Update()
{

	m_tInfo.fY += m_fSpeed;
	__super::Update_Rect();

	if(m_tInfo.fY >= WINCY)
		m_tInfo.fY = WINCY >> 1;


	return 0;
}

void CSnow::Late_Update()
{
}

void CSnow::Render(HDC hDC)
{
	HDC hSnowDC = GET(CResourceMgr)->Find_Bmp(L"Snow");
	GdiTransparentBlt(
		hDC,
		m_tRect.left,
		m_tRect.top - WINCY,
		WINCX,
		WINCY,
		hSnowDC,
		0,
		0,
		320,
		180,
		RGB(255, 0, 255)
	);
	GdiTransparentBlt(
		hDC,
		m_tRect.left,
		m_tRect.top,
		WINCX,
		WINCY,
		hSnowDC,
		0,
		0,
		320,
		180,
		RGB(255, 0, 255)
	);
}

void CSnow::Release()
{
}
