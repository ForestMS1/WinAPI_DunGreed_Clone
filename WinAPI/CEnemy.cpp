#include "pch.h"
#include "CEnemy.h"

CEnemy::CEnemy() : m_fMaxHp(0.f), m_fCurHp(0.f)
{
	m_eRender = GAMEOBJECT;
}

CEnemy::~CEnemy()
{
}
