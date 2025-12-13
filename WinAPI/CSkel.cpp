#include "pch.h"
#include "CSkel.h"
#include "CPlayer.h"
#include "CSkelArrow.h"
CSkel::CSkel() : m_iAttack(5), playArrowLoad(false), playArrowShoot(false), inCheck(false)
{
}

CSkel::~CSkel()
{
	Release();
}

void CSkel::Initialize()
{
	CEnemy::Initialize();

	m_fMaxHp = 100.f;
	m_fCurHp = m_fMaxHp;

	m_fSpeed = 4.f;

	//플레이어 감지 범위
	m_fDetectfCX = 800;
	m_fDetectfCY = 900;

	m_tFrame.iStart = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.iEnd = 14;
	m_tFrame.dwSpeed = 100.f;
	m_iFrameWidth = 124;
	m_iFrameHeight = 124;
	m_tInfo.fCX = m_iFrameWidth;
	m_tInfo.fCY = m_iFrameHeight;
	//m_fDetectfCX = m_tInfo.fCX;
	//m_fDetectfCY = m_tInfo.fCY;
	m_wsFrameKey = L"EnemySpawn";
	m_tFrame.dwTime = GetTickCount();

	__super::Update_Rect();

	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/Skel/SkelIdle.bmp", L"SkelIdle");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/Skel/SkelWalk.bmp", L"SkelWalk");
	//GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/Skel/SkelBow.bmp", L"SkelBow");
	GET(CResourceMgr)->Insert_Png(L"../Resources/Images/Unit/Enemy/Skel/SkelBow.png", L"SkelBow");
	GET(CResourceMgr)->Insert_Png(L"../Resources/Images/Unit/Enemy/Skel/SkelArrow.png", L"SkelArrow");


	m_dwAttackDelay = GetTickCount();

	m_eCurState = SPAWN;
	m_wsFrameKey = L"EnemySpawn";
	srand(time(0));
	m_iDropGold = 50 + (rand() % 10);
}

int CSkel::Update()
{
	CEnemy::Update();


	m_tInfo.fY += GRAVITY;

	__super::Update_Rect();
	Update_DetectRect();

	if (m_eCurState == SPAWN)
	{
		SpawnEffect();
		return 0;
	}

	if (m_fCurHp <= 0.f)
	{
		m_bIsDead = true;
		m_eCurState = DEAD;
		DeadEffect();
		if (m_tFrame.iStart >= m_tFrame.iEnd)
			return OBJ_DEAD;
		else
			return 0;
	}

	if (m_bIsInPlayer && m_eCurState != ATTACK)
	{
		CEnemy::ToPlayerAngle();
		m_eCurState = IDLE;
		//if (fabsf(GET(CPlayerMgr)->GetPlayer()->Get_Pos().fX - m_tInfo.fX) > 50)
			//m_tInfo.fX += m_fSpeed * cosf(m_fAngle); //* 180.f / PI);
		//m_tInfo.fY -= m_fSpeed * sinf(m_fAngle); //* 180.f / PI);
	}

	Attack_CircleBullet();

	if (GET(CPlayerMgr)->GetPlayer()->Get_Info()->fX < m_tInfo.fX)
		m_tFrame.iMotion = 1;
	else
		m_tFrame.iMotion = 0;


	Move_Frame();

	if (m_bIsHit && m_dwLastHitTime + 10 < GetTickCount())
	{
		m_bIsHit = false;
	}

	return OBJ_NOEVENT;
}

void CSkel::Late_Update()
{
	CEnemy::Late_Update();

	Motion_Change();
	CCollisionMgr::Collision_RectTile(this, GET(CTileMgr)->GetVecTile());
	float py(0.f);
	GET(CLineMgr)->Collision_Line(this, &py);
}

