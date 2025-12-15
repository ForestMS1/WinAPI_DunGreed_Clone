#pragma once
#include "CObj.h"
class CTorch :
    public CObj
{
public:
    CTorch();
    ~CTorch();
public:
    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};

