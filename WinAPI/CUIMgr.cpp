#include "pch.h"
#include "CUIMgr.h"
#include "CMapTileUI.h"

CUIMgr* CUIMgr::m_pInstance = nullptr;

CUIMgr::CUIMgr()
{

}
CUIMgr::~CUIMgr()
{
	Release();
}

void CUIMgr::Initialize()
{
	m_vecUI.push_back(new CMapTileUI);

	for (auto& pUI : m_vecUI)
	{
		pUI->Initialize();
	}
}

void CUIMgr::Update()
{
	for (auto& pUI : m_vecUI)
	{
		pUI->Update();
	}
}

void CUIMgr::Render(HDC hDC)
{
	for (auto& pUI : m_vecUI)
	{
		pUI->Render(hDC);
	}
}

void CUIMgr::Release()
{
	for (auto& pUI : m_vecUI)
	{
		Safe_Delete(pUI);
	}
	m_vecUI.clear();
}

