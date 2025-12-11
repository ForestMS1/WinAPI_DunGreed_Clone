#pragma once
#include "CObj.h"
class CDamageText :
    public CObj
{
public:
    CDamageText(int damage, float fX, float fY);
    ~CDamageText();
public:
    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

private:
    int   m_iDamage;
    DWORD m_dwSpawnTime; // 생성된 시간
    DWORD m_dwLifeTime = 1000;
    float m_fSpeed;

    float m_ft;
};

