#pragma once
#include "CEnemy.h"
class CBelialBack :
    public CEnemy
{
public:
    CBelialBack();
    CBelialBack(CEnemy* pBelial, float fX, float fY);
    ~CBelialBack();
public:
    // CEnemy을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
    void Motion_Change() override;

    CEnemy* m_pOwner;

    BELIAL_STATE m_eBelailPreState;
    BELIAL_STATE m_eBelialCurState;

    BYTE m_bAlpha;
    bool m_bIntro;

    float offsetX;
    float offsetY;
};

