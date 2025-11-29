#include "pch.h"
#include "CRunEffect.h"
#include "CCamera.h"
#include "CResourceMgr.h"

CRunEffect::CRunEffect() : m_pOwner(nullptr)
{
}

CRunEffect::~CRunEffect()
{
}

void CRunEffect::Initialize()
{
	m_tInfo.fCX = 48.f;
	m_tInfo.fCY = 48.f;
}

int CRunEffect::Update()
{
	//플레이어 따라다님
	if (m_pOwner->IsFlipped())
	{
		m_tInfo.fX = m_pOwner->Get_Info()->fX - m_tInfo.fCX * 0.5f;
		m_tInfo.fY = m_pOwner->Get_Rect()->bottom - m_tInfo.fCY * 0.5f;
	}
	else
	{
		m_tInfo.fX = m_pOwner->Get_Info()->fX + m_tInfo.fCX * 0.5f;
		m_tInfo.fY = m_pOwner->Get_Rect()->bottom - m_tInfo.fCY * 0.5f;
	}
    return 0;
}

void CRunEffect::Late_Update()
{
}

void CRunEffect::Render(HDC hDC)
{
	HDC hMemDC = CResourceMgr::Get_Instance()->Find_Bmp(m_wsFrameKey);

	int SrcX = 48 * m_tFrame.iStart;

	GdiTransparentBlt(
		hDC,
		(int)(m_tRect.left - GET(CCamera)->Get_ScrollX()),			// 복사 받을 공간의 LEFT	
		(int)(m_tRect.top - GET(CCamera)->Get_ScrollY()),				// 복사 받을 공간의 TOP
		48,													// 복사 받을 공간의 가로 
		48,													// 복사 받을 공간의 세로 
		hMemDC,															// 복사 할 DC
		SrcX,															// 원본이미지 left
		0,																// 원본이미지 top
		48,													// 원본이미지 가로
		48,													// 원본이미지 세로
		RGB(255, 0, 255)
	);
}

void CRunEffect::Release()
{
}
