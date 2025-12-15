#pragma once
#include "CObj.h"
class CStartDoor :
    public CObj
{
public:
    CStartDoor();
    ~CStartDoor();
public:
    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void SetOpen() { m_bIsOpen = true; }
private:
    bool m_bPlaySound;

    bool m_bIsOpen;
};

