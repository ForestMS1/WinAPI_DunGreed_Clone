#pragma once
#include "CEnemyBullet.h"
class CBelialBullet :
    public CEnemyBullet
{
private:
    enum STATE { IDLE, DEAD, END };
public:
    CBelialBullet();
    virtual~CBelialBullet();
public:
    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void Motion_Change();
private:
    STATE m_eCurState;
    STATE m_ePreState;
};

