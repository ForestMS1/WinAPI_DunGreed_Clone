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
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

private:
    float m_fAddAtk;
    float m_fAddDfs;
    float m_fAddHp;

};

