#pragma once
#include "Define.h"
#include "CItem.h"
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
	POINT Get_Point() const { return m_ptInfo; }

private:
	INFO m_tInfo;
	RECT m_tRect;
	POINT m_ptInfo;

	//아이템 집기 위한 변수
	CItem* m_pItem;

	// 타일에디터에서 값을 넘겨주기 위한 변수
	int m_iDrawIDX;
	int m_iDrawIDY;
	int m_iOption;
};

