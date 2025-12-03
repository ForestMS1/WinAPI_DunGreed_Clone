#pragma once
#include "CUnit.h"

enum BELIAL_STATE { IDLE, ATTACK_ROTATE, ATTACK_HAND, ATTACK_SPEAR, DEAD, STATE_END };


class CEnemy :
    public CUnit
{
public:
    CEnemy();
    virtual ~CEnemy();



    void Update_DetectRect();
    RECT* GetDetectRect() { return &m_tDetectRect; }
    void InPlayer() { m_bIsInPlayer = true; }
    void OutPlayer() { m_bIsInPlayer = false; }
    virtual void Motion_Change() PURE;
protected:
    //플레이어를 감지 할 범위
    RECT  m_tDetectRect;
    float m_fDetectfCX;
    float m_fDetectfCY;
    bool  m_bIsInPlayer;
};

