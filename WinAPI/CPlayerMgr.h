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

	void EquipWeapon(CItem* pItem , wstring key);
	CItem* GetEquip(wstring key) const 
	{ 
		if (m_mapPlayerEquiped.find(key) == m_mapPlayerEquiped.end())
			return nullptr;
		return m_mapPlayerEquiped.find(key)->second; 
	}

	
	void SetChange();
	bool IsFirstSet() const { return m_bIsFirstSet; }
private:
	CObj* m_pPlayer;
	map<wstring, CItem*> m_mapPlayerEquiped;
	bool	m_bIsFirstSet;
};

