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

    wstring GetItemName() const { return m_wsName; }
    int GetShopPrice() const { return m_fShopPrice; }
    bool IsDrop()   const { return m_bIsDrop; }
    void SetDrop(bool isDrop) { m_bIsDrop = isDrop; }

    //플레이어 감지
    void ToPlayerAngle();
    void Update_DetectRect();
    RECT* GetDetectRect() { return &m_tDetectRect; }
    void InPlayer() { m_bIsInPlayer = true; }
    void OutPlayer() { m_bIsInPlayer = false; }

protected:
    float m_fAddAtk;
    float m_fAddDfs;
    float m_fAddHp;
    int m_fShopPrice;
    wstring m_wsName;

    bool m_bIsDrop;

    //플레이어를 감지 할 범위
    RECT  m_tDetectRect;
    float m_fDetectfCX;
    float m_fDetectfCY;
    bool  m_bIsInPlayer;

    float m_fAngle;


};

