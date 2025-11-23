#include "pch.h"
#include "CPlayer.h"
#include "CResourceMgr.h"
#include "CKeyMgr.h"

CPlayer::CPlayer() : m_bIsFlipped(true), m_pImg(nullptr)
{
}
CPlayer::~CPlayer()
{

}

void CPlayer::Initialize()
{
	m_fSpeed = 4.f;

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

	CResourceMgr::Get_Instance()->Insert_Png(L"../Resource/hero.png", L"Player");
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
	m_pImg = GET(CResourceMgr)->Find_Png(m_wsFrameKey);

	int frameWidth = 112;
	int frameHeight = 96;

	int SrcX = frameWidth * m_tFrame.iStart;
	int SrcY = frameHeight * m_tFrame.iMotion;

	Graphics grp(hDC);
	
	// 반전 상태에 따라 그리기 설정
	int destWidth = frameWidth;
	int destX = (int)m_tInfo.fX;

	if (!m_bIsFlipped) // 왼쪽을 볼 때 (반전 상태)
	{
		// 대상 너비를 음수로 설정하여 좌우 반전
		destWidth = -frameWidth;
		// X 좌표는 캐릭터 위치에서 프레임 너비만큼 더해줘야 올바른 위치에 그려짐
		destX = (int)m_tInfo.fX + frameWidth;
	}
	// 오른쪽을 볼 때는 destWidth와 destX가 기본값 (양수 너비)

	// DrawImage 오버로드 함수 사용 (원본 픽셀을 대상 영역에 복사)
	grp.DrawImage(
		m_pImg,
		Rect(destX, (int)m_tInfo.fY, destWidth, frameHeight), // 대상 영역 (X, Y, Width, Height)
		SrcX,                                                // 원본 시작 X
		SrcY,                                                // 원본 시작 Y
		frameWidth,                                          // 원본 너비
		frameHeight,                                         // 원본 높이
		UnitPixel,                                           // 단위
		nullptr,                                             // ImageAttributes (NULL)
		nullptr                                              // GdiplusNativeWindow (NULL)
	);
}

void CPlayer::Release()
{
}

void CPlayer::Key_Input()
{
	if (GET(CKeyMgr)->Key_Down(VK_LEFT) && m_bIsFlipped)
	{
		m_bIsFlipped = false;
	}
	if (GET(CKeyMgr)->Key_Down(VK_RIGHT) && !m_bIsFlipped)
	{
		m_bIsFlipped = true;
	}
	if (GET(CKeyMgr)->Key_Pressing(VK_LEFT))
	{
		m_tInfo.fX -= m_fSpeed;
		m_eCurState = WALK;
	}
	if (GET(CKeyMgr)->Key_Pressing(VK_RIGHT))
	{
		m_tInfo.fX += m_fSpeed;
		m_eCurState = WALK;
	}
	if (GET(CKeyMgr)->Key_Pressing(VK_UP))
	{
		m_tInfo.fY -= m_fSpeed;
		m_eCurState = WALK;
	}
	if (GET(CKeyMgr)->Key_Pressing(VK_DOWN))
	{
		m_tInfo.fY += m_fSpeed;
		m_eCurState = WALK;
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
