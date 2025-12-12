#include "pch.h"
#include "CItem.h"

CItem::CItem():
m_fAddAtk(0.f),
m_fAddDfs(0.f),
m_fAddHp(0.f),
m_fShopPrice(0),
m_bIsDrop(false)
{
	m_eRender = GAMEOBJECT;
}

CItem::~CItem()
{
}

void CItem::Initialize()
{
}

int CItem::Update()
{
	if (m_bIsDrop)
		m_tInfo.fY += GRAVITY;
	Update_DetectRect();

	return 0;
}

void CItem::Late_Update()
{
	if (m_bIsDrop)
	{
		CCollisionMgr::Collision_RectTile(this, GET(CTileMgr)->GetVecTile());
		float py;
		GET(CLineMgr)->Collision_Line(this, &py);
	}
}

void CItem::Render(HDC hDC)
{
}

void CItem::Release()
{
}


void CItem::Update_DetectRect()
{
	m_tDetectRect.left = m_tInfo.fX - m_fDetectfCX * 0.5f;
	m_tDetectRect.top = m_tInfo.fY - m_fDetectfCY * 0.5f;
	m_tDetectRect.right = m_tInfo.fX + m_fDetectfCX * 0.5f;
	m_tDetectRect.bottom = m_tInfo.fY + m_fDetectfCY * 0.5f;
}
void CItem::ToPlayerAngle()
{
	float	fWidth(0.f), fHeight(0.f), fDiagonal(0.f);

	fWidth = GET(CPlayerMgr)->GetPlayer()->Get_Info()->fX - m_tInfo.fX;
	fHeight = GET(CPlayerMgr)->GetPlayer()->Get_Info()->fY - m_tInfo.fY;

	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	m_fAngle = acosf(fWidth / fDiagonal);
	if (GET(CPlayerMgr)->GetPlayer()->Get_Info()->fY > m_tInfo.fY)
		m_fAngle = 2.f * PI - m_fAngle;
}