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
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/MapTool/MapTile.bmp", L"MapTile");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/MapTool/Object.bmp", L"MapTileOption");
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

void CTileMgr::Picking_Tile(POINT ptMouse, int iOption)
{
	int	x = ptMouse.x / TILECX;
	int	y = ptMouse.y / TILECY;

	int iIndex = y * TILEX + x;

	if (0 > iIndex || (size_t)iIndex >= m_vecTile.size())
		return;

	dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_Option(iOption);
}


void CTileMgr::Save_Tile()
{
	HANDLE	hFile = CreateFile(L"../Resources/Data/Tile.dat", // 파일 이름이 포함된 경로
		GENERIC_WRITE,		// 파일 접근 모드(GENERIC_WRITE : 쓰기, GENERIC_READ : 읽기)
		NULL,				// 공유 방식(파일이 열려 있는 상태에서 다른 프로세스가 오픈 할 때 허가하는 것에 대해 설정, 지정하지 않을 경우 NULL)
		NULL,				// 보안 속성(기본값인 경우 NULL)
		CREATE_ALWAYS,		// 파일이 없을 경우 파일을 생성하여 저장(OPEN_EXISTING : 파일이 있을 경우에만 로드)
		FILE_ATTRIBUTE_NORMAL,	// 파일 속성(아무런 속성이 없는 일반 파일)
		NULL);				// 생성될 파일의 속성ㅇ르 제공할 템플릿 파일

	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(g_hWnd, _T("Tile File"), L"Fail", MB_OKCANCEL);
		return;
	}

	DWORD		dwByte(0);
	TILEINFO	tDrawID{ 0,0 };
	int			iOption(0);

	for (auto& pTile : m_vecTile)
	{
		tDrawID = dynamic_cast<CTile*>(pTile)->Get_DrawID();
		iOption = dynamic_cast<CTile*>(pTile)->Get_Option();

		WriteFile(hFile, pTile->Get_Info(), sizeof(INFO), &dwByte, NULL);
		WriteFile(hFile, &tDrawID, sizeof(TILEINFO), &dwByte, NULL);
		WriteFile(hFile, &iOption, sizeof(int), &dwByte, NULL);

	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, _T("Tile 저장 완료"), L"Success", MB_OK);
}

void CTileMgr::Load_Tile()
{
	HANDLE	hFile = CreateFile(L"../Resources/Data/Tile.dat", // 파일 이름이 포함된 경로
		GENERIC_READ,		// 파일 접근 모드(GENERIC_WRITE : 쓰기, GENERIC_READ : 읽기)
		NULL,				// 공유 방식(파일이 열려 있는 상태에서 다른 프로세스가 오픈 할 때 허가하는 것에 대해 설정, 지정하지 않을 경우 NULL)
		NULL,				// 보안 속성(기본값인 경우 NULL)
		OPEN_EXISTING,		// 파일이 없을 경우 파일을 생성하여 저장(OPEN_EXISTING : 파일이 있을 경우에만 로드)
		FILE_ATTRIBUTE_NORMAL,	// 파일 속성(아무런 속성이 없는 일반 파일)
		NULL);				// 생성될 파일의 속성ㅇ르 제공할 템플릿 파일

	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(g_hWnd, _T("Load Tile File"), L"Fail", MB_OKCANCEL);
		return;
	}

	DWORD	dwByte(0);		// eof 역할

	Release();

	INFO		tInfo{};
	TILEINFO	tDrawID;
	int			iOption(0);

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, nullptr);
		ReadFile(hFile, &tDrawID, sizeof(TILEINFO), &dwByte, NULL);
		ReadFile(hFile, &iOption, sizeof(int), &dwByte, NULL);

		if (0 == dwByte)
			break;

		CObj* pTile = CAbstractFactory<CTile>::Create(tInfo.fX, tInfo.fY);
		dynamic_cast<CTile*>(pTile)->Set_DrawID(tDrawID.iDrawIDX, tDrawID.iDrawIDY);
		dynamic_cast<CTile*>(pTile)->Set_Option(iOption);

		m_vecTile.push_back(pTile);
		pTile->Initialize();
	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, _T("Load 완료"), L"Success", MB_OK);
}

void CTileMgr::Clear_Tile()
{
	for (auto& pTile : m_vecTile)
	{
		dynamic_cast<CTile*>(pTile)->Set_Option(ERASE);
	}
}
