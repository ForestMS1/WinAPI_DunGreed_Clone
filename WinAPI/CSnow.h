#pragma once
#include "CObj.h"
class CSnow :
    public CObj
{
public:
    CSnow();
    ~CSnow();
public:
    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
    
    void SetSpeed(float speed) { m_fSpeed = speed; }
};

