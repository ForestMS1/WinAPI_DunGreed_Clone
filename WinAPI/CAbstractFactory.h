#pragma once
#include "CObj.h"
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

};

