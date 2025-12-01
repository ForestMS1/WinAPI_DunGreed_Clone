#pragma once
#include "Define.h"
#include "CScene.h"
class CScene;

class CSceneMgr
{
	SINGLE(CSceneMgr)

public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render(HDC hDC);
	void Release();

	void CreateScene(wstring sceneName, CScene* pScene);
	void ChangeScene(wstring sceneName);
	CScene* GetCurScene() const { return m_pCurCScene; }

private:
	map<wstring, CScene*>	m_mapScene;
	CScene*					m_pCurCScene;

};

