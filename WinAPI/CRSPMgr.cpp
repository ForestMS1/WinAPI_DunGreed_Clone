#include "pch.h"
#include "CRSPMgr.h"
#include "CPlayer.h"
#include "CRSP.h"
#include "CNifleHeim.h"
CRSPMgr* CRSPMgr::m_pInstance = nullptr;

CRSPMgr::CRSPMgr() : m_ePlayerSelect(SELECT_END), m_eEnemySelect(SELECT_END)
, m_bIsPlayerWin(false), m_bIsEnemyWin(false), m_pNifleHeim(nullptr)
{

}
CRSPMgr::~CRSPMgr()
{

}

void CRSPMgr::Initialize()
{
}

int CRSPMgr::Update()
{
	switch (m_ePlayerSelect)
	{
	case ROCK:
		if (m_eEnemySelect == SCISSORS)
		{
			m_bIsPlayerWin = true;
			m_bIsEnemyWin = false;
		}
		else if (m_eEnemySelect == PAPER)
		{
			m_bIsPlayerWin = false;
			m_bIsEnemyWin = true;
		}
		break;
	case SCISSORS:
		if (m_eEnemySelect == ROCK)
		{
			m_bIsPlayerWin = false;
			m_bIsEnemyWin = true;
		}
		else if (m_eEnemySelect == PAPER)
		{
			m_bIsPlayerWin = true;
			m_bIsEnemyWin = false;
		}
		break;
	case PAPER:
		if (m_eEnemySelect == ROCK)
		{
			m_bIsPlayerWin = true;
			m_bIsEnemyWin = false;
		}
		else if (m_eEnemySelect == SCISSORS)
		{
			m_bIsPlayerWin = false;
			m_bIsEnemyWin = true;
		}
		break;
	default:
		m_bIsPlayerWin = false;
		m_bIsEnemyWin = false;
		break;
	}

	//가위바위보 했는데 지거나 비겼음
	if (m_ePlayerSelect != SELECT_END && !m_bIsPlayerWin)
	{
		if (dynamic_cast<CPlayer*>(GET(CPlayerMgr)->GetPlayer()) != nullptr)
		{
			dynamic_cast<CPlayer*>(GET(CPlayerMgr)->GetPlayer())->OnDamage(10);
		}
		m_ePlayerSelect = SELECT_END;
		m_eEnemySelect = SELECT_END;
		m_dwLoseTime = GetTickCount();
	}
	else if (m_ePlayerSelect != SELECT_END && (m_bIsPlayerWin && !m_bIsEnemyWin))
	{
		if (dynamic_cast<CNifleHeim*>(m_pNifleHeim) != nullptr)
		{
			dynamic_cast<CNifleHeim*>(m_pNifleHeim)->OnDamage(50);
		}
		m_ePlayerSelect = SELECT_END;
		m_eEnemySelect = SELECT_END;
		m_dwLoseTime = GetTickCount();
	}

	if (m_dwLoseTime + 2000 < GetTickCount())
	{
		dynamic_cast<CRSP*>(GET(CUIMgr)->Find_UI(L"RSP"))->SetPlay();
	}
	return 0;
}

void CRSPMgr::Late_Update()
{
}

void CRSPMgr::Render(HDC hDC)
{
}

void CRSPMgr::Release()
{
}
