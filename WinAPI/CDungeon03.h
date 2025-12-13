#pragma once
#include "CScene.h"
class CDungeon03 :
    public CScene
{
public:
    CDungeon03();
    virtual ~CDungeon03();
public:
    // CScene을(를) 통해 상속됨
    void Initialize() override;
    void Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void Key_Input();
};

