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
	m_umapUI.insert({ L"MapTileUI", new CMapTileUI });

	for (auto& pUI : m_umapUI)
	{
		pUI.second->Initialize();
	}
}

void CUIMgr::Update()
{
	for (auto& pUI : m_umapUI)
	{
		pUI.second->Update();
	}
}

void CUIMgr::Late_Update()
{
	for (auto& pUI : m_umapUI)
	{
		pUI.second->Late_Update();
	}
}


void CUIMgr::Render(HDC hDC)
{
	for (auto& pUI : m_umapUI)
	{
		pUI.second->Render(hDC);
	}
}

void CUIMgr::Release()
{
	for (auto& pUI : m_umapUI)
	{
		Safe_Delete(pUI.second);
	}
	m_umapUI.clear();
}

CUI* CUIMgr::Get_UI(wstring UIKey)
{
	unordered_map<wstring, CUI*>::iterator iter = m_umapUI.find(UIKey);
	if (iter != m_umapUI.end())
	{
		return (*iter).second;
	}
	return nullptr;
}

