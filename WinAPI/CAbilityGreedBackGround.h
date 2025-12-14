#pragma once
#include "CUI.h"
class CAbilityGreedBackGround :
    public CUI
{
public:
	CAbilityGreedBackGround();
	virtual ~CAbilityGreedBackGround();
public:
	// CUI을(를) 통해 상속됨
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC hDC) override;

	void Release() override;
private:
	HFONT m_hFont;
};

