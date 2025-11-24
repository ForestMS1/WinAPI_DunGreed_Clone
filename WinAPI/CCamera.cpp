#include "pch.h"
#include "CCamera.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

CCamera* CCamera::m_pInstance = nullptr;

CCamera::CCamera() : m_pTarget(nullptr), m_fTime(0.5f),
m_fSpeed(0.f), m_fAccTime(0.f)
{

}

CCamera::~CCamera()
{

}

void CCamera::Update()
{
	if (m_pTarget)
	{
		if (m_pTarget->IsDead())
			m_pTarget = nullptr;
		else
			m_vLookAt = m_pTarget->Get_Pos();
	}

	//if (GET(CKeyMgr)->Key_Pressing('D'))
	//{
	//	m_vLookAt.fX += 5.f;
	//}
	//if (GET(CKeyMgr)->Key_Pressing('A'))
	//{
	//	m_vLookAt.fX -= 5.f;
	//}
	//if (GET(CKeyMgr)->Key_Pressing('W'))
	//{
	//	m_vLookAt.fY -= 5.f;
	//}
	//if (GET(CKeyMgr)->Key_Pressing('S'))
	//{
	//	m_vLookAt.fY += 5.f;
	//}


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
	m_vPrevLookAt = m_vCurLookAt;
}
