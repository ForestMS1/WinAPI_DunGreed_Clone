#pragma once
#include "CUI.h"
class CTileOptionBtn :
    public CUI
{
public:
    CTileOptionBtn(float fX, float fY);
    ~CTileOptionBtn();
public:
    // CUI을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
private:
    int	 m_iOption;
    bool m_bMouseOn;
};

