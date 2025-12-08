#pragma once
#include "CWeapon.h"
class CGatlingGun :
    public CWeapon
{
public:
	CGatlingGun();
	CGatlingGun(CObj* pOwner);
	~CGatlingGun();
public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	CWeapon* Clone() override { return new CGatlingGun(*this); }
private:
	DWORD	m_dwShootDelay;
	DWORD   m_dwSoundTick;
};

