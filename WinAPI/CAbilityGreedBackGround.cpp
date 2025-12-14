#include "pch.h"
#include "CAbilityGreedBackGround.h"
#include "CAbilityGreedBtn.h"
CAbilityGreedBackGround::CAbilityGreedBackGround()
{
}

CAbilityGreedBackGround::~CAbilityGreedBackGround()
{
	Release();
}

void CAbilityGreedBackGround::Initialize()
{
	m_iFrameWidth = 62;
	m_iFrameHeight = 116;

	m_tInfo.fCX = m_iFrameWidth * 3;
	m_tInfo.fCY = m_iFrameHeight * 3;
	__super::Update_Rect();

	m_tFrame.iStart = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.iEnd = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();
	m_wsFrameKey = L"AbilityBackground_Greed";
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/Ability/AbilityBackground_Greed.bmp", L"AbilityBackground_Greed");


	CUI* btn = new CAbilityGreedBtn;
	btn->Set_Pos(m_tRect.left + m_tInfo.fCX * 0.5, m_tRect.bottom - 30);
	AddChildUI(btn);
	for (auto& pChildUI : m_vecChildUI)
	{
		pChildUI->Initialize();
	}
}

int CAbilityGreedBackGround::Update()
{
	__super::Update_Rect();
	for (auto& pChildUI : m_vecChildUI)
	{
		pChildUI->Update();
	}
	return 0;
}

void CAbilityGreedBackGround::Late_Update()
{
	for (auto& pChildUI : m_vecChildUI)
	{
		pChildUI->Late_Update();
	}
}

void CAbilityGreedBackGround::Render(HDC hDC)
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

	for (auto& pChildUI : m_vecChildUI)
	{
		pChildUI->Render(hDC);
	}
}

void CAbilityGreedBackGround::Release()
{

}