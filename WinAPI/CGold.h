#pragma once
#include "CItem.h"
class CGold :
    public CItem
{
public:
    CGold();
    CGold(int gold, float fX, float fY);
    ~CGold();
public:
    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
private:
    int m_iGold;
    float m_fSpeed;
    bool m_bIsGot;

    float m_fBurstAngle;
    float m_fBurstSpeed;
    DWORD m_dwBurstEnd;

    // CItem을(를) 통해 상속됨
    CItem* Clone() override;
};

