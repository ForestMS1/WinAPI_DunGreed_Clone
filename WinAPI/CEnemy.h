#pragma once
#include "CObj.h"

enum BELIAL_STATE { IDLE, ATTACK_ROTATE, ATTACK_HAND, ATTACK_SPEAR, DEAD, STATE_END };


class CEnemy :
    public CObj
{
public:
    CEnemy();
    virtual ~CEnemy();


    void OnDamage(int dmg) { m_fCurHp -= dmg; if (m_fCurHp <= 0.f) m_fCurHp = 0.f;  }
    virtual void Motion_Change() PURE;
protected:
    float m_fMaxHp;
    float m_fCurHp;
};

