#include "pch.h"
#include "CLineMgr.h"

CLineMgr* CLineMgr::m_pInstance = nullptr;

CLineMgr::CLineMgr() : m_bClicked(false)
{

}
CLineMgr::~CLineMgr()
{
	Release();
}

void CLineMgr::Initialize()
{
	for (auto iter = m_LineList.begin(); iter != m_LineList.end(); ++iter)
	{
		if((*iter) != nullptr)
			(*iter)->Initialize();
	}
}

void CLineMgr::Update()
{
	POINT		ptMouse{};
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	//ptMouse.x += (int)GET(CCamera)->Get_ScrollX();
	//ptMouse.y += (int)GET(CCamera)->Get_ScrollY();
	Vec2 Real = GET(CCamera)->GetRealPos(Vec2(ptMouse.x, ptMouse.y));
	ptMouse.x = (int)Real.fX;
	ptMouse.y = (int)Real.fY;

	if (GetAsyncKeyState(VK_LBUTTON))
	{
		m_tPoint[LEFT].fX = (float)ptMouse.x;
		m_tPoint[LEFT].fY = (float)ptMouse.y;
		m_bClicked = true;
	}
	if (GetAsyncKeyState(VK_RBUTTON))
	{
		m_tPoint[RIGHT].fX = (float)ptMouse.x;
		m_tPoint[RIGHT].fY = (float)ptMouse.y;

		if ((m_tPoint[LEFT].fX) && (m_tPoint[LEFT].fY))
			m_LineList.push_back(new CLine(POINT{ (int)m_tPoint[LEFT].fX, (int)m_tPoint[LEFT].fY },
				POINT{ (int)m_tPoint[RIGHT].fX, (int)m_tPoint[RIGHT].fY }));

		m_bClicked = false;
		m_tPoint[LEFT].fX = (float)ptMouse.x;
		m_tPoint[LEFT].fY = (float)ptMouse.y;
	}
	if (GetAsyncKeyState(VK_BACK))
	{
		if (!m_LineList.empty())
			m_LineList.pop_back();
	}


	if (GetAsyncKeyState('S'))
	{
		Save_Line();
		return;
	}

	if (GetAsyncKeyState('L'))
	{
		Load_Line();
		return;
	}
	for (auto iter = m_LineList.begin(); iter != m_LineList.end(); ++iter)
	{
		if ((*iter) != nullptr)
			(*iter)->Update();
	}
}

void CLineMgr::Late_Update()
{
	for (auto iter = m_LineList.begin(); iter != m_LineList.end(); ++iter)
	{
		if ((*iter) != nullptr)
			(*iter)->Late_Update();
	}
}

void CLineMgr::Render(HDC hDC)
{
	for (auto iter = m_LineList.begin(); iter != m_LineList.end(); ++iter)
	{
		if ((*iter) != nullptr)
			(*iter)->Render(hDC);
	}
}

void CLineMgr::Release()
{
	for (auto iter = m_LineList.begin(); iter != m_LineList.end(); ++iter)
	{
		Safe_Delete((*iter));
	}
	m_LineList.clear();
}

void CLineMgr::Add_Line(CLine* pLine)
{
	if(pLine != nullptr)
		m_LineList.push_back(pLine);
}

bool CLineMgr::Collision_Line(CObj* pPlayer, float* pY)
{
	if (m_LineList.empty())
		return false;
	float fFantaStickMagicNumber = 18.f; // 미친 간격
	float fX = pPlayer->Get_Info()->fX;
	float fY = pPlayer->Get_Info()->fY;
	float bottom = pPlayer->Get_Rect()->bottom;
	CLine* pTarget = nullptr;

	float minDist = 0.f;
	for (auto& pLine : m_LineList)
	{
		if ((fX >= pLine->Get_Left().x &&
			fX <= pLine->Get_Right().x))
		{
			int		x1 = pLine->Get_Left().x;
			int		y1 = pLine->Get_Left().y;
			int		x2 = pLine->Get_Right().x;
			int		y2 = pLine->Get_Right().y;

			*pY = ((y2 - y1) / (x2 - x1)) * (fX - x1) + y1;

			if (*pY + fFantaStickMagicNumber > bottom && *pY - fFantaStickMagicNumber < bottom)
			{
				float offset = pPlayer->Get_Info()->fCY * 0.5f + 8.f;
				pPlayer->Set_Pos(fX, *pY - offset);
				pTarget = pLine;
				return true;
			}
		}
	}

	if(pTarget == nullptr)
		return false;
}
void CLineMgr::Save_Line()
{
	// 파일 개방
	HANDLE	hFile = CreateFile(L"../Resources/Data/TownLine.dat", // 파일 이름이 포함된 경로
		GENERIC_WRITE,		// 파일 접근 모드(GENERIC_WRITE : 쓰기, GENERIC_READ : 읽기)
		NULL,				// 공유 방식(파일이 열려 있는 상태에서 다른 프로세스가 오픈 할 때 허가하는 것에 대해 설정, 지정하지 않을 경우 NULL)
		NULL,				// 보안 속성(기본값인 경우 NULL)
		CREATE_ALWAYS,		// 파일이 없을 경우 파일을 생성하여 저장(OPEN_EXISTING : 파일이 있을 경우에만 로드)
		FILE_ATTRIBUTE_NORMAL,	// 파일 속성(아무런 속성이 없는 일반 파일)
		NULL);				// 생성될 파일의 속성ㅇ르 제공할 템플릿 파일

	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(g_hWnd, _T("Save File"), L"Fail", MB_OKCANCEL);
		return;
	}

	DWORD	dwByte(0);		// eof 역할


	for (auto& pLine : m_LineList)
	{
		LINE_DATA data{};
		data.tLeft = pLine->Get_Left();
		data.tRight = pLine->Get_Right();

		WriteFile(hFile, &data, sizeof(LINE_DATA), &dwByte, nullptr);
	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, _T("Save 완료"), L"Success", MB_OK);
}
void CLineMgr::Load_Line()
{
	// 파일 개방
	HANDLE	hFile = CreateFile(L"../Resources/Data/TownLine.dat", // 파일 이름이 포함된 경로
		GENERIC_READ,		// 파일 접근 모드(GENERIC_WRITE : 쓰기, GENERIC_READ : 읽기)
		NULL,				// 공유 방식(파일이 열려 있는 상태에서 다른 프로세스가 오픈 할 때 허가하는 것에 대해 설정, 지정하지 않을 경우 NULL)
		NULL,				// 보안 속성(기본값인 경우 NULL)
		OPEN_EXISTING,		// 파일이 없을 경우 파일을 생성하여 저장(OPEN_EXISTING : 파일이 있을 경우에만 로드)
		FILE_ATTRIBUTE_NORMAL,	// 파일 속성(아무런 속성이 없는 일반 파일)
		NULL);				// 생성될 파일의 속성ㅇ르 제공할 템플릿 파일

	if (hFile == INVALID_HANDLE_VALUE)
	{
		//MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OKCANCEL);
		return;
	}

	DWORD	dwByte(0);		// eof 역할

	Release();

	LINE_DATA data{};

	while (true)
	{
		ReadFile(hFile, &data, sizeof(LINE_DATA), &dwByte, nullptr);

		if (0 == dwByte)
			break;

		m_LineList.push_back(new CLine(data.tLeft, data.tRight));
	}

	CloseHandle(hFile);
	//MessageBox(g_hWnd, _T("Load 완료"), L"Success", MB_OK);
}