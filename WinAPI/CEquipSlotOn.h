#pragma once
#include "CUI.h"
class CEquipSlotOn :
    public CUI
{
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
	CItem* m_pItem;
};

