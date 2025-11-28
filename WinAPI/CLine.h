#pragma once
#include "CObj.h"
class CLine :
    public CObj
{
public:
    CLine();
    CLine(POINT ptLeft, POINT ptRight);
    virtual~CLine();
    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int  Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;
    POINT Get_Left() const { return m_ptLeft; }
    POINT Get_Right() const { return m_ptRight; }
private:
    POINT   m_ptLeft;
    POINT   m_ptRight;
};

