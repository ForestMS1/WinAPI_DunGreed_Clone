#pragma once
#include "CObj.h"
class CSwingFX :
    public CObj
{
public:
    CSwingFX();
    ~CSwingFX();
    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
    CSwingFX* Clone() { return new CSwingFX(*this); }
private:
    float m_fAngle;
};

