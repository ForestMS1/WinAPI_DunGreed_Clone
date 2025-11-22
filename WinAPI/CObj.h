#pragma once
#include "Define.h"
class CObj abstract
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual void Initialize()							PURE;
	virtual int Update()								PURE;
	virtual void Late_Update()							PURE;
	virtual void Render(HDC hDC)						PURE;
	virtual void Release()								PURE;

public:
	INFO Get_Info() const												{ return m_tInfo; }
	void Set_Info(float _fX, float _fY, float _fCX, float _fCY)			{ m_tInfo.fX = _fX; m_tInfo.fY = _fY; m_tInfo.fCX = _fCX; m_tInfo.fCY = _fCY;}
	RECT Get_Rect() const												{ return m_tRect; }
	void Set_Pos(float _fX, float _fY)									{ m_tInfo.fX = _fX; m_tInfo.fY = _fY; }

	void Update_Rect();


protected:
	// 좌표, 크기 관련
	INFO		m_tInfo;
	RECT		m_tRect;


	// 수치 관련
	float		m_fSpeed;

};

