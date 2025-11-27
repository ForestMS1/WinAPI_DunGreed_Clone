#pragma once
#include "CObj.h"
class CPlayer : public CObj
{
public:
	enum STATE {IDLE, WALK, JUMP, FLY, ATTACK, HIT, DEAD, END};
public:
	CPlayer();
	virtual~CPlayer();
public:
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	void Key_Input();
	void Motion_Change();

private:
	STATE				m_ePreState;
	STATE				m_eCurState;

	//점프 속력
	float				m_v0;
	float				m_ft;
	float				m_fAcct;
	bool				m_bJump;
	
};

