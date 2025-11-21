#include "pch.h"
#include "CPlayer.h"
#include "CResourceMgr.h"

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
	m_tInfo.fCX = 60.f;
	m_tInfo.fCY = 60.f;

	CResourceMgr::Get_Instance()->Insert_Image(L"../Resource/maja2.bmp", L"Player");
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
	HDC hMemDC = CreateCompatibleDC(hDC);
	hMemDC = CResourceMgr::Get_Instance()->Find_Image(L"Player");

	GdiTransparentBlt(hDC,			// 복사 받을 DC
		m_tRect.left,				// 복사 받을 공간의 LEFT	
		m_tRect.top,				// 복사 받을 공간의 TOP
		(int)m_tInfo.fCX,			// 복사 받을 공간의 가로 
		(int)m_tInfo.fCY,			// 복사 받을 공간의 세로 
		hMemDC,				// 복사 할 DC
		0,					// 복사할 이미지의 LEFT, TOP
		0,
		(INT)m_tInfo.fCX,		// 복사할 이미지의 가로, 세로
		(INT)m_tInfo.fCY,
		RGB(255, 255, 255));	// 제거할 색상
}

void CPlayer::Release()
{
}
