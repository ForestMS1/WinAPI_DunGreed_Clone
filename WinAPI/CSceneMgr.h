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
	SCENEID GetCurSceneID() const { return m_pCurCScene->GetSceneID(); }

private:
	map<wstring, CScene*>	m_mapScene;
	CScene*					m_pCurCScene;

};

