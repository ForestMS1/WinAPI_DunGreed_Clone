#pragma once
#include "CObj.h"
class CRSPMgr 
{
    SINGLE(CRSPMgr)
public:
    enum SELECT {ROCK, SCISSORS, PAPER, SELECT_END};
public:
    // CEnemy을(를) 통해 상속됨
    void Initialize();
    int Update();
    void Late_Update();
    void Render(HDC hDC);
    void Release();

    void SetPlayerSelect(SELECT eSelect) { m_ePlayerSelect = eSelect; }
    void SetEnemySelect(SELECT eSelect) { m_eEnemySelect = eSelect; }

public:
    bool IsPlayerWin() const { return m_bIsPlayerWin; }
private:
    bool m_bIsPlayerWin;

    DWORD m_dwLoseTime;

    SELECT m_ePlayerSelect;
    SELECT m_eEnemySelect;
};