void CSkel::Render(HDC hDC)
{
	CEnemy::Render(hDC);

	if (!m_bIsHit)
	{
		int ScrollX = (int)GET(CCamera)->Get_ScrollX();
		int ScrollY = (int)GET(CCamera)->Get_ScrollY();
		if (g_bDebugMod)
		{
			Rectangle(hDC, m_tRect.left - ScrollX, m_tRect.top - ScrollY, m_tRect.right - ScrollX, m_tRect.bottom - ScrollY);

			HPEN hPen = CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
			hPen = (HPEN)SelectObject(hDC, hPen);
			MoveToEx(hDC, m_tDetectRect.left - ScrollX, m_tDetectRect.top - ScrollY, nullptr);
			LineTo(hDC, m_tDetectRect.right - ScrollX, m_tDetectRect.top - ScrollY);
			LineTo(hDC, m_tDetectRect.right - ScrollX, m_tDetectRect.bottom - ScrollY);
			LineTo(hDC, m_tDetectRect.left - ScrollX, m_tDetectRect.bottom - ScrollY);
			LineTo(hDC, m_tDetectRect.left - ScrollX, m_tDetectRect.top - ScrollY);
			hPen = (HPEN)SelectObject(hDC, hPen);
			DeleteObject(hPen);
		}

		HDC hMemDC = GET(CResourceMgr)->Find_Bmp(m_wsFrameKey);

		GdiTransparentBlt(
			hDC,
			m_tRect.left - ScrollX,
			m_tRect.top - ScrollY,
			m_tInfo.fCX,
			m_tInfo.fCY,
			hMemDC,
			m_iFrameWidth * m_tFrame.iStart,
			m_iFrameHeight * m_tFrame.iMotion,
			m_iFrameWidth,
			m_iFrameHeight,
			RGB(255, 0, 255)
		);

		//HDC hBowDC = GET(CResourceMgr)->Find_Bmp(L"SkelBow");


		// 1. 필요한 값 및 객체 준비
		Bitmap* _bmp = (Bitmap*)GET(CResourceMgr)->Find_Png(L"SkelBow");
		if (!_bmp) return;

		// 프레임 정보
		int W = 51;     // 현재 프레임의 너비
		int H = 45;    // 현재 프레임의 높이
		int FrameX = 1; //m_tFrame.iStart; // 현재 프레임의 시작 인덱스 (X축)

		// 화면 DC Graphics 객체
		Graphics _gx(hDC);

		// --- [수정 1: 회전 중심을 '현재 프레임'의 중심'으로 설정] ---
		float centerX = (float)W / 2.0f; // 현재 프레임의 상대적 중심 X
		float centerY = (float)H / 2.0f; // 현재 프레임의 상대적 중심 Y (m_iFrameHeight / 2.0f)

		// 최종적으로 이미지가 그려질 화면상의 중심 좌표 (스크롤 및 Info 반영)
		float targetX = m_tInfo.fX - ScrollX;
		float targetY = m_tInfo.fY - ScrollY;

		// 원본 이미지 시트에서 현재 프레임의 시작 위치
		int srcX = FrameX * W;
		int srcY = 0; // Y축 방향으로의 애니메이션이 없다면 0

		// 2. 현재 Graphics의 변환 상태 저장
		Matrix originalMatrix;
		_gx.GetTransform(&originalMatrix);

		// 3. 변환(Transform) 단계 적용 

		// 3-1. 최종 위치로 이동 (targetX, targetY)
		_gx.TranslateTransform(targetX, targetY);

		// 3-2. 각도만큼 회전 (m_fAngle은 Degree로 가정)
		// 참고: (m_fAngle + 270) * 180.f / PI 대신 -m_fAngle을 사용해 테스트해보세요.
		// GDI+의 RotateTransform은 Degree를 사용합니다. PI 변환이 필요 없습니다.
		// 회전 방향에 따라 부호를 조정하세요.
		_gx.RotateTransform(-(m_fAngle) * 180.f / PI);

		// 3-3. 원본 중심점 (현재 프레임의 중심)을 원점으로 이동
		_gx.TranslateTransform(-centerX, -centerY);


		// 4. 이미지 그리기 (DrawImage 오버로드 사용)
		// 현재 프레임 영역만 잘라내서, 변환된 좌표계의 중심 (targetX, targetY)에 그려지도록 합니다.
		// DrawImage(이미지, 대상X, 대상Y, 원본X, 원본Y, 원본너비, 원본높이, 단위)

		int offsetX = 40;

		_gx.DrawImage(
			_bmp,
			0 + offsetX, 0,/*(int)(-centerX), (int)(-centerY),*/ // Dest X, Y: 변환된 좌표계의 (0, 0)에 그려지도록 (중심 정렬)
			srcX, srcY,                       // Source X, Y: 이미지 시트에서 현재 프레임 시작 위치
			W, H,                             // Source W, H: 현재 프레임의 너비와 높이
			UnitPixel
		);

		// 5. Graphics 변환 상태 복원 (매우 중요!)
		_gx.SetTransform(&originalMatrix);

	}
}

