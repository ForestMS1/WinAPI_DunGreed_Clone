#pragma once
#include "CWeapon.h"
#include "CCosSwingFX.h"
class CCosSword :
    public CWeapon
{
public:
    CCosSword();
    CCosSword(float fX, float fY);
    CCosSword(const CCosSword& rhs)
    {
        m_pSwingFX = dynamic_cast<CCosSwingFX*>(rhs.m_pSwingFX)->Clone();
    }
    ~CCosSword();
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
    CObj* m_pSwingFX;

    bool m_bIsGot;
    DWORD m_dwSoundTick;
    UINT m_SoundIndex;

    DWORD m_dwShootDelay;

    bool isAttack;
};

