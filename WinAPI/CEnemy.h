#pragma once
#include "CObj.h"
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

