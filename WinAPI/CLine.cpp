#include "pch.h"
#include "CLine.h"

CLine::CLine()
{
	ZeroMemory(&m_ptLeft, sizeof(m_ptLeft));
	ZeroMemory(&m_ptRight, sizeof(m_ptRight));

}
CLine::CLine(POINT ptLeft, POINT ptRight)
{
	m_ptLeft.x = ptLeft.x;
	m_ptLeft.y = ptLeft.y;
	m_ptRight.x = ptRight.x;
	m_ptRight.y = ptRight.y;
}
CLine::~CLine()
{

}

void CLine::Initialize()
{
}

int CLine::Update()
{
	return 0;
}

void CLine::Late_Update()
{
}

void CLine::Render(HDC hDC)
{
	MoveToEx(hDC, m_ptLeft.x, m_ptLeft.y, nullptr);
	LineTo(hDC, m_ptRight.x, m_ptRight.y);
}

void CLine::Release()
{
}
