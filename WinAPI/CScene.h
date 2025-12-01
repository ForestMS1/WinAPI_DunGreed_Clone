#pragma once
#include "Define.h"

class CScene abstract
{
public:
	CScene();
	virtual~CScene();
public:
	virtual void Initialize()							PURE;
	virtual void Update()								PURE;
	virtual void Late_Update()							PURE;
	virtual void Render(HDC hDC)						PURE;
	virtual void Release()								PURE;

	void SetSceneID(SCENEID Id) { SCENEID = Id; }
	SCENEID GetSceneID() const { return SCENEID; }

protected:
	SCENEID	 SCENEID;
};

