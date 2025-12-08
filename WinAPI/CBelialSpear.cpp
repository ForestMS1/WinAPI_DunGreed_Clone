#include "pch.h"
#include "CBelialSpear.h"
#include "CPlayer.h"

CBelialSpear::CBelialSpear() : m_pOwner(nullptr), m_pTarget(nullptr)
, m_fAngle(0.f), isActive(false), isAttack(false)
{
}

CBelialSpear::CBelialSpear(CEnemy* pBelial) : m_pTarget(nullptr), m_fAngle(0.f)
, isActive(false), isAttack(false), onEffect(false), m_fShootAngle(0.f) , isGround(false)
, m_fDamage(0.f)
{
	m_pOwner = pBelial;
}

CBelialSpear::~CBelialSpear()
{
	Release();
}

void CBelialSpear::Initialize()
{
	m_tInfo.fCX = 62.f;
	m_tInfo.fCY = 190;
	m_fAngle = 0.f;
	m_fSpeed = 50.f;
	__super::Update_Rect();
	if (!GET(CObjMgr)->GetObjLayer(OBJ_PLAYER).empty())
		m_pTarget = GET(CObjMgr)->GetObjLayer(OBJ_PLAYER).front();

	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/Belial/SwordEffect.bmp", L"SwordEffect");
	// 소환 이펙트
	m_tFrame.iStart = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.iEnd = 2;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();
	m_iFrameWidth = 438 / 3;
	m_iFrameHeight = 200;

	m_fDamage = 10.f;
	m_iMaxAttackCount = 1;
	m_iCurAttackCount = 0;
	m_dwDelay = GetTickCount();
}

int CBelialSpear::Update()
{
	if (!isActive)
		return 0;

	if (m_pTarget != nullptr && !isGround && !isAttack)
	{
		float	fWidth(0.f), fHeight(0.f), fDiagonal(0.f);

		fWidth = m_pTarget->Get_Info()->fX - m_tInfo.fX;
		fHeight = m_pTarget->Get_Info()->fY - m_tInfo.fY;

		fDiagonal = sqrtf(fWidth * fWidth + fHeight * fHeight);

		m_fAngle = acosf(fWidth / fDiagonal);
		if (m_pTarget->Get_Info()->fY > m_tInfo.fY)
			m_fAngle = 2.f * PI - m_fAngle;
	}

	//소환(isActive = true)되고나서 3초뒤에 발사
	if (isAttack == false && m_dwDelay + 3000 < GetTickCount())
	{
		if (isAttack == false)
		{
			m_fShootAngle = m_fAngle;
			if (isGround == false)
			{
				GET(CSoundMgr)->PlaySoundW(L"Belial_sword_shoot.wav", SOUND_ENEMY_ATTACK, 1.f);
			}
		}
		isAttack = true;
	}

	for (auto& pTile : GET(CTileMgr)->GetVecTile())
	{
		POINT pt = { (int)m_tInfo.fX, (int)m_tInfo.fY };
		if (dynamic_cast<CTile*>(pTile)->Get_Option() == BLOCKED && PtInRect(pTile->Get_Rect(), pt))
		{
			isAttack = false;
			isGround = true;
			m_fAngle = m_fShootAngle;
		}
	}
	Shoot();

	__super::Update_Rect();
	return 0;
}

void CBelialSpear::Late_Update()
{
	if (onEffect)
	{
		Move_Frame_No_Loop();
	}

	RECT rt;
	if (!GET(CObjMgr)->GetObjLayer(OBJ_PLAYER).empty())
	{
		CObj* pPlayer = GET(CObjMgr)->GetObjLayer(OBJ_PLAYER).front();
		if (m_iMaxAttackCount > m_iCurAttackCount && IntersectRect(&rt, &m_tRect, GET(CObjMgr)->GetObjLayer(OBJ_PLAYER).front()->Get_Rect()))
		{
			if (isAttack && !isGround)
			{
				dynamic_cast<CPlayer*>(pPlayer)->OnDamage(m_fDamage);
				m_iCurAttackCount++;
			}
		}
	}
}

void CBelialSpear::Render(HDC hDC)
{
	if (!isActive)
		return;

	int ScrollX = GET(CCamera)->Get_ScrollX();
	int ScrollY = GET(CCamera)->Get_ScrollY();
	if (onEffect)
	{
		HDC hMemDC = GET(CResourceMgr)->Find_Bmp(L"SwordEffect");
		GdiTransparentBlt(
			hDC,
			m_tRect.left - ScrollX,
			m_tRect.top - ScrollY,
			m_iFrameWidth,
			m_iFrameHeight,
			hMemDC,
			m_iFrameWidth * m_tFrame.iStart,
			0,
			m_iFrameWidth,
			m_iFrameHeight,
			RGB(255, 0, 255)
		);
	}

	// 1. 필요한 값 및 객체 준비
	Bitmap* _bmp = (Bitmap*)GET(CResourceMgr)->Find_Png(L"SkellBossSword");
	if (!_bmp) return;

	int W = _bmp->GetWidth();
	int H = _bmp->GetHeight();

	// 화면 DC Graphics 객체
	Graphics _gx(hDC);

	// 원본 이미지 중심 좌표 (회전의 중심축)
	float centerX = (float)W / 2.0f;
	float centerY = (float)H / 2.0f;

	// 최종적으로 이미지가 그려질 화면상의 중심 좌표 (스크롤 및 Info 반영)
	float targetX = m_tInfo.fX - ScrollX;
	float targetY = m_tInfo.fY - ScrollY;

	// 2. 현재 Graphics의 변환 상태 저장
	Matrix originalMatrix;
	_gx.GetTransform(&originalMatrix); // 기존 행렬 저장 (복원용)

	// 3. 변환(Transform) 단계 적용

	// 3-1. 최종 위치로 이동 (targetX, targetY)
	_gx.TranslateTransform(targetX, targetY);

	// 3-2. 각도만큼 회전 (m_fAngle은 Degree라고 가정)
	_gx.RotateTransform(-(m_fAngle + 90) * 180.f / PI);

	// 3-3. 원본 중심점을 원점으로 이동 (-centerX, -centerY)
	// 이 과정을 거쳐야 DrawImage(0, 0) 호출 시 원본 이미지의 중심이 
	// RotateTransform과 TranslateTransform의 최종 원점(targetX, targetY)에 위치하게 됩니다.
	_gx.TranslateTransform(-centerX, -centerY);


	// 4. 이미지 그리기
	// 변환된 좌표계의 (0, 0) 위치에 원본 이미지를 그립니다.
	_gx.DrawImage(_bmp, 0, 0);


	// 5. Graphics 변환 상태 복원 (매우 중요!)
	_gx.SetTransform(&originalMatrix);
}

void CBelialSpear::Release()
{
}

void CBelialSpear::Motion_Change()
{
}

void CBelialSpear::Shoot()
{
	if (isAttack)
	{
		m_tInfo.fX += m_fSpeed * cosf(-m_fShootAngle);
		m_tInfo.fY += m_fSpeed * sinf(-m_fShootAngle);
	}
}
