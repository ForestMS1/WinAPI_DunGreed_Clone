#pragma once
#include "CWeapon.h"
#include "CSwingFX.h"
class CCosmosSword :
    public CWeapon
{
public:
	CCosmosSword();
	~CCosmosSword();
public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	CWeapon* Clone() override { return new CCosmosSword(*this); }

private:
	CObj* m_pSwingFX;
};

