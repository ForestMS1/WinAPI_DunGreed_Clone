#pragma once
#include "CUI.h"
class CWeaponBtn1 :
    public CUI
{
public:
	CWeaponBtn1();
	CWeaponBtn1(CUI* pParentUI);
	virtual ~CWeaponBtn1();
public:
	// CUI을(를) 통해 상속됨
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC hDC) override;

	void Release() override;
private:
	void Cliked();
private:
	CItem* m_pEquipedItem;
	bool   m_bMouseOn;
	bool   m_bClicked;
};

