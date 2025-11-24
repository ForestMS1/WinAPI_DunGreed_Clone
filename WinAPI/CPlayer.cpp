#include "pch.h"
#include "CPlayer.h"
#include "CResourceMgr.h"
#include "CKeyMgr.h"
#include "CCamera.h"
#include "CTimeMgr.h"
CPlayer::CPlayer()
{
}
CPlayer::~CPlayer()
{

}

void CPlayer::Initialize()
{
	m_fSpeed = 10.f;

	m_tInfo.fX = 100.f;
	m_tInfo.fY = 100.f;
	m_tInfo.fCX = 60.f;
	m_tInfo.fCY = 60.f;

	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 2;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 200;
	m_tFrame.dwTime = GetTickCount();

	m_wsFrameKey = L"Player";

	m_eCurState = IDLE;

	GET(CResourceMgr)->Insert_Bmp(L"../Resource/hero.bmp", L"Player");
	//CResourceMgr::Get_Instance()->Insert_Png(L"../Resource/hero.png", L"Player");
}

int CPlayer::Update()
{
	Key_Input();

	Update_Rect();

	Move_Frame();

	return OBJ_NOEVENT;
}

void CPlayer::Late_Update()
{
	Motion_Change();
}

void CPlayer::Render(HDC hDC)
{
	Image* pImage = GET(CResourceMgr)->Find_Png(m_wsFrameKey);

	int frameWidth = 112;
	int frameHeight = 96;

	int SrcX = frameWidth * m_tFrame.iStart;
	int SrcY = frameHeight * m_tFrame.iMotion;

	Graphics grp(hDC);
	
	// 렌더링용 좌표 가져옴
	Vec2 vPos = Vec2(m_tInfo.fX, m_tInfo.fY);
	vPos = GET(CCamera)->GetRenderPos(vPos);
	RECT rRect = GET(CCamera)->GetRenderRect(m_tInfo);

	// 반전 상태에 따라 그리기 설정
	int destWidth = frameWidth;
	int destX = rRect.left;

	HDC hMemDC = GET(CResourceMgr)->Find_Bmp(L"Player");
	HBITMAP hBmp = GET(CResourceMgr)->Get_Bmp(L"Player");

	HBITMAP renderBmp = hBmp;

	if (m_bIsFlipped) // 왼쪽을 볼 때 (반전 상태)
	{
		renderBmp = GET(CResourceMgr)->FlipBitmapHorizontal(hBmp);
	}
	// 오른쪽을 볼 때는 destWidth와 destX가 기본값 (양수 너비)

	Rectangle(hDC, rRect.left, rRect.top, rRect.right, rRect.bottom);

	HBITMAP old = (HBITMAP)SelectObject(hMemDC, renderBmp);

	GdiTransparentBlt(
		hDC,
		(int)vPos.fX,
		(int)vPos.fY,
		frameWidth,
		frameHeight,
		hMemDC,
		SrcX,
		SrcY,
		frameWidth,
		frameHeight,
		RGB(255, 255, 255)
	);

	//GdiTransparentBlt(
	//	hDC,
	//	(int)vPos.fX,				// 복사 받을 공간의 LEFT	
	//	(int)vPos.fY,				// 복사 받을 공간의 TOP
	//	frameWidth,		// 복사 받을 공간의 가로 
	//	frameHeight,			// 복사 받을 공간의 세로 
	//	hMemDC,				// 복사 할 DC
	//	SrcX,
	//	SrcY,
	//	frameWidth,
	//	frameHeight,
	//	RGB(255, 255, 255)
	//);

}

void CPlayer::Release()
{
}

void CPlayer::Key_Input()
{
	if (GET(CKeyMgr)->Key_Down(VK_LEFT) && !m_bIsFlipped)
	{
		m_bIsFlipped = true;
	}
	else if (GET(CKeyMgr)->Key_Down(VK_RIGHT) && m_bIsFlipped)
	{
		m_bIsFlipped = false;
	}
	else if (GET(CKeyMgr)->Key_Pressing(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;
		m_eCurState = WALK;
	}
	else if (GET(CKeyMgr)->Key_Pressing(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;
		m_eCurState = WALK;
	}
	else if (GET(CKeyMgr)->Key_Pressing(VK_UP))
	{
		m_tInfo.fY -= m_fSpeed;
		m_eCurState = WALK;
	}
	else if (GET(CKeyMgr)->Key_Pressing(VK_DOWN))
	{
		m_tInfo.fY += m_fSpeed;
		m_eCurState = WALK;
	}
	else
	{
		m_eCurState = IDLE;
	}
}

void CPlayer::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 2;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 200;
			m_tFrame.dwTime = GetTickCount();
			break;

		case WALK:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 11;
			m_tFrame.iMotion = 1;
			m_tFrame.dwSpeed = 100;
			m_tFrame.dwTime = GetTickCount();
			break;

		//case ATTACK:
		//	m_tFrame.iStart = 0;
		//	m_tFrame.iEnd = 5;
		//	m_tFrame.iMotion = 2;
		//	m_tFrame.dwSpeed = 200;
		//	m_tFrame.dwTime = GetTickCount();
		//	break;

		//case HIT:
		//	m_tFrame.iStart = 0;
		//	m_tFrame.iEnd = 1;
		//	m_tFrame.iMotion = 3;
		//	m_tFrame.dwSpeed = 200;
		//	m_tFrame.dwTime = GetTickCount();
		//	break;

		//case DEAD:
		//	m_tFrame.iStart = 0;
		//	m_tFrame.iEnd = 3;
		//	m_tFrame.iMotion = 4;
		//	m_tFrame.dwSpeed = 200;
		//	m_tFrame.dwTime = GetTickCount();
		//	break;
		default:
			break;
		}

		m_ePreState = m_eCurState;
	}

}
