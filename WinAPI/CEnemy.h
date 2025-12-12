#pragma once
#include "CUnit.h"

enum BELIAL_STATE { BELAIL_IDLE, ATTACK_ROTATE, ATTACK_HAND, ATTACK_SPEAR, BELIAL_DEAD, STATE_END };

class CEnemy :
    public CUnit
{
protected:
    enum STATE { SPAWN, IDLE, ATTACK, MOVE, DEAD, END };
public:
    CEnemy();
    virtual ~CEnemy();

    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void ToPlayerAngle();
    void Update_DetectRect();
    RECT* GetDetectRect() { return &m_tDetectRect; }
    void InPlayer() { m_bIsInPlayer = true; }
    void OutPlayer() { m_bIsInPlayer = false; }
    virtual void Motion_Change() PURE;

    void OnDamage(int dmg) override
    {
        if (m_bIsHit)
            return;
        int result = dmg + (rand()%5);
        m_fCurHp -= result;
        if (m_fCurHp <= 0.f && !m_bIsDead)
        {
            m_fCurHp = 0.f;
            m_bIsDead = true;
            DropGold();
            DropGold();
            DropGold();
            DropGold();
        }

        m_dwLastHitTime = GetTickCount();
        m_bIsHit = true;
        GET(CSoundMgr)->PlaySoundW(L"Hit_Monster.wav", SOUND_EFFECT, 0.3f);
        CDamageText* pDamage = new CDamageText(result, m_tInfo.fX, m_tRect.top);
        pDamage->Initialize();
        GET(CObjMgr)->AddObject(OBJ_EFFECT, pDamage);
    }

protected:
    void SpawnEffect();
    void DeadEffect();
    void DropGold();
protected:
    //플레이어를 감지 할 범위
    RECT  m_tDetectRect;
    float m_fDetectfCX;
    float m_fDetectfCY;
    bool  m_bIsInPlayer;

    float m_fAngle;

    CUI* m_pHpBarUI;

    bool m_bIsSpawnSound;

    STATE m_ePreState;
    STATE m_eCurState;

    int  m_iDropGold;
};

