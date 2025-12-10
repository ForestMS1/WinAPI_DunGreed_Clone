#pragma once
#include "CUI.h"
class CPlayerHpBar :
    public CUI
{
public:
    CPlayerHpBar();
    ~CPlayerHpBar();
public:
    // CUI을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
private:
    float m_fMaxHp;
    float m_fCurHp;
    HFONT m_hFont;
};

