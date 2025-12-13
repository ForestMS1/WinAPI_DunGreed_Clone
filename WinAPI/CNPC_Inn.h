#pragma once
#include "CNPC.h"
class CNPC_Inn :
    public CNPC
{
public:
    CNPC_Inn();
    ~CNPC_Inn();
    // CEnemy을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
private:
    void KeyInput();
};

