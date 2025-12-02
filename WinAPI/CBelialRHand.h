#pragma once
#include "CEnemy.h"
class CBelialRHand :
    public CEnemy
{
public:
    CBelialRHand();
    CBelialRHand(CEnemy* pBelial);
    ~CBelialRHand();
public:
    // CEnemy을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
    void Motion_Change() override;
private:
    CEnemy* m_pOwner;

    BELIAL_STATE m_ePreState;
    BELIAL_STATE m_eCurState;
};

