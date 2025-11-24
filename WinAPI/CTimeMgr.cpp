#include "pch.h"
#include "CTimeMgr.h"

CTimeMgr* CTimeMgr::m_pInstance = nullptr;

CTimeMgr::CTimeMgr()
{

}
CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::Initialize()
{
	QueryPerformanceFrequency(&m_llFrequency);

	QueryPerformanceCounter(&m_llPrevCount);
}

void CTimeMgr::Update()
{
	QueryPerformanceCounter(&m_llCurCount);

	long long llTimeDelta = m_llCurCount.QuadPart - m_llPrevCount.QuadPart;

	m_fDeltaTime = (float)((double)llTimeDelta / m_llFrequency.QuadPart);

	m_llPrevCount = m_llCurCount;
}
