#pragma once
#include "CEnemy.h"
class CGiantBat :
    public CEnemy
{
public:
    CGiantBat();
    ~CGiantBat();
    // CEnemy을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
private:
    void Motion_Change() override;
    void Attack_CircleBullet();
private:

    DWORD m_dwAttackTick;

    DWORD m_dwBulletSpawnTime;
    float m_fBulletSpawnAngle;
    float m_fBulletShootAngle;
};

