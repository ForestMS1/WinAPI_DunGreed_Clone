#include "pch.h"
#include "CUIMgr.h"

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
	for (auto iter : m_mapUI)
	{
		iter.second->Initialize();
	}
}
void CUIMgr::Update()
{
	for (auto iter : m_mapUI)
	{
		iter.second->Update();
	}
}
void CUIMgr::Late_Update()
{
	for (auto iter : m_mapUI)
	{
		iter.second->Late_Update();
	}
}
void CUIMgr::Render(HDC hDC)
{
	for (auto iter : m_mapUI)
	{
		iter.second->Render(hDC);
	}
}
void CUIMgr::Release()
{
	for (auto iter : m_mapUI)
	{
		Safe_Delete(iter.second);
	}
	m_mapUI.clear();
}