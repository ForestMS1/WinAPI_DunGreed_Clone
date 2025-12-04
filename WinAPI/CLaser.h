#pragma once
#include "CEnemy.h"
class CLaser :
    public CEnemy
{
public:
    CLaser();
    CLaser(CEnemy* pHand, bool isR);
    ~CLaser();
public:
    // CEnemy을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
    void Motion_Change() override;

public:
    void SetActive(bool act) { isActive = act; if (act == false) { isAttack = false; m_iCurAttackCount = 0; } }
    bool GetActive()    const { return isActive; }
private:
    void Shoot();
private:
    CEnemy* m_pOwner;

    BELIAL_STATE m_ePreState;
    BELIAL_STATE m_eCurState;

    CObj* m_pTarget;
    bool    isActive;
    bool    isAttack;
    bool    isRight;
    DWORD   m_dwDelay; // ATTACK_HAND 상태가 되고 Delay 후에 레이저 발사

    // 공격력
    float			m_fDamage;
    int				m_iMaxAttackCount; // 무기의 한번에 줄 수 있는 최대 공격횟수
    int				m_iCurAttackCount; // 데미지 준 횟수
};

