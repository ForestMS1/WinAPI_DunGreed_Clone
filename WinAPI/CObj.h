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
	INFO* Get_Info() 													{ return &m_tInfo; }
	void Set_Info(float _fX, float _fY, float _fCX, float _fCY)			{ m_tInfo.fX = _fX; m_tInfo.fY = _fY; m_tInfo.fCX = _fCX; m_tInfo.fCY = _fCY;}
	RECT* Get_Rect() 													{ return &m_tRect; }
	Vec2 Get_Pos() const												{ return Vec2(m_tInfo.fX, m_tInfo.fY); }
	void Set_Pos(float _fX, float _fY)									{ m_tInfo.fX = _fX; m_tInfo.fY = _fY; }
	void Set_PosY(float _fY)											{ m_tInfo.fY += _fY; }
	void Set_PosX(float _fX)											{ m_tInfo.fX += _fX; }
	void Set_Scale(float _fCX, float _fCY)								{ m_tInfo.fCX = _fCX;  m_tInfo.fCY = _fCY; }
	bool IsDead() const													{ return m_bIsDead; }
	void SetDead()														{ m_bIsDead = true; }
	bool IsFlipped() const 												{ return m_bIsFlipped; }
	RENDERID Get_RenderID() const										{ return m_eRender; }
	void Update_Rect();
	void Move_Frame();
	void Move_Frame_No_Loop();
	float Get_MaxHp() const												{ return m_fMaxHp; }
	float Get_CurHp() const												{ return m_fCurHp; }
	wstring Get_FrameKey() const										{ return m_wsFrameKey; }
	int Get_FrameWidth() const											{ return m_iFrameWidth; }
	int Get_FrameHeight() const											{ return m_iFrameHeight; }


protected:
	// 좌표, 크기 관련
	INFO		m_tInfo;
	RECT		m_tRect;


	// 수치 관련
	float		m_fSpeed;
	float		m_fMaxHp;
	float		m_fCurHp;


	// 애니메이션
	FRAME		m_tFrame;
	wstring		m_wsFrameKey;	
	bool		m_bIsFlipped; // 좌 우 반전
	float			m_iFrameWidth;
	float			m_iFrameHeight;
	//렌더순서
	RENDERID	m_eRender;


	// 생사 여부
	bool m_bIsDead;
};

