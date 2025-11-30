#pragma once
#include "CObj.h"
#include "CWeapon.h"
#include "CRunEffect.h"
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
	bool IsGround() const { return m_bIsGround; }

	STATE Get_State() const { return m_eCurState;  }

private:
	void Key_Input();
	void Motion_Change();
	void Jump();
	bool ToMouse();

private:
	CWeapon*			m_pWeapon;
	CRunEffect*			m_pRunEffect;
	//플레이어가 장착한 무기, 플레이어의 이펙트 등을 담을 vector
	vector<CObj*>		m_vecOwned;

private:
	STATE				m_ePreState;
	STATE				m_eCurState;

	// 점프
	float				m_v0;	 // 점프 초기속력
	float				m_ft;	 // 흐르는 시간
	float				m_fAcct; // 점프 누적 시간
	bool				m_bJump; // 플레이어가 의도적으로 점프키를 눌러 점프했고 점프 중인 상태인가?
	bool				m_bIsGround; //플레이어가 땅에 닿아있는가
	// 하단점프
	bool				m_bBottomJump;


	// 애니메이션 잘라올 사이즈
	int m_iFrameWidth;
	int m_iFrameHeight;
	
};

