#pragma once
#include "CUnit.h"
#include "CWeapon.h"
#include "CRunEffect.h"
#include "CUI.h"
class CPlayer : public CUnit
{
public:
	enum STATE {IDLE, WALK, JUMP, DASH, ATTACK, HIT, DEAD, END};
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
	bool Get_IsAttack() const { return m_bAttack; }
	CItem* Get_EquipWeapon() const { return m_pWeapon; }

	void Set_Weapon(CItem* pWeapon) { Safe_Delete(m_pWeapon); m_pWeapon = pWeapon; }
	void SetGold(int gold) { m_iGold = gold; }

	void OnDamage(int dmg) override
	{
		if (m_bIsHit)
			return;
		int result = dmg + (rand() % 5);
		m_fCurHp -= result;
		if (m_fCurHp <= 0.f)
		{
			m_fCurHp = 0.f;
			m_bIsDead = true;
		}

		m_dwLastHitTime = GetTickCount();
		m_bIsHit = true;
		GET(CSoundMgr)->PlaySoundW(L"Hit_Player.wav", SOUND_EFFECT, 1.f);
		CDamageText* pDamage = new CDamageText(result, m_tInfo.fX, m_tRect.top);
		pDamage->Initialize();
		GET(CObjMgr)->AddObject(OBJ_EFFECT, pDamage);
	}
	void GetDropGold(int gold);
	void SetNoPlayerRender() { m_bIsNoPlayerRender = true; }
private:
	void Key_Input();
	void Motion_Change();
	void Jump();
	void Dash();
	void Attack();
	bool ToMouse();

	// TODO : 나중에 다른곳으로 빼자
	float lerp(float x, float y, float t)
	{
		if (t < 0.f)
			t = 0.f;
		if (t > 1.f)
			t = 1.f;
		return x + t * (y - x);
	}

private:
	CItem*			m_pWeapon;
	CRunEffect*			m_pRunEffect;
	//플레이어가 장착한 무기, 플레이어의 이펙트 등을 담을 vector
	//vector<CObj*>		m_vecOwned;

private:
	STATE				m_ePreState;
	STATE				m_eCurState;

	//소지금, 포만감
	int					m_iGold;
	float				m_fMaxSatiety;
	float				m_fCurSatiety;

	// 점프
	float				m_v0;	 // 점프 초기속력
	float				m_ft;	 // 흐르는 시간
	float				m_fAcct; // 점프 누적 시간
	bool				m_bJump; // 플레이어가 의도적으로 점프키를 눌러 점프했고 점프 중인 상태인가?
	bool				m_bIsGround; //플레이어가 땅에 닿아있는가
	bool				m_IsOnLine; // 선 타일에 있는가
	bool				m_IsOnBlock; // 뚫을 수 없는 바닥에 있는가
	// 하단점프
	bool				m_bBottomJump;

	// 대시
	float				m_fDashSpeed;
	float				m_fDasht;
	float				m_fDashAcct;
	bool				m_bDash;
	Vec2				m_vDashDir;
	float				m_fDashRadian;
	int					m_iDashFXCount;

	// 공격
	bool				m_bAttack;
	float				m_fAttackAcct;
	float				m_fAttackt;



	// 애니메이션 잘라올 사이즈
	int m_iFrameWidth;
	int m_iFrameHeight;

	bool m_bIsNoPlayerRender;
	
};

