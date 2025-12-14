#pragma once
#include "CNPC.h"
class CNPC_Commander :
    public CNPC
{
public:
    CNPC_Commander();
    ~CNPC_Commander();
    // CEnemy을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
private:
    void KeyInput();
};

