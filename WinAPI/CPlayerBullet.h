#pragma once
#include "CBullet.h"
class CPlayerBullet :
    public CBullet
{
public:
    CPlayerBullet();
    virtual~CPlayerBullet();
public:
    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
};

