#include "pch.h"
#include "CAbilityGreedBtn.h"
#include "CAbilityFX.h"

CAbilityGreedBtn::CAbilityGreedBtn()
{

}

CAbilityGreedBtn::~CAbilityGreedBtn()
{
	Release();
}

void CAbilityGreedBtn::Initialize()
{
	m_iFrameWidth = 18;
	m_iFrameHeight = 18;

	m_tInfo.fCX = m_iFrameWidth * 3;
	m_tInfo.fCY = m_iFrameHeight * 3;
	__super::Update_Rect();

	m_tFrame.iStart = 0;
	m_tFrame.iMotion = 1;
	m_tFrame.iEnd = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();
	m_wsFrameKey = L"AbilityBackgroundButton_Greed";
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/Ability/AbilityBackgroundButton_Greed.bmp", L"AbilityBackgroundButton_Greed");
}

int CAbilityGreedBtn::Update()
{
	__super::Update_Rect();
	if (PtInRect(&m_tRect, GET(CMouse)->Get_Point()))
	{
		m_bMouseOn = true;
	}
	else
	{
		m_bMouseOn = false;
	}

	Clicked();
	return 0;
}

void CAbilityGreedBtn::Late_Update()
{

}

void CAbilityGreedBtn::Render(HDC hDC)
{

	HDC hMemDC = GET(CResourceMgr)->Find_Bmp(m_wsFrameKey);

	GdiTransparentBlt(
		hDC,
		m_tRect.left,
		m_tRect.top,
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

void CAbilityGreedBtn::Release()
{

}

void CAbilityGreedBtn::Clicked()
{
	if (m_bMouseOn)
	{
		if (GET(CKeyMgr)->Key_Down(VK_LBUTTON))
		{
			GET(CSoundMgr)->PlaySoundW(L"Ability_Up.wav", SOUND_EFFECT, 1.f);
			GET(CPlayerMgr)->SetAddGreed(10);
			//GET(CObjMgr)->AddObject(OBJ_EFFECT, CAbstractFactory<CAbilityFX>::Create(m_tInfo.fX, m_tInfo.fY));
		}
	}
	
}
