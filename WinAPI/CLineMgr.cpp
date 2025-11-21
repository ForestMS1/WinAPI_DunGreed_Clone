#include "pch.h"
#include "CLineMgr.h"

CLineMgr* CLineMgr::m_pInstance = nullptr;

CLineMgr::CLineMgr()
{

}
CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize()
{
	for (auto iter = m_LineList.begin(); iter != m_LineList.end(); ++iter)
	{
		if((*iter) != nullptr)
			(*iter)->Initialize();
	}
}

void CLineMgr::Update()
{
	for (auto iter = m_LineList.begin(); iter != m_LineList.end(); ++iter)
	{
		if ((*iter) != nullptr)
			(*iter)->Update();
	}
}

void CLineMgr::Late_Update()
{
	for (auto iter = m_LineList.begin(); iter != m_LineList.end(); ++iter)
	{
		if ((*iter) != nullptr)
			(*iter)->Late_Update();
	}
}

void CLineMgr::Render(HDC hDC)
{
	for (auto iter = m_LineList.begin(); iter != m_LineList.end(); ++iter)
	{
		if ((*iter) != nullptr)
			(*iter)->Render(hDC);
	}
}

void CLineMgr::Release()
{
	for (auto iter = m_LineList.begin(); iter != m_LineList.end(); ++iter)
	{
		Safe_Delete((*iter));
	}
	m_LineList.clear();
}

void CLineMgr::Add_Line(CLine* pLine)
{
	if(pLine != nullptr)
		m_LineList.push_back(pLine);
}
