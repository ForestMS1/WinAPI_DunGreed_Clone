#pragma once
#include "Define.h"
class CObj abstract
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual void Initialize()					PURE;
	virtual void Update()						PURE;
	virtual void Late_Update()					PURE;
	virtual void Render(HDC hDC)				PURE;
	virtual void Release()						PURE;

public:
	INFO Get_Info() const						{ return m_tInfo; }
	void Set_Info(float _fX, float _fY)			{ m_tInfo.fX = _fX; m_tInfo.fY = _fY; }
	RECT Get_Rect() const						{ return m_tRect; }
	void Update_Rect();


private:
	INFO		m_tInfo;
	RECT		m_tRect;
};

