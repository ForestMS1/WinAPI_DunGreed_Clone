#pragma once
class CPlayerMgr
{
	SINGLE(CPlayerMgr)

public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render(HDC hDC);
	void Release();

	void SetPlayer(CObj* pPlayer) { m_pPlayer = pPlayer; }
	CObj* GetPlayer() const { return m_pPlayer; }

	void EquipWeapon(CItem* pItem);
	CItem* GetEquip(wstring key) const 
	{ 
		if (m_mapPlayerEquiped.find(key) == m_mapPlayerEquiped.end())
			return nullptr;
		return m_mapPlayerEquiped.find(key)->second; 
	}
private:
	CObj* m_pPlayer;
	map<wstring, CItem*> m_mapPlayerEquiped;
};

