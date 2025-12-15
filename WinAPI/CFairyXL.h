#pragma once
#include "CItem.h"
class CFairyXL :
    public CItem
{
public:
    CFairyXL();
    CFairyXL(int reHp, float fX, float fY);
    ~CFairyXL();
public:
    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
private:
    int m_iReHp;
    float m_fSpeed;
    bool m_bIsGot;

    float m_fBurstAngle;
    float m_fBurstSpeed;
    DWORD m_dwBurstEnd;

    DWORD m_dwSpawnTime;

    // CItem을(를) 통해 상속됨
    CItem* Clone() override;
};

