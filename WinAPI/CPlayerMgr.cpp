#include "pch.h"
#include "CPlayerMgr.h"
#include "CPlayer.h"
#include "CCosmosSword.h"
#include "CGatlingGun.h"
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

	//CItem* pWeapon = new CCosmosSword;
	//pWeapon->Initialize();
	m_mapPlayerEquiped.insert({ L"Weapon1", nullptr });
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
	for (auto iter : m_mapPlayerEquiped)
	{
		Safe_Delete<CItem*>(iter.second);
	}
	m_mapPlayerEquiped.clear();
}

void CPlayerMgr::EquipWeapon(CItem* pItem)
{
	Safe_Delete(m_mapPlayerEquiped[L"Weapon1"]);
	m_mapPlayerEquiped[L"Weapon1"] = pItem;
	if (pItem != nullptr)
	{
		dynamic_cast<CPlayer*>(m_pPlayer)->Set_Weapon(m_mapPlayerEquiped[L"Weapon1"]->Clone());
		m_mapPlayerEquiped[L"Weapon1"]->Initialize();
	}
	else
	{
		dynamic_cast<CPlayer*>(m_pPlayer)->Set_Weapon(nullptr);
	}
}
