#pragma once
#include "CLine.h"
class CLineMgr
{
	SINGLE(CLineMgr)

public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render(HDC hDC);
	void Release();
public:
	list<CLine*>&	Get_Line() { return m_LineList; }
	void			Add_Line(CLine* pLine);
	bool			Collision_Line(CObj* pPlayer, float* pY);
private:
	list<CLine*> m_LineList;
};

