#pragma once
#include "Define.h"
class CUI
{
public:
	CUI();
	virtual ~CUI();

public:
	virtual void Initialize()							PURE;
	virtual void Update()								PURE;
	virtual void Late_Update()							PURE;
	virtual void Render(HDC hDC)						PURE;
	virtual void Release()								PURE;

public:
	INFO* Get_Info() { return &m_tInfo; }
	void Set_Info(float _fX, float _fY, float _fCX, float _fCY) { m_tInfo.fX = _fX; m_tInfo.fY = _fY; m_tInfo.fCX = _fCX; m_tInfo.fCY = _fCY; }
	RECT Get_Rect() const { return m_tRect; }
	Vec2 Get_Pos() const { return Vec2(m_tInfo.fX, m_tInfo.fY); }
	void Set_Pos(float _fX, float _fY) { m_tInfo.fX = _fX; m_tInfo.fY = _fY; }
	void Set_Scale(float _fCX, float _fCY) { m_tInfo.fCX = _fCX;  m_tInfo.fCY = _fCY; }
	bool IsOpen() const { return m_bIsOpen; }
	void Open() { m_bIsOpen = true; }
	void Close() { m_bIsOpen = false; }

	void Update_Rect();
	void Move_Frame();


protected:
	// 좌표, 크기 관련
	INFO		m_tInfo;
	RECT		m_tRect;

	// 애니메이션
	FRAME		m_tFrame;
	wstring		m_wsFrameKey;
	bool		m_bIsFlipped; // 좌 우 반전


	// UI 활성화 여부
	bool m_bIsOpen;
};

