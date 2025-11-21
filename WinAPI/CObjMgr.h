#pragma once
#include "CObj.h"

class CObjMgr
{
	SINGLE(CObjMgr)
public:
	void Initialize();
	void Update();
	void Late_Update();
	void Render(HDC hDC);
	void Release();

	void AddObject(OBJ_LAYER eLayer, CObj* pObj);
	void DeleteLayerObj(OBJ_LAYER eLayer);

private:
	list<CObj*>		m_ObjLayer[OBJ_END];
};

