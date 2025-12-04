#pragma once
#include "CEnemy.h"
class CBelialSpear :
    public CEnemy
{
public:
    CBelialSpear();
    CBelialSpear(CEnemy* pBelial);
    ~CBelialSpear();
public:
    // CEnemy을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
    void Motion_Change() override;

public:
    void SetActive(bool act) { isActive = act; if (act == false) { isAttack = false; isGround = false; m_iCurAttackCount = 0; } }
    void SetEffect(bool eft) { onEffect = eft; }
    bool GetActive()    const { return isActive; }
private:
    void Shoot();
private:
    CEnemy* m_pOwner;

    BELIAL_STATE m_ePreState;
    BELIAL_STATE m_eCurState;

    CObj*   m_pTarget;
    float   m_fAngle;
    float   m_fShootAngle;
    bool    isActive;
    bool    isAttack;
    bool    onEffect; // 소환 이펙트 출력 가능한상태 = true, else false
    bool    isGround; // 땅에 박힘
    DWORD   m_dwDelay;

    // 공격력
    float			m_fDamage;
    int				m_iMaxAttackCount; // 무기의 한번에 줄 수 있는 최대 공격횟수
    int				m_iCurAttackCount; // 데미지 준 횟수
};

