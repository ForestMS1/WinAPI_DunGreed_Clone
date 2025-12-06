#pragma once
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

	void Insert_UI(wstring name, CUI* pUI) {if(m_mapUI.find(name) == m_mapUI.end()) m_mapUI.insert({ name, pUI }); }
	CUI* Find_UI(wstring name) { auto iter = m_mapUI.find(name); if (iter != m_mapUI.end()) { return iter->second; } else return nullptr; }
private:
	unordered_map<wstring, CUI*>		m_mapUI;
};

