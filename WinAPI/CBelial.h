#pragma once
#include "CEnemy.h"
class CBelial :
    public CEnemy
{
public:
    enum STATE { IDLE, ATTACK_ROTATE, ATTACK_HAND, ATTACK_SPEAR, DEAD, STATE_END };
public:
    CBelial();
    ~CBelial();
    // CEnemy을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    STATE GetCurState() const { return m_eCurState; }
private:
    void Motion_Change() override;
private:
    STATE m_ePreState;
    STATE m_eCurState;
};

