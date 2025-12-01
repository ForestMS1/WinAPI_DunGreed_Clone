#pragma once
#include "CUI.h"
class CPlayerUI :
    public CUI
{
public:
	CPlayerUI();
    CPlayerUI(CObj* pPlayer);
    virtual ~CPlayerUI();
public:
	// CUI을(를) 통해 상속됨
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC hDC) override;

	void Release() override;

	CObj* GetPlayer() const { return m_pPlayer; }
private:
	CObj* m_pPlayer;
};

