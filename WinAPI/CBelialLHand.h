#pragma once
#include "CEnemy.h"
#include "CLaser.h"
class CBelialLHand :
    public CEnemy
{
public:
    CBelialLHand();
    CBelialLHand(CEnemy* pBelial);
    ~CBelialLHand();
public:

    // CEnemy을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
    void Motion_Change() override;

    void SetActive(bool act) { m_isActive = act; }
private:
    void MoveToPlayer();
private:
    CEnemy* m_pOwner;
    CLaser* m_pLaser;
    BELIAL_STATE m_ePreState;
    BELIAL_STATE m_eCurState;

    float   m_fAtackDuration;
    float   m_fMoveDuration;
    bool    m_isActive;
    bool    m_bMoveEnd;
    float   diffY;
};

