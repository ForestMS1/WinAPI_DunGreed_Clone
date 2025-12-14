#include "pch.h"
#include "CStarBullet.h"

CStarBullet::CStarBullet()
{
}

CStarBullet::~CStarBullet()
{
	Release();
}

void CStarBullet::Initialize()
{
	m_iFrameWidth = 14;
	m_iFrameHeight = 13;
	m_tInfo.fCX = m_iFrameWidth * 3;
	m_tInfo.fCY = m_iFrameHeight * 3;

	m_fSpeed = 10.f;
	m_fDamage = 15.f;


	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 3;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100.f;
	m_tFrame.dwTime = GetTickCount();

	GET(CResourceMgr)->Insert_Png(L"../Resources/Images/Item/Bullet/StarBullet.png", L"StarBullet");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Unit/Enemy/Bat/BatBulletHit.bmp", L"BatBulletHit");
	m_wsFrameKey = L"StarBullet";
	m_ePreState = IDLE;
	m_eCurState = IDLE;
}

int CStarBullet::Update()
{
	if (m_bIsDead)
	{
		m_eCurState = DEAD;
		Move_Frame_No_Loop();
		if (m_tFrame.iStart >= m_tFrame.iEnd)
			return OBJ_DEAD;
	}
	else
	{
		CBullet::Update();	
		//m_tInfo.fX += m_fSpeed * cosf(m_fAngle * PI / 180.f);
		//m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * PI / 180.f);
	

		// 매 프레임 가장 가까운 몬스터를 찾도록
		float minDist = WINCX;
		CObj* pClosestMonster = nullptr;

		for (auto& pMonster : GET(CObjMgr)->GetObjLayer(OBJ_MONSTER))
		{
			if (!pMonster->IsDead())
			{
				float x = (pMonster->Get_Info()->fX - m_tInfo.fX);
				float y = (pMonster->Get_Info()->fY - m_tInfo.fY);
				float dist = sqrtf(x * x + y * y);

				if (minDist > dist)
				{
					minDist = dist;
					pClosestMonster = pMonster;
				}
			}
		}

		if (pClosestMonster != nullptr)
		{
			float DeltaX = pClosestMonster->Get_Info()->fX - m_tInfo.fX;
			float DeltaY = pClosestMonster->Get_Info()->fY - m_tInfo.fY;

			// atan2f (Y축 반전 필요)
			// atan2(y, x)에서 게임 좌표계(Y축이 아래로 증가)를 고려하여 -DeltaY 사용
			float radianAngle = atan2f(-DeltaY, DeltaX);

			// 렌더링(RotateTransform)에 Degree가 필요하므로 라디안 -> Degree로 변환하여 m_fAngle에 저장.
			// m_fAngle = radianAngle * 180.f / PI; 
			// m_fAngle은 이미 CLala에서 Degree로 초기화되어 넘어오므로,
			// 여기서는 최종 이동에 필요한 라디안만 구하고, Degree 변환은 렌더링에 맞게 처리.

			// 이동 방향을 라디안 각도를 이용해 계산
			m_tInfo.fX += m_fSpeed * cosf(radianAngle);
			m_tInfo.fY -= m_fSpeed * sinf(radianAngle); // Y축은 화면 좌표계에 맞춰 반전

			// 렌더링에 사용할 m_fAngle을 Degree로 갱신
			m_fAngle = radianAngle * 180.f / PI;
		}
		else
		{
			m_tInfo.fX += m_fSpeed * cosf(m_fAngle * PI / 180.f);
			m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * PI / 180.f);
		}
	}
	return 0;
}

void CStarBullet::Late_Update()
{
}

void CStarBullet::Render(HDC hDC)
{
	CBullet::Render(hDC);
	if (m_eCurState == DEAD)
	{
		HDC hMemDC = GET(CResourceMgr)->Find_Bmp(L"BatBulletHit");
		int ScrollX = GET(CCamera)->Get_ScrollX();
		int ScrollY = GET(CCamera)->Get_ScrollY();
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
		return;
	}

	int ScrollX = GET(CCamera)->Get_ScrollX();
	int ScrollY = GET(CCamera)->Get_ScrollY();

	// 1. 필요한 값 및 객체 준비
	Bitmap* _bmp = (Bitmap*)GET(CResourceMgr)->Find_Png(m_wsFrameKey);
	if (!_bmp) return;

	// 프레임 정보
	int W = m_iFrameWidth;     // 현재 프레임의 너비
	int H = m_iFrameHeight;    // 현재 프레임의 높이
	int FrameX = m_tFrame.iStart; // 현재 프레임의 시작 인덱스 (X축)

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

	// --- [추가: 3-1.5. 스케일 변환 적용 (5배 확대)] ---
	const float scaleFactor = 3.0f;
	_gx.ScaleTransform(scaleFactor, scaleFactor);
	// ----------------------------------------------------

	// 3-2. 각도만큼 회전 (m_fAngle은 Degree로 가정)
	// 참고: (m_fAngle + 270) * 180.f / PI 대신 -m_fAngle을 사용해 테스트해보세요.
	// GDI+의 RotateTransform은 Degree를 사용합니다. PI 변환이 필요 없습니다.
	// 회전 방향에 따라 부호를 조정하세요.
	_gx.RotateTransform(-m_fAngle);

	// 3-3. 원본 중심점 (현재 프레임의 중심)을 원점으로 이동
	_gx.TranslateTransform(-centerX, -centerY);


	// 4. 이미지 그리기 (DrawImage 오버로드 사용)
	// 현재 프레임 영역만 잘라내서, 변환된 좌표계의 중심 (targetX, targetY)에 그려지도록 합니다.
	// DrawImage(이미지, 대상X, 대상Y, 원본X, 원본Y, 원본너비, 원본높이, 단위)
	_gx.DrawImage(
		_bmp,
		0, 0,/*(int)(-centerX), (int)(-centerY),*/ // Dest X, Y: 변환된 좌표계의 (0, 0)에 그려지도록 (중심 정렬)
		srcX, srcY,                       // Source X, Y: 이미지 시트에서 현재 프레임 시작 위치
		W, H,                             // Source W, H: 현재 프레임의 너비와 높이
		UnitPixel
	);

	// 5. Graphics 변환 상태 복원 (매우 중요!)
	_gx.SetTransform(&originalMatrix);

}

void CStarBullet::Release()
{
}

void CStarBullet::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_iFrameWidth = 16;
			m_iFrameHeight = 13;
			m_tInfo.fCX = m_iFrameWidth * 5;
			m_tInfo.fCY = m_iFrameHeight * 5;
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 3;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount();
			m_wsFrameKey = L"StarBullet";
			break;
		case DEAD:
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 6;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100.f;
			m_tFrame.dwTime = GetTickCount();
			m_iFrameWidth = 546 / 7;
			m_iFrameHeight = 78.f;
			m_tInfo.fCX = m_iFrameWidth;
			m_tInfo.fCY = m_iFrameHeight;
			m_wsFrameKey = L"BatBulletHit";
			break;
		default:
			break;
		}

		m_ePreState = m_eCurState;
	}
}