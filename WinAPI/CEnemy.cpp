#include "pch.h"
#include "CEnemy.h"

CEnemy::CEnemy() : m_fDetectfCX(0.f), m_fDetectfCY(0.f), m_bIsInPlayer(false)
{
	ZeroMemory(&m_tDetectRect, sizeof(RECT));
	m_eRender = GAMEOBJECT;
}

CEnemy::~CEnemy()
{
}

void CEnemy::Update_DetectRect()
{
	m_tDetectRect.left = m_tInfo.fX - m_fDetectfCX * 0.5f;
	m_tDetectRect.top = m_tInfo.fY - m_fDetectfCY * 0.5f;
	m_tDetectRect.right = m_tInfo.fX + m_fDetectfCX * 0.5f;
	m_tDetectRect.bottom = m_tInfo.fY + m_fDetectfCY * 0.5f;
}
