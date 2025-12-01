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

	CObj* Get_Owner() const { return m_pOwner; }
	RECT  Get_AttackRect() const { return m_tAttackRect; }
	float Get_Angle() const { return m_fAngle; }

protected:
	CObj*			m_pOwner;

	float			m_fOffsetX;
	float			m_fOffsetY;

	// 마우스 따라다닐 각도
	float			m_fAngle;

	// 공격 범위
	RECT			m_tAttackRect;
};

