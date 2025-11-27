#include "pch.h"
#include "CTileMgr.h"
#include "CCamera.h"
#include "CResourceMgr.h"
#include "CAbstractFactory.h"

CTileMgr* CTileMgr::m_pInstance = nullptr;

CTileMgr::CTileMgr()
{
	m_vecTile.reserve(TILEX * TILEY);
}
CTileMgr::~CTileMgr()
{
	Release();
}

void CTileMgr::Initialize()
{
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			float		fX = (TILECX * j) + (TILECX >> 1);
			float		fY = (TILECY * i) + (TILECY >> 1);

			CObj* pTile = CAbstractFactory<CTile>::Create(fX, fY);
			m_vecTile.push_back(pTile);
		}
	}
}

void CTileMgr::Update()
{
	for (auto& pTile : m_vecTile)
	{
		pTile->Update();
	}
}

void CTileMgr::Late_Update()
{
	for (auto& pTile : m_vecTile)
	{
		pTile->Late_Update();
	}
}

void CTileMgr::Render(HDC hDC)
{
	int	iCullX = abs((int)CCamera::Get_Instance()->Get_ScrollX() / TILECX);
	int	iCullY = abs((int)CCamera::Get_Instance()->Get_ScrollY() / TILECY);

	int iMaxX = iCullX + WINCX / TILECX + 2;
	int iMaxY = iCullY + WINCY / TILECY + 2;

	for (int i = iCullY; i < iMaxY; ++i)
	{
		for (int j = iCullX; j < iMaxX; ++j)
		{
			int iIndex = i * TILEX + j;

			if (0 > iIndex || (size_t)iIndex >= m_vecTile.size())
				continue;

			m_vecTile[iIndex]->Render(hDC);
		}
	}
}

void CTileMgr::Release()
{
	for (auto& pTile : m_vecTile)
	{
		Safe_Delete(pTile);
	}
	m_vecTile.clear();
}

void CTileMgr::Picking_Tile(POINT ptMouse, int iDrawIDX, int iDrawIDY, int iOption)
{
	int	x = ptMouse.x / TILECX;
	int	y = ptMouse.y / TILECY;

	int iIndex = y * TILEX + x;

	if (0 > iIndex || (size_t)iIndex >= m_vecTile.size())
		return;

	dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_DrawID(iDrawIDX, iDrawIDY);
	dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_Option(iOption);
}