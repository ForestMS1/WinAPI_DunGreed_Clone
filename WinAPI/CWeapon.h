#pragma once
#include "CObj.h"
class CWeapon : public CObj
{
public:
	CWeapon();
	CWeapon(CObj* pOwner);
	virtual ~CWeapon();
public:
	// CObj을(를) 통해 상속됨
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

protected:
	CObj*			m_pOwner;

	float			m_fOffsetX;
	float			m_fOffsetY;
	
	// 애니메이션
	float			m_iFrameWidth;
	float			m_iFrameHeight;

	// 마우스 따라다닐 각도
	float			m_fAngle;
};

