#include "pch.h"
#include "CPlayer.h"

CPlayer::CPlayer()
{
}
CPlayer::~CPlayer()
{

}

void CPlayer::Initialize()
{
	m_tInfo.fX = 100.f;
	m_tInfo.fY = 100.f;
	m_tInfo.fCX = 50.f;
	m_tInfo.fCY = 50.f;
}

int CPlayer::Update()
{
	__super::Update_Rect();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
}

void CPlayer::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CPlayer::Release()
{
}
