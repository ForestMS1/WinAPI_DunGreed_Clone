#pragma once
#include "CLine.h"
class CLineMgr
{
public:
	enum POINTDIRECTION { LEFT, RIGHT, END };
	SINGLE(CLineMgr)

public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render(HDC hDC);
	void Release();

	void Save_Line();
	void Load_Line();
public:
	list<CLine*>&	Get_Line() { return m_LineList; }
	void			Add_Line(CLine* pLine);
	bool			Collision_Line(CObj* pPlayer, float* pY);
private:
	list<CLine*> m_LineList;
	LINEPOINT			m_tPoint[END];
	bool m_bClicked;

	struct LINE_DATA
	{
		POINT tLeft;
		POINT tRight;
	};
};

