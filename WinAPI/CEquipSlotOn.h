#pragma once
#include "CUI.h"
#include "CWeaponBtn1.h"
class CEquipSlotOn :
    public CUI
{
public:
	enum EquipState {};
public:
	CEquipSlotOn();
	CEquipSlotOn(CUI* pParentUI);
	virtual ~CEquipSlotOn();
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
	bool   m_bMouseOn;
	bool   m_bClicked;
	CWeaponBtn1 m_pWeaponBtn1;
};

