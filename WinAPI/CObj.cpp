#include "pch.h"
#include "CObj.h"

CObj::CObj()
{
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
	ZeroMemory(&m_tRect, sizeof(m_tInfo));

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
