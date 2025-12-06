#pragma once
#include "CObj.h"
class CUnit :
    public CObj
{
public:
    CUnit();
    virtual~CUnit();

    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void OnDamage(int dmg) 
    { 
        m_fCurHp -= dmg; 
        if (m_fCurHp <= 0.f) 
            m_fCurHp = 0.f; 

        m_dwLastHitTime = GetTickCount();
        m_bIsHit = true;
    }
protected:
    bool m_bIsHit;
    DWORD m_dwLastHitTime;
};

