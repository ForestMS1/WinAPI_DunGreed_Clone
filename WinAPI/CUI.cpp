#include "pch.h"
#include "CUI.h"

CUI::CUI() : m_bIsFlipped(false), m_bIsOpen(false), m_pParentUI(nullptr)
{
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
	ZeroMemory(&m_tRect, sizeof(m_tRect));
	ZeroMemory(&m_tFrame, sizeof(m_tFrame));
	m_eRender = UI;
}

CUI::~CUI()
{

}

void CUI::Initialize()
{
}

int CUI::Update()
{
	return 0;
}

void CUI::Late_Update()
{
}

void CUI::Render(HDC hDC)
{
}

void CUI::Release()
{
}

void CUI::Move_Frame()
{
    // Move_Frame이 안먹어서 직접Move_Frame();
    if (m_tFrame.dwSpeed + m_tFrame.dwTime < GetTickCount())
    {
        ++m_tFrame.iStart;
        m_tFrame.dwTime = GetTickCount();
    
    
        if (m_tFrame.iStart > m_tFrame.iEnd)
            m_tFrame.iStart = 0;
    }
}
