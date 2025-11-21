#include "pch.h"
#include "CSceneMgr.h"

CSceneMgr* CSceneMgr::m_pInstance = nullptr;

CSceneMgr::CSceneMgr() : m_pCurCScene(nullptr)
{

}
CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Initialize()
{
	m_pCurCScene->Initialize();
}

void CSceneMgr::Update()
{
	m_pCurCScene->Update();
}

void CSceneMgr::Late_Update()
{
	m_pCurCScene->Late_Update();
}

void CSceneMgr::Render(HDC hDC)
{
	m_pCurCScene->Render(hDC);
}

void CSceneMgr::Release()
{
	map<wstring, CScene*>::iterator iter = m_mpScene.begin();

	for (; iter != m_mpScene.end(); ++iter)
	{
		Safe_Delete(iter->second);
	}
	m_mpScene.clear();
}

void CSceneMgr::CreateScene(wstring sceneName, CScene* pScene)
{
	if (pScene != nullptr && (m_mpScene.find(sceneName) == m_mpScene.end()))
	{
		m_mpScene.insert({sceneName, pScene});
	}
}

void CSceneMgr::ChangeScene(wstring sceneName)
{
	map<wstring, CScene*>::iterator iter = m_mpScene.find(sceneName);
	if (iter != m_mpScene.end())
	{
		m_pCurCScene = iter->second;
		m_pCurCScene->Initialize();
	}
}
