#include "pch.h"
#include "CScene.h"
#include "CTile.h"
#include "CObjMgr.h"
CScene::CScene()
{
}

CScene::~CScene()
{
}

void CScene::CreateTile(UINT _iXCount, UINT _iYCount)
{
	for (UINT i = 0; i < _iYCount; ++i)
	{
		for (UINT j = 0; j < _iXCount; ++j)
		{
			CTile* pTile = new CTile;
			pTile->Set_Pos((float)(j * TILESIZE), (float)(i * TILESIZE));
			pTile->SetFrameKey(L"MapTile");
			GET(CObjMgr)->AddObject(OBJ_TILE, pTile);
		}
	}
}

void CScene::Release()
{
	
}
