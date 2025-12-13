#pragma once
#include "CNPC.h"
class CPortal :
    public CNPC
{
public:
    CPortal();
    ~CPortal();
    // CEnemy을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
    bool EnterPortal() const { return GoNextScene; }
private:
    void KeyInput();
    bool GoNextScene;
};

