#pragma once
#include "CWeapon.h"
#include "CSwingFX.h"
class CCosmosSword :
    public CWeapon
{
public:
	CCosmosSword();
	CCosmosSword(const CCosmosSword& rhs)
	{
		m_pSwingFX = dynamic_cast<CSwingFX*>(rhs.m_pSwingFX)->Clone();
	}
	~CCosmosSword();
public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
	CWeapon* Clone() override 
	{ 
		CCosmosSword* pSword = new CCosmosSword(*this);
		pSword->Initialize();
		return pSword; 
	}

private:
	CObj* m_pSwingFX;
	DWORD m_dwSoundTick;
	UINT m_SoundIndex;

	bool isAttack;
};

