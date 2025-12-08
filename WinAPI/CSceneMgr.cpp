#include "pch.h"
#include "CSceneMgr.h"
#include "CMouse.h"

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
	map<wstring, CScene*>::iterator iter = m_mapScene.begin();

	for (; iter != m_mapScene.end(); ++iter)
	{
		Safe_Delete(iter->second);
	}
	m_mapScene.clear();
}

void CSceneMgr::CreateScene(wstring sceneName, CScene* pScene)
{
	if (pScene != nullptr && (m_mapScene.find(sceneName) == m_mapScene.end()))
	{
		m_mapScene.insert({sceneName, pScene});
	}
}

void CSceneMgr::ChangeScene(wstring sceneName)
{
	map<wstring, CScene*>::iterator iter = m_mapScene.find(sceneName);
	if (iter != m_mapScene.end())
	{
		if(m_pCurCScene != nullptr)
			m_pCurCScene->Release();

		m_pCurCScene = iter->second;
		m_pCurCScene->Initialize();
	}
}