void CSkel::Release()
{

}

void CSkel::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case SPAWN:
			m_tFrame.iStart = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.iEnd = 14;
			m_tFrame.dwSpeed = 1000.f;
			m_iFrameWidth = 124;
			m_iFrameHeight = 124;
			m_tInfo.fCX = m_iFrameWidth * 0.5;
			m_tInfo.fCY = m_iFrameHeight * 0.5;
			m_wsFrameKey = L"EnemySpawn";
			m_tFrame.dwTime = GetTickCount();
			break;
		case IDLE:
			m_tFrame.iStart = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.iEnd = 0;
			m_tFrame.dwSpeed = 100.f;
			m_iFrameWidth = 42;
			m_iFrameHeight = 57;
			m_tInfo.fCX = m_iFrameWidth;
			m_tInfo.fCY = m_iFrameHeight;
			m_wsFrameKey = L"SkelIdle";
			m_tFrame.dwTime = GetTickCount();
			break;
		case MOVE:
			m_tFrame.iStart = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.iEnd = 5;
			m_tFrame.dwSpeed = 100.f;
			m_iFrameWidth = 42;
			m_iFrameHeight = 57;
			m_tInfo.fCX = m_iFrameWidth;
			m_tInfo.fCY = m_iFrameHeight;
			m_wsFrameKey = L"SkelWalk";
			m_tFrame.dwTime = GetTickCount();
			break;
		case DEAD:
			m_tFrame.iStart = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.iEnd = 10;
			m_tFrame.dwSpeed = 100.f;
			m_iFrameWidth = 128;
			m_iFrameHeight = 128;
			m_tInfo.fCX = m_iFrameWidth;
			m_tInfo.fCY = m_iFrameHeight;
			m_wsFrameKey = L"EnemyDie_small";
			m_tFrame.dwTime = GetTickCount();
			break;
		default:
			break;
		}
		m_ePreState = m_eCurState;
	}

}

void CSkel::Attack_CircleBullet()
{
	if (m_bIsInPlayer)
	{
		if (!inCheck)
		{
			m_dwInDelay = GetTickCount();
			inCheck = true;
		}

		CEnemy::ToPlayerAngle();
		if (!playArrowLoad)
		{
			GET(CSoundMgr)->PlaySoundW(L"arrow_load.wav", SOUND_EFFECT, 1.f);
			playArrowLoad = true;
		}


		//TODO : 2초에 한번씩 플레이어에게 화살 발사
		if (m_dwInDelay + 1000 < GetTickCount() && m_dwAttackDelay + 2000 < GetTickCount())
		{
			GET(CObjMgr)->AddObject(OBJ_ENEMY_BULLET,
				CAbstractFactory<CSkelArrow>::CreateBullet(m_tInfo.fX, m_tInfo.fY, m_fAngle * 180.f / PI));
			playArrowLoad = false;
			GET(CSoundMgr)->PlaySoundW(L"arrow_shoot.wav", SOUND_ENEMY_ATTACK, 1.f);
			m_dwAttackDelay = GetTickCount();
			inCheck = false;
		}
	}
	else
	{
		inCheck = false;
	}
}