#pragma once
#include "CObj.h"
class CItem :
    public CObj
{
public:
    enum ITEM_STATE { DROPPED, ON_INVEN, ON_EQUIPPED, ITEM_STATE_END };
public:
    CItem();
    virtual~CItem();
public:

    // CObj을(를) 통해 상속됨
    virtual void Initialize() override;
    virtual int Update() override;
    virtual void Late_Update() override;
    virtual void Render(HDC hDC) override;
    virtual void Release() override;
    virtual CItem* Clone() = 0;
private:
    float m_fAddAtk;
    float m_fAddDfs;
    float m_fAddHp;
};

