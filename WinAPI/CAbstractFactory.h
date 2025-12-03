#pragma once
#include "CObj.h"
#include "CBullet.h"
template<typename T>
class CAbstractFactory
{
public:
	static CObj* Create(float fX, float fY)
	{
		CObj* pObj = new T;
		pObj->Set_Pos(fX, fY);
		pObj->Initialize();
		return pObj;
	}
	static CBullet* CreateBullet(float fX, float fY, float fAngle)
	{
		CBullet* pObj = new T;
		pObj->Set_Pos(fX, fY);
		pObj->Set_Angle(fAngle);
		pObj->Initialize();
		return pObj;
	}
};

