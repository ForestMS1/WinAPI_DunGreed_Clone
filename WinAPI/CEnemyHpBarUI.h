#pragma once
#include "CUI.h"
class CEnemyHpBarUI :
    public CUI
{
public:
    CEnemyHpBarUI(CObj* pOwner);
    ~CEnemyHpBarUI();
public:
    // CUI을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
private:
    CObj* m_pOwner;
    float m_fMaxHp;
    float m_fCurHp;
};

