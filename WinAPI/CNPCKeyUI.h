#pragma once
#include "CUI.h"
class CNPCKeyUI :
    public CUI
{
public:
    CNPCKeyUI(CObj* pOwner);
    ~CNPCKeyUI();
public:
    // CUI을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
private:
    CObj* m_pOwner;
};

