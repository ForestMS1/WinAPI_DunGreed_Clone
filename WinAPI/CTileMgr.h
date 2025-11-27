#pragma once
#include "CTile.h"
#include "Define.h"
class CTileMgr
{
	SINGLE(CTileMgr)


public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render(HDC hDC);
	void Release();

public:
	void Picking_Tile(POINT ptMouse, int iDrawIDX, int iDrawIDY, int iOption);
	void Save_Tile();
	void Load_Tile();

private:
	vector<CObj*> m_vecTile;
};

