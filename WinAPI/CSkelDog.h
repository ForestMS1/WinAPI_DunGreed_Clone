#pragma once
#include "CEnemy.h"
class CSkelDog :
    public CEnemy
{
public:
    CSkelDog();
    ~CSkelDog();
    // CEnemy을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
private:
    void Motion_Change() override;
    void Attack_CircleBullet();
    void Jump();
private:
    int m_iAttack;

    DWORD m_dwAttackDelay;
};

