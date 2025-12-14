#pragma once
#include "CUI.h"
class CPaper :
    public CUI
{
public:
	CPaper();
	virtual ~CPaper();
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

