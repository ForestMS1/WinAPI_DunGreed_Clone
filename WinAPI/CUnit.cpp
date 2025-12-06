#include "pch.h"
#include "CUnit.h"

CUnit::CUnit() : m_bIsHit(false), m_dwLastHitTime(GetTickCount())
{
}

CUnit::~CUnit()
{
	Release();
}

void CUnit::Initialize()
{
}

int CUnit::Update()
{
	return 0;
}

void CUnit::Late_Update()
{
}

void CUnit::Render(HDC hDC)
{
}

void CUnit::Release()
{
}
