#pragma once
#include "CUI.h"
class CInventoryUI :
    public CUI
{
public:
	CInventoryUI();
	CInventoryUI(CObj* pPlayer);
	virtual ~CInventoryUI();
public:
	// CUI을(를) 통해 상속됨
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC hDC) override;

	void Release() override;

	CObj* GetPlayer() const { return m_pPlayer; }
private:
	void Key_Input();
private:
	CObj* m_pPlayer;
};

