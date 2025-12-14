#include "pch.h"
#include "CPlayerMgr.h"
#include "CPlayer.h"
#include "CCosmosSword.h"
#include "CGatlingGun.h"
CPlayerMgr* CPlayerMgr::m_pInstance = nullptr;

CPlayerMgr::CPlayerMgr() : m_bIsFirstSet(true), m_fMaxHp(100.f), m_fCurHp(100.f), m_iGold(3000)
, m_fMaxSatiety(100.f), m_fCurSatiety(0.f), m_iAddMaxHp(0.f), m_iAddDef(0.f), m_iAddGreed(0.f)
{
	m_pPlayer = nullptr;
	m_vecItem = vector<CItem*>(15, nullptr);
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
	if(m_pPlayer != nullptr)
		dynamic_cast<CPlayer*>(m_pPlayer)->SetGold(m_iGold);
	if (m_pPlayer != nullptr)
		dynamic_cast<CPlayer*>(m_pPlayer)->SetGold(m_iGold);
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

	for (auto iter : m_vecItem)
	{
		Safe_Delete(iter);
	}
	m_vecItem.clear();
}

void CPlayerMgr::EquipWeapon(CItem* pItem, wstring key)
{
	Safe_Delete(m_mapPlayerEquiped[key]);
	m_mapPlayerEquiped[key] = pItem;

	GET(CSoundMgr)->PlaySoundW(L"Equip.wav", SOUND_EFFECT, 1.0f);

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
	GET(CSoundMgr)->PlaySoundW(L"Swap_weapon.wav", SOUND_EFFECT, 1.0f);
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
