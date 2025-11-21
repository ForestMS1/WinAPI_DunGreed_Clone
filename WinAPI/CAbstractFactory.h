#pragma once
#include "CObj.h"
class CAbstractFactory
{
	template<typename T>
	static T* Create(float fX, float fY)
	{
		CObj* pObj = new T;
		pObj.Set_Pos(fX, fY);
		pObj->Initialize();
		return ;
	}

};

