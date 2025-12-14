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

	void AddItem(CItem* pItem) { if (pItem != nullptr) { m_vecItem.push_back(pItem->Clone()); } }
	vector<CItem*>& GetItemVec() { return m_vecItem; }
	void SetMaxHp(float MaxHp) { m_fMaxHp = MaxHp; }
	void SetCurHp(float CurHp) { m_fCurHp = CurHp; }
	void SetGold(float gold) { m_iGold = gold; }
	void SetMaxSatiety(float maxSatiety) { m_fMaxSatiety = maxSatiety; }
	void SetCurSatiety(float curSatiety) { m_fCurSatiety = curSatiety; }
	void GetDropGold(int gold) { m_iGold += gold; }


	float GetMaxHp() const { return m_fMaxHp; }
	float GetCurHp() const { return m_fCurHp; }
	int	  GetGold() const { return m_iGold; }
	float GetMaxSatiety() const { return m_fMaxSatiety; }
	float GetCurSatiety() const { return m_fCurSatiety; }

	int GetAddMaxHp() const { return m_iAddMaxHp; }
	int GetAddDef() const { return m_iAddDef; }
	int GetAddGreed() const { return m_iAddGreed; }
	int GetAddMaxDashCount() const { return m_iAddMaxDashCount; }
	void SetAddMaxHp(int addMaxHp) { m_iAddMaxHp += addMaxHp; }
	void SetAddDef(int addDef) { m_iAddDef += addDef; }
	void SetAddGreed(int addGreed) { m_iAddGreed += addGreed; }
	void SetAddMaxDashCount(int addDashCount) { m_iAddMaxDashCount += addDashCount; }
private:
	CObj* m_pPlayer;
	map<wstring, CItem*> m_mapPlayerEquiped;
	bool	m_bIsFirstSet;

	
	//플레이어에 상태 저장
	float m_fMaxHp;
	float m_fCurHp;
	int	  m_iGold;
	float m_fMaxSatiety;
	float m_fCurSatiety;
	vector<CItem*> m_vecItem;

	//추가 스탯
	int m_iAddMaxHp;
	int m_iAddDef;
	int m_iAddGreed;
	int m_iAddMaxDashCount;
};

