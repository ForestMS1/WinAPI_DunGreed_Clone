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


private:
	map<wstring, CScene*>	m_mpScene;
	CScene*					m_pCurCScene;

};

