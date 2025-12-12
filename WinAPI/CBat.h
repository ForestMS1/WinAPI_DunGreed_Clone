#pragma once
#include "CEnemy.h"
class CBat :
    public CEnemy
{
public:
    CBat();
    ~CBat();
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
};

