#pragma once
#include "CUI.h"
class CMapTileOptionUI :
    public CUI
{
public:
	CMapTileOptionUI();
	~CMapTileOptionUI();
public:
	// CUI을(를) 통해 상속됨
	void Initialize() override;

	int Update() override;

	void Late_Update() override;

	void Render(HDC hDC) override;

	void Release() override;

public:
	bool IsMouseOn() { return m_bMouseOn; }
private:
	void Key_Input();
private:
	bool m_bMouseOn;
	int  m_iScrollX;
};

