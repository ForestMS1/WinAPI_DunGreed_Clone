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
    void Update_DetectRect();
    RECT* GetDetectRect() { return &m_tDetectRect; }
    void InPlayer() { m_bIsInPlayer = true; }
    void OutPlayer() { m_bIsInPlayer = false; }
    virtual void Motion_Change() PURE;
protected:
    float m_fMaxHp;
    float m_fCurHp;

    //플레이어를 감지 할 범위
    RECT  m_tDetectRect;
    float m_fDetectfCX;
    float m_fDetectfCY;
    bool  m_bIsInPlayer;
};

