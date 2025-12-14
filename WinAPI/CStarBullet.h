#pragma once
#include "CPlayerBullet.h"
class CStarBullet :
    public CPlayerBullet
{
    enum STATE { IDLE, DEAD, END };
public:
    CStarBullet();
    virtual~CStarBullet();
public:
    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
private:
    void Motion_Change();
private:
    STATE m_eCurState;
    STATE m_ePreState;
};

