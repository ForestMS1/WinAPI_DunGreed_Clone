#pragma once
#include "CEnemy.h"
class CNifleHeim :
    public CEnemy
{
public:
    CNifleHeim();
    ~CNifleHeim();
    // CEnemy을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    NIFLEHEIM_STATE GetCurState() const { return m_eNifleHeimCurState; }
    CObj* GetPortal() const { return m_pPortal; }
private:
    void Motion_Change() override;
    void DeadEffect();
private:
    NIFLEHEIM_STATE m_eNifleHeimPreState;
    NIFLEHEIM_STATE m_eNifleHeimCurState;

    DWORD m_SpawnEffectStartTime;
    bool m_bPlayBossBGM;
    float m_DeadEffectTime;

    bool m_bIntro;
    BYTE m_bAlpha;
    HFONT m_hFont;

    CObj* m_pPortal;

    DWORD m_dwDeadStartTime;

    bool CompleteCreatePortal;
};

