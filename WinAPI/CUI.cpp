#include "pch.h"
#include "CUI.h"

CUI::CUI() : m_bIsFlipped(false), m_bIsOpen(true), m_pParentUI(nullptr)
{
	ZeroMemory(&m_tInfo, sizeof(m_tInfo));
	ZeroMemory(&m_tRect, sizeof(m_tRect));
	ZeroMemory(&m_tFrame, sizeof(m_tFrame));
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
