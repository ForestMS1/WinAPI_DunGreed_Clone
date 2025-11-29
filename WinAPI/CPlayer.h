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
	void Jump();
	void ToMouse();

private:
	STATE				m_ePreState;
	STATE				m_eCurState;

	// 점프
	float				m_v0;	 // 점프 초기속력
	float				m_ft;	 // 흐르는 시간
	float				m_fAcct; // 점프 누적 시간
	bool				m_bJump; // 플레이어가 의도적으로 점프키를 눌러 점프했고 점프 중인 상태인가?
	// 하단점프
	bool				m_bBottomJump;


	// 애니메이션 잘라올 사이즈
	int m_iFrameWidth;
	int m_iFrameHeight;
	
};

