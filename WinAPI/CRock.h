#pragma once
#include "CUI.h"
class CRock :
    public CUI
{
public:
	CRock();
	virtual ~CRock();
public:
	// CUI을(를) 통해 상속됨
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC hDC) override;

	void Release() override;
private:
	void Clicked();
private:
	bool   m_bMouseOn;
};

