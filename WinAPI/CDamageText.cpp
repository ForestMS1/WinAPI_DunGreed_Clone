#include "pch.h"
#include "CDamageText.h"

CDamageText::CDamageText(int damage, float fX, float fY) : m_ft(0.f)
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
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/Font/DamageFont.bmp", L"DamageFont");
}

int CDamageText::Update()
{
	m_ft += 0.05f;
	__super::Update_Rect();
	m_tInfo.fX += m_fSpeed * cosf(60.f * PI / 180) * m_ft;
	m_tInfo.fY -= m_fSpeed*m_ft - m_fSpeed * sinf(60.f * PI / 180) * m_ft * m_ft;

	if(m_dwSpawnTime + m_dwLifeTime < GetTickCount())
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
}

void CDamageText::Release()
{
}
