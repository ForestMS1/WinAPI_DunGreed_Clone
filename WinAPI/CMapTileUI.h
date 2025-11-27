#pragma once
#include "CUI.h"
class CMapTileUI : public CUI
{
public:
	CMapTileUI();
	~CMapTileUI();
public:
	// CUI을(를) 통해 상속됨
	void Initialize() override;

	void Update() override;

	void Late_Update() override;

	void Render(HDC hDC) override;

	void Release() override;

public:
	void Set_TileIdx(int iX, int iY) { m_iCurTileX = iX; m_iCurTileY = iY; }
private:
	INFO m_CurTileInfo;
	RECT m_CurTileRect;
	int	 m_iCurTileX;
	int	 m_iCurTileY;
};

