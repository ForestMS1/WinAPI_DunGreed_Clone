#pragma once
#include "CScene.h"
class CDungeonFoodShop :
    public CScene
{
public:
    CDungeonFoodShop();
    virtual ~CDungeonFoodShop();
public:
    // CScene을(를) 통해 상속됨
    void Initialize() override;
    void Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void Key_Input();
};

