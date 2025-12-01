#pragma once
#include "CWeapon.h"
class CCosmosSword :
    public CWeapon
{
public:
	CCosmosSword(CObj* pOwner);
	~CCosmosSword();
public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
private:
	CObj* m_pSwingFX;
};

