#pragma once
#include "CObj.h"
class CCosSwingFX :
    public CObj
{
public:
    CCosSwingFX();
    ~CCosSwingFX();
    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
    CCosSwingFX* Clone() { return new CCosSwingFX(*this); }
private:
    float m_fAngle;
};

