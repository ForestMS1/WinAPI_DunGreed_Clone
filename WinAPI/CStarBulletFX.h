#pragma once
#include "CObj.h"
class CStarBulletFX :
    public CObj
{
public:
    CStarBulletFX(float fX, float fY);
    ~CStarBulletFX();
public:
    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

private:
    DWORD m_dwSpawnTime; // 생성된 시간
    DWORD m_dwLifeTime = 1000;
    BYTE m_bAlpha;
    float m_ft;
};

