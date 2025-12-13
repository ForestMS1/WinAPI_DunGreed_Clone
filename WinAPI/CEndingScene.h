#pragma once
#include "CScene.h"
class CEndingScene :
    public CScene
{
public:
    CEndingScene();
    virtual ~CEndingScene();
public:
    // CScene을(를) 통해 상속됨
    void Initialize() override;
    void Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    DWORD m_SpawnEffectStartTime;
    BYTE m_bAlpha;
    HFONT m_hFont;

    float m_fTextScrollY;
    float m_fSpeed;
};

