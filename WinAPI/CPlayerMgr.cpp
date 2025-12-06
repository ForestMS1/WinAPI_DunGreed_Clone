#include "pch.h"
#include "CPlayerMgr.h"

CPlayerMgr* CPlayerMgr::m_pInstance = nullptr;

CPlayerMgr::CPlayerMgr()
{

}
CPlayerMgr::~CPlayerMgr()
{
	Release();
}

void CPlayerMgr::Initialize()
{
	if (!GET(CObjMgr)->GetObjLayer(OBJ_PLAYER).empty())
		m_pPlayer = GET(CObjMgr)->GetObjLayer(OBJ_PLAYER).front();
}

void CPlayerMgr::Update()
{

}

void CPlayerMgr::Late_Update()
{

}

void CPlayerMgr::Render(HDC hDC)
{

}
void CPlayerMgr::Release()
{

}