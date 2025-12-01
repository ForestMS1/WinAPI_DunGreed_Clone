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

	void SetName(wstring name) { m_wsName = name; }
	wstring GetName() const { return m_wsName; }

protected:
	wstring m_wsName;
};

