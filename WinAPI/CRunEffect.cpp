#include "pch.h"
#include "CRunEffect.h"
#include "CCamera.h"
#include "CResourceMgr.h"
#include "CPlayer.h"
#include "CKeyMgr.h"
CRunEffect::CRunEffect() : m_pOwner(nullptr)
{
}
CRunEffect::CRunEffect(CObj* pOwner)
{
	m_pOwner = pOwner;
}

CRunEffect::~CRunEffect()
{
}

void CRunEffect::Initialize()
{
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Player/RunEffect.bmp", L"RunEffect");
	m_wsFrameKey = L"RunEffect";
	m_iFrameWidth = 48.f;
	m_iFrameHeight = 48.f;
	m_tInfo.fCX = m_iFrameWidth;
	m_tInfo.fCY = m_iFrameHeight;

	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 4;
	m_tFrame.dwSpeed = 100;
	m_tFrame.iMotion = 0;
	m_tFrame.dwTime = GetTickCount();
}

int CRunEffect::Update()
{
	if (dynamic_cast<CPlayer*>(m_pOwner)->IsGround() && dynamic_cast<CPlayer*>(m_pOwner)->Get_State() == CPlayer::WALK)
	{
		//플레이어 따라다님
		if (GET(CKeyMgr)->Get_KeyState('A'))
		{
			m_tInfo.fX = m_pOwner->Get_Info()->fX + m_tInfo.fCX;
			m_tInfo.fY = m_pOwner->Get_Rect()->bottom - m_tInfo.fCY * 0.5f;
			m_tFrame.iMotion = 1;
		}
		else if(GET(CKeyMgr)->Get_KeyState('D'))
		{
			m_tInfo.fX = m_pOwner->Get_Info()->fX - m_tInfo.fCX;
			m_tInfo.fY = m_pOwner->Get_Rect()->bottom - m_tInfo.fCY * 0.5f;
			m_tFrame.iMotion = 0;
		}
		Move_Frame();
		__super::Update_Rect();
	}
    return 0;
}

void CRunEffect::Late_Update()
{
}

void CRunEffect::Render(HDC hDC)
{
	if (dynamic_cast<CPlayer*>(m_pOwner)->Get_State() != CPlayer::WALK || !dynamic_cast<CPlayer*>(m_pOwner)->IsGround())
		return;

	if (g_bDebugMod)
		Rectangle(hDC, m_tRect.left - GET(CCamera)->Get_ScrollX(), m_tRect.top - GET(CCamera)->Get_ScrollY(),
			m_tRect.right - GET(CCamera)->Get_ScrollX(), m_tRect.bottom - GET(CCamera)->Get_ScrollY());
	HDC hMemDC = CResourceMgr::Get_Instance()->Find_Bmp(m_wsFrameKey);

	int SrcX = m_iFrameWidth * m_tFrame.iStart;
	int SrcY = m_iFrameHeight * m_tFrame.iMotion;

	GdiTransparentBlt(
		hDC,
		(int)(m_tRect.left - GET(CCamera)->Get_ScrollX()),			// 복사 받을 공간의 LEFT	
		(int)(m_tRect.top - GET(CCamera)->Get_ScrollY()),				// 복사 받을 공간의 TOP
		m_tInfo.fCX,													// 복사 받을 공간의 가로 
		m_tInfo.fCY,													// 복사 받을 공간의 세로 
		hMemDC,															// 복사 할 DC
		SrcX,															// 원본이미지 left
		SrcY,																// 원본이미지 top
		m_iFrameWidth,													// 원본이미지 가로
		m_iFrameHeight,													// 원본이미지 세로
		RGB(255, 0, 255)
	);
}

void CRunEffect::Release()
{
}
