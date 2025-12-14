#pragma once
#include "CWeapon.h"
class CLala :
    public CWeapon
{
public:
    CLala();
    CLala(float fX, float fY);
    ~CLala();
public:
    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    // CItem을(를) 통해 상속됨
    CItem* Clone() override;
    void SetGotFree() { m_bIsGot = false; }

private:
    bool m_bIsGot;

private:
    DWORD	m_dwShootDelay;
    DWORD   m_dwSoundTick;
};

