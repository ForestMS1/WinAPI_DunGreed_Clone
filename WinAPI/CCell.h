#pragma once
#include "CUI.h"
#include "CItem.h"
class CCell :
    public CUI
{
public:
	CCell(UINT idx);
	CCell(CUI* pParentUI);
	virtual ~CCell();
public:
	// CUI을(를) 통해 상속됨
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC hDC) override;

	void Release() override;

	void SetItem(CItem* pItem) {/*if(m_pItem == nullptr)*/ Safe_Delete(m_pItem); m_pItem = pItem; }
	CItem* GetItem() const { return m_pItem; }
private:
	void Clicked();
private:
	CItem* m_pItem;
	bool   m_bMouseOn;
	UINT   m_iIndex;
};

