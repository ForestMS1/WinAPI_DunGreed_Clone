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
	Vec2 Get_Pos() const												{ return Vec2(m_tInfo.fX, m_tInfo.fY); }
	Vec2 Get_Scale()const												{ return Vec2(m_tInfo.fCX, m_tInfo.fCY); }
	void Set_Pos(float _fX, float _fY)									{ m_tInfo.fX = _fX; m_tInfo.fY = _fY; }
	void Set_Pos(Vec2 vVec)												{ m_tInfo.fX = vVec.fX; m_tInfo.fY = vVec.fY; }
	void Set_Scale(float _fCX, float _fCY)								{ m_tInfo.fCX = _fCX;  m_tInfo.fCY = _fCY; }
	bool IsDead() const													{ return m_bIsDead; }
	void SetDead()														{ m_bIsDead = true; }

	void Update_Rect();
	void Move_Frame();


protected:
	// 좌표, 크기 관련
	INFO		m_tInfo;
	RECT		m_tRect;


	// 수치 관련
	float		m_fSpeed;

	// 애니메이션
	FRAME		m_tFrame;
	wstring		m_wsFrameKey;	
	bool		m_bIsFlipped; // 좌 우 반전


	// 생사 여부
	bool m_bIsDead;
};

