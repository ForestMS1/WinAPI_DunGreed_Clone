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
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/Font/DamageFont.bmp", L"DamageFont");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/Font/GoldFont.bmp", L"GoldFont");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/UI/Font/G.bmp", L"G");
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
