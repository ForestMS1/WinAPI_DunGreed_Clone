#pragma once
#include "Define.h"
class CMouse
{
	SINGLE(CMouse)
public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render(HDC hDC);
	void Release();

	void Set_DrawID(int x, int y) { m_iDrawIDX = x; m_iDrawIDY = y; }
	void Set_Option(int option) { m_iOption = option; }
	int Get_DrawIDX() const { return m_iDrawIDX; }
	int Get_DrawIDY() const { return m_iDrawIDY; }
	int Get_Option() const { return m_iOption; }

private:
	INFO m_tInfo;
	RECT m_tRect;
	POINT m_ptInfo;

	int m_iDrawIDX;
	int m_iDrawIDY;
	int m_iOption;
};

