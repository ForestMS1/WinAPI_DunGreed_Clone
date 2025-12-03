#pragma once
#include "CObj.h"
class CBullet :
    public CObj
{
public:
    CBullet();
    virtual~CBullet();
public:
    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void Set_Angle(float fAngle) { m_fAngle = fAngle; }
    void Set_Damage(float dmg) { m_fDamage = dmg; }
    float Get_Damage() const { return m_fDamage; }
protected:
    float m_fDamage;
    float m_fAngle;
};

