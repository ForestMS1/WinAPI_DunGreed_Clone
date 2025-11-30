#include "pch.h"
#include "CCamera.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

CCamera* CCamera::m_pInstance = nullptr;

CCamera::CCamera() : m_pTarget(nullptr), m_fTime(1.f),
m_fSpeed(0.f), m_fAccTime(0.f)
{

}

CCamera::~CCamera()
{

}
void CCamera::Initialize()
{
	m_vLookAt.fX = WINCX >> 1;
	m_vLookAt.fY = WINCY >> 1;
}
void CCamera::Update()
{
	if (m_pTarget)
	{
		if (m_pTarget->IsDead())
			m_pTarget = nullptr;
		else
		{
			m_vLookAt = m_pTarget->Get_Pos();
		}
	}
	

	// 화면 중앙좌표와 카메라 LookAt 좌표간의 차이값 계산
	CalDiff();
}

void CCamera::CalDiff()
{
	// 이전 LookAt과 현재 LooK의 차이값을 보정해서 현재의 LookAt을 구한다
	m_fAccTime += DT;

	if (m_fAccTime >= m_fTime)
	{
		m_vCurLookAt = m_vLookAt;
	}
	else
	{
		Vec2 vLookDir = m_vLookAt - m_vPrevLookAt; // 쫓아갈 방향 벡터
		m_vCurLookAt = m_vPrevLookAt + vLookDir.Normalize() * m_fSpeed * DT; // 따라가는 중
	}


	Vec2 vCenter = Vec2(WINCX >> 1, WINCY >> 1);

	m_vDiff = m_vCurLookAt - vCenter;

	//Scroll Lock
	if (m_vDiff.fX < 0)
	{
		m_vDiff.fX = 0;
		m_vLookAt.fX = vCenter.fX;
	}
	if (m_vDiff.fY < 0)
	{
		m_vDiff.fY = 0;
		m_vLookAt.fY = vCenter.fY;
	}
	//if (1920 - WINCX < m_vDiff.fX)
	if (TILEX * TILECX - WINCX < m_vDiff.fX)
	{
		m_vDiff.fX = TILEX * TILECX - WINCX;
		m_vLookAt.fX = TILEX * TILECX - (WINCX >> 1);
	}
	if (TILEY * TILECY - WINCY < m_vDiff.fY)
	{
		m_vDiff.fY = TILEY * TILECY - WINCY;
		m_vLookAt.fY = TILEY * TILECY - (WINCY >> 1);
	}

	m_vPrevLookAt = m_vCurLookAt;
}