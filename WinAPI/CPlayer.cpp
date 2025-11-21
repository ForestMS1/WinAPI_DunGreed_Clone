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

	CResourceMgr::Get_Instance()->Insert_Png(L"../Resource/hero.png", L"Player");
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
	//HDC hMemDC = CreateCompatibleDC(hDC);
	//hMemDC = CResourceMgr::Get_Instance()->Find_Bmp(L"Player");

	Image* pImg = CResourceMgr::Get_Instance()->Find_Png(L"Player");

	if (pImg == nullptr)
		int a = 10;

	int frameWidth = 112;
	int frameHeight = 96;
	int frameIdx = 0;

	int SrcX = frameWidth * frameIdx;
	int SrcY = 0;

	Rect rc((int)m_tInfo.fX, (int)m_tInfo.fY, frameWidth, frameHeight);
	Graphics grp(hDC);

	grp.DrawImage(pImg, rc, SrcX, SrcY, frameWidth, frameHeight, UnitPixel);
}

void CPlayer::Release()
{
}
