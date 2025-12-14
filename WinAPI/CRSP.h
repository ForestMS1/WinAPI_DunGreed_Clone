#pragma once
#include "CUI.h"
#include "CRSPMgr.h"
class CRSP :
    public CUI
{
public:
    CRSP(CObj* pOwner);
    ~CRSP();
public:
    // CUI을(를) 통해 상속됨
    void Initialize() override;
    int Update() override;
    void Late_Update() override;
    void Render(HDC hDC) override;
    void Release() override;

    void SetStop() 
    { 
        m_bStop = true; 
        switch (m_tFrame.iStart)
        {
        case 0:
            GET(CRSPMgr)->SetEnemySelect(CRSPMgr::ROCK);
            break;
        case 1:
            GET(CRSPMgr)->SetEnemySelect(CRSPMgr::SCISSORS);
            break;
        case 2:
            GET(CRSPMgr)->SetEnemySelect(CRSPMgr::PAPER);
            break;
        default:
            break;
        }
    }
    void SetPlay() { m_bStop = false; }
private:
    CObj* m_pOwner;

    bool m_bStop;
};

