#include "pch.h"
#include "CObj.h"

CObj::CObj() : m_fSpeed(0.f), m_bIsFlipped(false), m_bIsDead(false)
, m_iFrameWidth(0.f), m_iFrameHeight(0.f), m_eRender(RENDER_END)
{
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
	ZeroMemory(&m_tRect, sizeof(m_tRect));
	ZeroMemory(&m_tFrame, sizeof(m_tFrame));
}

CObj::~CObj()
{
}

void CObj::Update_Rect()
{
	m_tRect.left	= m_tInfo.fX - m_tInfo.fCX / 2;
	m_tRect.right	= m_tInfo.fX + m_tInfo.fCX / 2;
	m_tRect.top		= m_tInfo.fY - m_tInfo.fCY / 2;
	m_tRect.bottom	= m_tInfo.fY + m_tInfo.fCY / 2;
}

void CObj::Move_Frame()
{
	if (m_tFrame.dwSpeed + m_tFrame.dwTime < GetTickCount())
	{
		++m_tFrame.iStart;
		m_tFrame.dwTime = GetTickCount();


		if (m_tFrame.iStart > m_tFrame.iEnd)
			m_tFrame.iStart = 0;
	}
}
