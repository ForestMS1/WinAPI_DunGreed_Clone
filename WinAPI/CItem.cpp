#include "pch.h"
#include "CItem.h"

CItem::CItem():
m_fAddAtk(0.f),
m_fAddDfs(0.f),
m_fAddHp(0.f),
m_fShopPrice(0)
{
}

CItem::~CItem()
{
}

void CItem::Initialize()
{
}

int CItem::Update()
{
	return 0;
}

void CItem::Late_Update()
{
}

void CItem::Render(HDC hDC)
{
}

void CItem::Release()
{
}
