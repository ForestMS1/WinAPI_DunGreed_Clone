#pragma once
#include "CScene.h"
class CDungeonStart :
    public CScene
{
public:
    CDungeonStart();
    virtual ~CDungeonStart();
public:
    // CScene을(를) 통해 상속됨
    void Initialize() override;
    void Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void Key_Input();
private:
    POINT       m_ptMouse;
    POINT       m_ptLeft;
    POINT       m_ptRight;
    bool        m_bIsDrawing;
};

