#include "pch.h"
#include "CLineMgr.h"

CLineMgr* CLineMgr::m_pInstance = nullptr;

CLineMgr::CLineMgr()
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