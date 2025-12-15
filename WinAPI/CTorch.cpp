#include "pch.h"
#include "CTorch.h"

CTorch::CTorch()
{
	m_eRender = GAMEOBJECT;
}

CTorch::~CTorch()
{
}

void CTorch::Initialize()
{
	m_iFrameWidth = 20;
	m_iFrameHeight = 30;
	m_tInfo.fCX = m_iFrameWidth * 3.5;
	m_tInfo.fCY = m_iFrameHeight * 3.5;
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 6;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();
	__super::Update_Rect();
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/torch.bmp", L"Torch");
}

int CTorch::Update()
{
	Move_Frame();
	return 0;
}

void CTorch::Late_Update()
{
}

void CTorch::Render(HDC hDC)
{
	int scrollX = GET(CCamera)->Get_ScrollX();
	int scrollY = GET(CCamera)->Get_ScrollY();
	HDC hMemDC = GET(CResourceMgr)->Find_Bmp(L"Torch");
	GdiTransparentBlt(
		hDC,
		m_tRect.left - scrollX,
		m_tRect.top - scrollY,
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

void CTorch::Release()
{
}
