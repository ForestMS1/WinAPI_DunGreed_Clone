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

    void SetNifleHeim(CObj* pNifleHeim) { m_pNifleHeim = pNifleHeim; }
    void SetPlayerSelect(SELECT eSelect) { m_ePlayerSelect = eSelect; }
    void SetEnemySelect(SELECT eSelect) { m_eEnemySelect = eSelect; }
    SELECT GetEnemySelect() const { return m_eEnemySelect; }
    SELECT GetPlayerSelect() const { return m_eEnemySelect; }

public:
    bool IsPlayerWin() const { return m_bIsPlayerWin; }
private:
    bool m_bIsPlayerWin;
    bool m_bIsEnemyWin;

    DWORD m_dwLoseTime;

    CObj* m_pNifleHeim;

    SELECT m_ePlayerSelect;
    SELECT m_eEnemySelect;
};

