#include "pch.h"
#include "CGoldText.h"

CGoldText::CGoldText(int gold, float fX, float fY) : m_ft(0.f)
{
	m_iGold = gold;
	m_tInfo.fX = fX;
	m_tInfo.fY = fY;
	m_eRender = EFFECT;
	m_dwSpawnTime = GetTickCount();
	m_dwLifeTime = 500;
}

CGoldText::~CGoldText()
{
}

void CGoldText::Initialize()
{
	m_fSpeed = 5.f;
	m_iFrameWidth = 6;
	m_iFrameHeight = 11;
	m_tInfo.fCX = m_iFrameWidth * 4;
	m_tInfo.fCY = m_iFrameHeight * 4;
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/Font/GoldFont.bmp", L"GoldFont");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/Font/G.bmp", L"G");
}

int CGoldText::Update()
{
	m_ft += 0.05f;
	__super::Update_Rect();
	m_tInfo.fX += m_fSpeed * cosf(60.f * PI / 180) * m_ft;
	m_tInfo.fY -= m_fSpeed * m_ft - m_fSpeed * sinf(60.f * PI / 180) * m_ft * m_ft;

	if (m_dwSpawnTime + m_dwLifeTime < GetTickCount())
		return OBJ_DEAD;

	return OBJ_NOEVENT;
}

void CGoldText::Late_Update()
{

}

void CGoldText::Render(HDC hDC)
{
	int scrollX = GET(CCamera)->Get_ScrollX();
	int scrollY = GET(CCamera)->Get_ScrollY();
	wstring wsDamage = to_wstring(m_iGold);

	for (size_t i = 0; i < wsDamage.size(); ++i)
	{
		m_tFrame.iStart = wsDamage[i] - L'0';


		HDC hMemDC = GET(CResourceMgr)->Find_Bmp(L"GoldFont");
		GdiTransparentBlt(
			hDC,
			m_tRect.left + (m_iFrameWidth * 4 * i) - scrollX,
			m_tRect.top - scrollY,
			m_tInfo.fCX,
			m_tInfo.fCY,
			hMemDC,
			m_iFrameWidth * m_tFrame.iStart,
			m_iFrameHeight * 0,
			m_iFrameWidth,
			m_iFrameHeight,
			RGB(255, 0, 255)
		);
	}
	HDC hGDC = GET(CResourceMgr)->Find_Bmp(L"G");
	GdiTransparentBlt(
		hDC,
		m_tRect.left + (m_iFrameWidth * 4 * wsDamage.size()) - scrollX,
		m_tRect.top - scrollY,
		m_tInfo.fCX,
		m_tInfo.fCY,
		hGDC,
		0,
		0,
		m_iFrameWidth,
		m_iFrameHeight,
		RGB(255, 0, 255)
	);
}

void CGoldText::Release()
{
}
