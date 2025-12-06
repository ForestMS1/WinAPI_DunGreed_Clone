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
private:
	CObj* m_pPlayer;
	map<wstring, CItem*> m_mapPlayerEquiped;
};

