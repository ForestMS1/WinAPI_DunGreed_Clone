#include "pch.h"
#include "CCollisionMgr.h"
#include "CTile.h"
#include "CCamera.h"
#include "CEnemy.h"
#include "CWeapon.h"
void CCollisionMgr::Collision_Rect(list<CObj*> _Dst, list<CObj*> _Src)
{

	RECT	rc{};

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, Dst->Get_Rect(), Src->Get_Rect()))
			{
				//Dst->Set_Dead();
				//Src->Set_Dead();
			}
		}
	}
}

void CCollisionMgr::Collision_Bullet(list<CObj*> _Dst, list<CObj*> _Src)
{

	RECT	rc{};

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (IntersectRect(&rc, Dst->Get_Rect(), Src->Get_Rect()))
			{
				CUnit* pTarget = nullptr;
				pTarget = dynamic_cast<CUnit*>(Dst);
				CBullet* pBullet = nullptr;
				pBullet = dynamic_cast<CBullet*>(Src);
				if (pTarget != nullptr && pBullet != nullptr)
				{
					pTarget->OnDamage(pBullet->Get_Damage());
					pBullet->SetDead();
				}
			}
		}
	}
}
void CCollisionMgr::Collision_Weapon(CWeapon* pWeapon, list<CObj*> _Src)
{

	RECT	rc{};

	for (auto& Src : _Src)
	{
		if (IntersectRect(&rc, pWeapon->Get_AttackRect(), Src->Get_Rect()))
		{
			CObj* pEnemy = nullptr;
			pEnemy = dynamic_cast<CEnemy*>(Src);
			if (pEnemy != nullptr)
			{
				if (pWeapon->Get_MaxAttackCount() > pWeapon->Get_CurAttackCount())
				{
					pWeapon->Set_AttackCount();
					dynamic_cast<CEnemy*>(pEnemy)->OnDamage(pWeapon->Get_Damage());
				}
			}
		}
	}
}

void CCollisionMgr::MonsterDetecPlayer(CObj* pPlayer, list<CObj*> _Src)
{

	RECT	rc{};

	for (auto& Src : _Src)
	{
		if (IntersectRect(&rc, pPlayer->Get_Rect(), dynamic_cast<CEnemy*>(Src)->GetDetectRect()))
		{
			if (Src != nullptr)
			{
				dynamic_cast<CEnemy*>(Src)->InPlayer();
			}
		}
		else
		{
			if (Src != nullptr)
			{
				dynamic_cast<CEnemy*>(Src)->OutPlayer();
			}
		}
	}
}

void CCollisionMgr::Collision_RectEx(list<CObj*> _Dst, list<CObj*> _Src)
{
	float	fWidth(0.f), fHeight(0.f);

	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Rect(Dst, Src, &fWidth, &fHeight))
			{
				// 상 하 충돌
				if (fWidth > fHeight)
				{
					// 상 충돌
					if (Dst->Get_Info()->fY < Src->Get_Info()->fY)
					{
						Dst->Set_PosY(-fHeight);
					}
					// 하 충돌
					else
					{
						Dst->Set_PosY(fHeight);
					}
				}

				// 좌 우 충돌
				else
				{
					// 좌 충돌
					if (Dst->Get_Info()->fX < Src->Get_Info()->fX)
					{
						Dst->Set_PosX(-fWidth);
					}
					// 우 충돌
					else
					{
						Dst->Set_PosX(fWidth);
					}
				}
			}
		}
	}
}

// 플레이어가 땅에 닿으면 true, 다른충돌은 false 리턴
bool CCollisionMgr::Collision_RectTile(CObj* pPlayer, vector<CObj*>& _Src)
{
	float	fWidth(0.f), fHeight(0.f);

	for (auto& Src : _Src)
	{
		if (Check_Rect(pPlayer, Src, &fWidth, &fHeight) && dynamic_cast<CTile*>(Src)->Get_Option() == 1)
		{
			// 상 하 충돌
			if (fWidth > fHeight)
			{
				// 상 충돌
				if (pPlayer->Get_Info()->fY < Src->Get_Info()->fY)
				{
					pPlayer->Set_PosY(-fHeight-GRAVITY);
					return true;
				}
				// 하 충돌
				else
				{
					pPlayer->Set_PosY(fHeight+GRAVITY);
				}
			}

			// 좌 우 충돌
			else
			{
				// 좌 충돌
				if (pPlayer->Get_Info()->fX < Src->Get_Info()->fX)
				{
					pPlayer->Set_PosX(-fWidth);
				}
				// 우 충돌
				else
				{
					pPlayer->Set_PosX(fWidth);
				}
			}
		}
	}
	return false;
}

bool CCollisionMgr::Check_Rect(CObj* pDst, CObj* pSrc, float* pX, float* pY)
{
	float		fWidth = fabsf(pDst->Get_Info()->fX - pSrc->Get_Info()->fX);
	float		fHeight = fabsf(pDst->Get_Info()->fY - pSrc->Get_Info()->fY);

	float		fRadiusX = (pDst->Get_Info()->fCX + pSrc->Get_Info()->fCX) * 0.5f;
	float		fRadiusY = (pDst->Get_Info()->fCY + pSrc->Get_Info()->fCY) * 0.5f;

	if (fRadiusX >= fWidth && fRadiusY >= fHeight)
	{
		*pX = fRadiusX - fWidth;
		*pY = fRadiusY - fHeight;

		return true;
	}

	return false;
}

bool CCollisionMgr::Check_Ground(CObj* pDst, vector<CObj*>& vecSrc)
{
	float fHeight(0.f), fRadiusY(0.f);
	for (auto& pTile : vecSrc)
	{
		fHeight = fabsf(pDst->Get_Info()->fY - pTile->Get_Info()->fY);
		fRadiusY = (pDst->Get_Info()->fCY + pTile->Get_Info()->fCY) * 0.5f;
		if (fRadiusY >= fHeight)
		{
			return true;
		}
	}

	return false;
}

bool CCollisionMgr::Check_Circle(CObj* pDst, CObj* pSrc)
{
	float	fRadius = (pDst->Get_Info()->fCX + pSrc->Get_Info()->fCX) * 0.5f;

	float	fWidth = fabsf(pDst->Get_Info()->fX - pSrc->Get_Info()->fX);
	float	fHeight = fabsf(pDst->Get_Info()->fY - pSrc->Get_Info()->fY);

	float	fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

	return fRadius >= fDiagonal;
}

void CCollisionMgr::Collision_Circle(list<CObj*> _Dst, list<CObj*> _Src)
{
	for (auto& Dst : _Dst)
	{
		for (auto& Src : _Src)
		{
			if (Check_Circle(Dst, Src))
			{
				//Dst->Set_Dead();
				//Src->Set_Dead();
			}
		}
	}
}
