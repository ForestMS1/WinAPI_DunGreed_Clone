#pragma once
#include "CNPC.h"
class CTresure :
    public CNPC
{
private:
    enum STATE { SPAWN, IDLE, END };
public:
    CTresure();
    ~CTresure();
    // CEnemy을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void Motion_Change();
private:
    void KeyInput();
    void SpawnEffect();

    bool m_bIsClear;
    bool m_bOpen;
    bool m_bCompleteDropGold;

    bool m_bIsSpawnSound;

    STATE m_ePreState;
    STATE m_eCurState;
};

