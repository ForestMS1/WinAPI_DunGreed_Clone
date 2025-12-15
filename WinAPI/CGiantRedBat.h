#pragma once
#include "CEnemy.h"
class CGiantRedBat :
    public CEnemy
{
public:
    CGiantRedBat();
    ~CGiantRedBat();
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
    DWORD m_dwAttackDelay;

    DWORD m_dwBulletSpawnTime;
    float m_fBulletSpawnAngle;
    float m_fBulletShootAngle;

    bool m_bPlaySound;

    int m_iShootCount;
};

