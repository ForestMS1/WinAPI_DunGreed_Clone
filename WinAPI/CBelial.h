#pragma once
#include "CEnemy.h"
#include "CBelialRHand.h"
#include "CBelialLHand.h"
#include "SpearMgr.h"

class CBelial :
    public CEnemy
{
public:
    CBelial();
    ~CBelial();
    // CEnemy을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    BELIAL_STATE GetCurState() const { return m_eCurState; }
private:
    void Motion_Change() override;
    void Attack_Rotate();
    void Attack_Hand();
private:
    BELIAL_STATE m_ePreState;
    BELIAL_STATE m_eCurState;

    //스읍... 이게 맞나 너무 하드코딩같지만 일단 끼워
    CBelialRHand* m_pRHand;
    CBelialLHand* m_pLHand;

    //spear
    SpearMgr* m_pSpearMgr;


    //패턴 바뀌는 시간
    DWORD m_dwChangePattern;

    DWORD m_dwRotateAttackTick;
    DWORD m_dwHandAttackTick;

    bool HandAttack;
    bool isRightHandOn;

    DWORD m_SpawnEffectStartTime;
    bool m_bPlayBossBGM;
};

