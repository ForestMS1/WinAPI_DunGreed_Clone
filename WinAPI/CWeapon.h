#pragma once
#include "CItem.h"
class CWeapon : public CItem
{
public:
	CWeapon();
	virtual ~CWeapon();
public:

	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	CItem* Clone() override { return new CWeapon(*this); }

	RECT*  Get_AttackRect()  { return &m_tAttackRect; }
	INFO* GET_AttackInfo() { return &m_tAttackInfo; }
	void Update_AttackRect();
	float Get_Angle() const { return m_fAngle; }
	float Get_Damage() const { return m_fDamage; }
	void Set_AttackCount() { m_iCurAttackCount++; }
	int Get_MaxAttackCount() const { return m_iMaxAttackCount; }
	int Get_CurAttackCount() const { return m_iCurAttackCount; }
protected:

	float			m_fOffsetX;
	float			m_fOffsetY;

	// 마우스 따라다닐 각도
	float			m_fAngle;

	// 공격 범위
	RECT			m_tAttackRect;
	INFO			m_tAttackInfo;
	// 공격력
	float			m_fDamage;
	int				m_iMaxAttackCount; // 무기의 한번에 줄 수 있는 최대 공격횟수
	int				m_iCurAttackCount;

	// 데미지 준 횟수
};

