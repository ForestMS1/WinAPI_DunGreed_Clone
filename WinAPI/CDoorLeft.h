#pragma once
#include "CObj.h"
class CDoorLeft :
    public CObj
{
public:
    enum DOOR_STATE { OPEN, IDLE, CLOSE, END };
public:
    CDoorLeft();
    ~CDoorLeft();
public:
    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void SetDoorState(DOOR_STATE eState) { m_eCurState = eState; }
    DOOR_STATE GetDoorState() const { return m_eCurState; }
private:
    void Motion_Change();
private:
    DOOR_STATE m_ePreState;
    DOOR_STATE m_eCurState;
};

