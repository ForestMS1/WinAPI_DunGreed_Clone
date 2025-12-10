#pragma once
#include "CObj.h"
class CDoor :
    public CObj
{
public:
    enum DOOR_STATE 
    { 
        OPEN_LEFT, IDLE_LEFT, CLOSE_LEFT, 
        OPEN_BOTTOM, IDLE_BOTTOM, CLOSE_BOTTOM, 
        OPEN_RIGHT, IDLE_RIGHT, CLOSE_RIGHT, 
        END
    };
public:
    CDoor();
    ~CDoor();
public:
    // CObj을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void SetDoorState(DOOR_STATE eState) { m_eCurState = eState; }
    DOOR_STATE GetDoorState() const { return m_eCurState; }
    void SetNextSceneName(wstring name) { m_wsNextSceneName = name; }
    wstring GetNextSceneName() const { return m_wsNextSceneName; }
private:
    void Motion_Change();
private:
    DOOR_STATE m_ePreState;
    DOOR_STATE m_eCurState;
    wstring m_wsNextSceneName;
};

