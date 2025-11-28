#pragma once
#include "CUI.h"
class CTileBtn :
    public CUI
{
public:
    CTileBtn(float fX, float fY);
    ~CTileBtn();
public:
    // CUI을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
private:
    int	 m_iCurTileX;
    int	 m_iCurTileY;
};

