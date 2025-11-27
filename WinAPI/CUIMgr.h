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

private:
	vector<CUI*> m_vecUI;
};

