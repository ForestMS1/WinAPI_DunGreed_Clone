#pragma once
#include "CScene.h"
class CDungeon06 :
    public CScene
{
public:
    CDungeon06();
    virtual ~CDungeon06();
public:
    // CScene을(를) 통해 상속됨
    void Initialize() override;
    void Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void Key_Input();
};

