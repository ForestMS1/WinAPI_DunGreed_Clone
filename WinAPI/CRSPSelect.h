#pragma once
#include "CUI.h"
class CRSPSelect :
    public CUI
{
public:
    CRSPSelect();
    ~CRSPSelect();
public:
    // CUI을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};

