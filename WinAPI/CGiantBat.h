#pragma once
#include "CEnemy.h"
class CGiantBat :
    public CEnemy
{
private:
    enum STATE {SPAWN, IDLE, ATTACK, DEAD, END};
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
    STATE m_ePreState;
    STATE m_eCurState;


    DWORD m_dwAttackTick;
    DWORD spawnTick;

    DWORD m_dwSpawnTime;
};

