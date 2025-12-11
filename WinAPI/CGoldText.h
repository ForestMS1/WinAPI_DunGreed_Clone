#pragma once
#include "CObj.h"
class CGoldText :
    public CObj
{
public:
    CGoldText(int gold, float fX, float fY);
    ~CGoldText();
public:
    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

private:
    int   m_iGold;
    DWORD m_dwSpawnTime; // 생성된 시간
    DWORD m_dwLifeTime = 1000;
    float m_fSpeed;

    float m_ft;
};

