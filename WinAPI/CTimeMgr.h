#pragma once
#include "Define.h"
class CTimeMgr
{
	SINGLE(CTimeMgr)

public:
	void Initialize();
	void Update();

	float GetDeltaTime() const { return m_fDeltaTime; }
private:
	LARGE_INTEGER m_llFrequency; // CPU Å¬·° ºóµµ ¼ö
	LARGE_INTEGER m_llPrevCount;
	LARGE_INTEGER m_llCurCount;

	float m_fDeltaTime;
};

