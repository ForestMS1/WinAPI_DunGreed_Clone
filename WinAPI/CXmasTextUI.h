#pragma once
#include "CUI.h"
class CXmasTextUI :
    public CUI
{
public:
	CXmasTextUI();
	virtual ~CXmasTextUI();
public:
	// CUI을(를) 통해 상속됨
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC hDC) override;

	void Release() override;
private:
	void Key_Input();
private:
	HFONT m_hFont;
	vector<wstring> m_vecText;
	UINT m_TextIdx;
	bool m_bCompleteGift;
};

