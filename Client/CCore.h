#pragma once
#include "pch.h"
class CCore
{
	SINGLE(CCore)
public:
	void Init(HWND hWnd, POINT pResolution);
private:
	CCore();
	//~CCore();
private:
	HWND m_hWnd;
	POINT m_pResolution;
};

