#include "pch.h"
#include "CLine.h"
#include "CCamera.h"
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
	Vec2 vStart = GET(CCamera)->GetRenderPos(Vec2(m_ptLeft.x, m_ptLeft.y));
	Vec2 vEnd = GET(CCamera)->GetRenderPos(Vec2(m_ptRight.x, m_ptRight.y));

	MoveToEx(hDC, vStart.fX, vStart.fY, nullptr);
	LineTo(hDC, vEnd.fX, vEnd.fY);
}

void CLine::Release()
{
}
