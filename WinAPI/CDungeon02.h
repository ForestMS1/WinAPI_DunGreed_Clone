#pragma once
#include "CScene.h"
class CDungeon02 :
    public CScene
{
public:
    CDungeon02();
    virtual ~CDungeon02();
public:
    // CScene을(를) 통해 상속됨
    void Initialize() override;
    void Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void Key_Input();
};

