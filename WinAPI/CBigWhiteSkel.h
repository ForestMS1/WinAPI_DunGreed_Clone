#pragma once
#include "CEnemy.h"
class CBigWhiteSkel :
    public CEnemy
{
public:
    CBigWhiteSkel();
    ~CBigWhiteSkel();
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
    bool m_bJump;
    float				m_v0;	 // 점프 초기속력
    float				m_ft;	 // 흐르는 시간
    float				m_fAcct; // 점프 누적 시간
};

