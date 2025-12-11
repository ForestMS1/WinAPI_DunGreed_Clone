#pragma once
#include "CNPC.h"
class CNPC_Giant :
    public CNPC
{
public:
    CNPC_Giant();
    ~CNPC_Giant();
    // CEnemy을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
private:
    void KeyInput();
};

