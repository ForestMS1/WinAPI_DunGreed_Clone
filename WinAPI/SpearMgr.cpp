#include "pch.h"
#include "SpearMgr.h"
#include "CBelial.h"
#include "CBelialSpear.h"

SpearMgr::SpearMgr() : m_pOwner(nullptr)
{

}

SpearMgr::SpearMgr(CEnemy* pBelial)
{
	m_pOwner = pBelial;

}

SpearMgr::~SpearMgr()
{
	Release();
}

void SpearMgr::Initialize()
{
	float offsetY = 300.f;
	m_tInfo.fX = m_pOwner->Get_Info()->fX;
	m_tInfo.fY = m_pOwner->Get_Info()->fY - offsetY;
	m_tInfo.fCX = 900.f;
	m_tInfo.fCY = 190.f;
	__super::Update_Rect();

	int spearCnt = 5;
	GET(CResourceMgr)->Insert_Png(L"../Resources/Images/Unit/Enemy/Belial/SkellBossSword.png", L"SkellBossSword");

	if (m_vecSpear.empty())
	{
		for (size_t i = 0; i < spearCnt; ++i)
		{
			float offset = 200.f;// m_tInfo.fCX / (float)spearCnt;
			CEnemy* pSpear = (CBelialSpear*)CAbstractFactory<CBelialSpear>::Create(m_tRect.left + offset * 0.5f + i * offset, m_tInfo.fY);
			m_vecSpear.push_back(pSpear);
		}
	}
	m_dwSpawnTick = GetTickCount();
}

int SpearMgr::Update()
{
	if (dynamic_cast<CBelial*>(m_pOwner)->GetCurState() == ATTACK_SPEAR)
	{
		for (size_t i = 0; i < m_vecSpear.size(); ++i)
		{
			if (m_dwSpawnTick + 500 < GetTickCount() && dynamic_cast<CBelialSpear*>(m_vecSpear[i])->GetActive() == false)
			{
				float offset = 200.f;
				m_vecSpear[i]->Set_Pos(m_tRect.left + offset * 0.5f + i * offset, m_tInfo.fY);
				m_vecSpear[i]->Initialize();
				dynamic_cast<CBelialSpear*>(m_vecSpear[i])->SetActive(true);
				dynamic_cast<CBelialSpear*>(m_vecSpear[i])->SetEffect(true);
				m_dwSpawnTick = GetTickCount();
			}
			if (dynamic_cast<CBelialSpear*>(m_vecSpear[i])->GetActive())
			{
				m_vecSpear[i]->Update();
			}
		}
	}
	else
	{
		for (size_t i = 0; i < m_vecSpear.size(); ++i)
		{
			dynamic_cast<CBelialSpear*>(m_vecSpear[i])->SetActive(false);
			dynamic_cast<CBelialSpear*>(m_vecSpear[i])->SetEffect(false);
		}
	}

	return 0;
}

void SpearMgr::Late_Update()
{
	for (auto& pSpear : m_vecSpear)
	{
		pSpear->Late_Update();
	}

}

void SpearMgr::Render(HDC hDC)
{
	for (auto& pSpear : m_vecSpear)
	{
		pSpear->Render(hDC);
	}
}

void SpearMgr::Release()
{
	for (auto& pSpear : m_vecSpear)
	{
		Safe_Delete(pSpear);
	}
	m_vecSpear.clear();
}

void SpearMgr::Motion_Change()
{
}
