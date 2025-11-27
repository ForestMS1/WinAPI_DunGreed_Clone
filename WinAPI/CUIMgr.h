#pragma once
#include "Define.h"
#include "CUI.h"
class CUIMgr
{
	SINGLE(CUIMgr)
public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render(HDC hDC);
	void Release();

public:
	CUI* Get_UI(wstring UIKey);

private:
	//최상위 부모 UI만 넣어서 관리한다
	unordered_map<wstring, CUI*> m_umapUI;
};

