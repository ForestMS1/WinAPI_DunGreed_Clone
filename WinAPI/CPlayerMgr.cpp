#include "pch.h"
#include "CPlayerMgr.h"
#include "CPlayer.h"
#include "CCosmosSword.h"
#include "CGatlingGun.h"
CPlayerMgr* CPlayerMgr::m_pInstance = nullptr;

CPlayerMgr::CPlayerMgr() : m_bIsFirstSet(true)
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
	m_mapPlayerEquiped.insert({ L"Shiled1", nullptr });
	m_mapPlayerEquiped.insert({ L"Weapon2", nullptr });
	m_mapPlayerEquiped.insert({ L"Shiled2", nullptr });
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

void CPlayerMgr::EquipWeapon(CItem* pItem, wstring key)
{
	Safe_Delete(m_mapPlayerEquiped[key]);
	m_mapPlayerEquiped[key] = pItem;
	if(pItem == nullptr)
		dynamic_cast<CPlayer*>(m_pPlayer)->Set_Weapon(nullptr);

	if (dynamic_cast<CPlayer*>(m_pPlayer)->Get_EquipWeapon() == nullptr)
	{
		if (key == L"Weapon1")
		{
			m_bIsFirstSet = true;
		}
		else if (key == L"Weapon2")
		{
			m_bIsFirstSet = false;
		}
		if (pItem != nullptr)
		{
			dynamic_cast<CPlayer*>(m_pPlayer)->Set_Weapon(m_mapPlayerEquiped[key]->Clone());
			m_mapPlayerEquiped[key]->Initialize();
		}
		else
		{
			dynamic_cast<CPlayer*>(m_pPlayer)->Set_Weapon(nullptr);
		}
	}
}

void CPlayerMgr::SetChange()
{
	m_bIsFirstSet = !m_bIsFirstSet;

	if (m_bIsFirstSet)
	{
		if (m_mapPlayerEquiped[L"Weapon1"] != nullptr)
		{
			dynamic_cast<CPlayer*>(m_pPlayer)->Set_Weapon(m_mapPlayerEquiped[L"Weapon1"]->Clone());
			m_mapPlayerEquiped[L"Weapon1"]->Initialize();
		}
		else
		{
			dynamic_cast<CPlayer*>(m_pPlayer)->Set_Weapon(nullptr);
		}
	}
	else
	{
		if (m_mapPlayerEquiped[L"Weapon2"] != nullptr)
		{
			dynamic_cast<CPlayer*>(m_pPlayer)->Set_Weapon(m_mapPlayerEquiped[L"Weapon2"]->Clone());
			m_mapPlayerEquiped[L"Weapon2"]->Initialize();
		}
		else
		{
			dynamic_cast<CPlayer*>(m_pPlayer)->Set_Weapon(nullptr);
		}
	}
}
