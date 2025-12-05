#pragma once

#include "CObj.h"

class CWeapon;
class CCollisionMgr
{
public:
	static void Collision_Rect(vector<CObj*> _Dst, list<CObj*> _Src);
	static void Collision_Weapon(CWeapon* pWeapon, list<CObj*> _Src);
	static  void Collision_Bullet(list<CObj*> _Dst, list<CObj*> _Src);
	static void MonsterDetecPlayer(CObj* pPlayer, list<CObj*> _Src);
	static void Collision_RectEx(list<CObj*> _Dst, list<CObj*> _Src);
	static bool Collision_RectTile(CObj* pPlayer, vector<CObj*>& _Src);
	static bool	Check_Rect(CObj* pDst, CObj* pSrc, float* pX, float* pY);
	static bool Check_Rect(CObj* pDst, CObj* pSrc);
	static bool Check_Ground(CObj* pDst, vector<CObj*>& vecSrc);
	static bool Check_Circle(CObj* pDst, CObj* pSrc);
	static void Collision_Circle(list<CObj*> _Dst, list<CObj*> _Src);

};


