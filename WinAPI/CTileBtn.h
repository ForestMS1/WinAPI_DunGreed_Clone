#pragma once
#include "CUI.h"
class CTileBtn :
    public CUI
{
public:
    CTileBtn();
    ~CTileBtn();
public:
    // CUI을(를) 통해 상속됨
    void Initialize() override;
    void Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
private:
    INFO m_CurTileInfo;
    RECT m_CurTileRect;
    int	 m_iCurTileX;
    int	 m_iCurTileY;
};

