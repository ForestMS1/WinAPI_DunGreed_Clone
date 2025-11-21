#pragma once
#include "Define.h"
class CMainGame
{
public:
	CMainGame();
	~CMainGame();
public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render();
	void Release();

private:
	HDC			m_hDC;
	HDC			m_hBackDC;
	HBITMAP		m_hBitMap;

	int			m_iFps;
	DWORD		m_dwLastTime;
	TCHAR		m_szFPS[128];
};

