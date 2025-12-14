#pragma once
#include "CUI.h"
class CAbilityWrathBackGround :
	public CUI
{
public:
	CAbilityWrathBackGround();
	virtual ~CAbilityWrathBackGround();
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

