#include "pch.h"
#include "CRSPSelect.h"
#include "CRock.h"
#include "CScissors.h"
#include "CPaper.h"
CRSPSelect::CRSPSelect()
{
}

CRSPSelect::~CRSPSelect()
{
    Release();
}

void CRSPSelect::Initialize()
{
    m_iFrameWidth = 44;
    m_iFrameHeight = 45;
    m_tInfo.fCX = 44 * 3;
    m_tInfo.fCY = 45;
    m_tInfo.fX = WINCX >> 1;
    m_tInfo.fY = WINCY - 200;
    __super::Update_Rect();
    m_bIsOpen = false;

    CUI* pBtn = new CRock;
    AddChildUI(pBtn);
    pBtn = new CScissors;
    AddChildUI(pBtn);
    pBtn = new CPaper;
    AddChildUI(pBtn);

    for (auto& pChildUI : m_vecChildUI)
    {
        pChildUI->Initialize();
    }
}

int CRSPSelect::Update()
{
    __super::Update_Rect();

    for (auto& pChildUI : m_vecChildUI)
    {
        pChildUI->Update();
    }
    return 0;
}

void CRSPSelect::Late_Update()
{
    for (auto& pChildUI : m_vecChildUI)
    {
        pChildUI->Late_Update();
    }
}

void CRSPSelect::Render(HDC hDC)
{
    if (!m_bIsOpen)
        return;
    for (auto& pChildUI : m_vecChildUI)
    {
        pChildUI->Render(hDC);
    }
}

void CRSPSelect::Release()
{
    for (auto& pChildUI : m_vecChildUI)
    {
        Safe_Delete(pChildUI);
    }
    m_vecChildUI.clear();
}
