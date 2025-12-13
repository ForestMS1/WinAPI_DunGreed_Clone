#include "pch.h"
#include "CSkelArrow.h"

CSkelArrow::CSkelArrow() :m_ePreState(END), m_eCurState(IDLE), m_bNoMove(false)
{
}

CSkelArrow::~CSkelArrow()
{
	Release();
}

void CSkelArrow::Initialize()
{
	m_fSpeed = 15.f;
	m_fDamage = 3.f;

	m_iFrameWidth = 39;
	m_iFrameHeight = 15;
	m_tInfo.fCX = m_iFrameWidth;
	m_tInfo.fCY = m_iFrameHeight;
	m_tFrame.iStart = 0;
	m_tFrame.iEnd = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.dwSpeed = 100.f;
	m_wsFrameKey = L"SkelArrow";
	m_tFrame.dwTime = GetTickCount();

	GET(CResourceMgr)->Insert_Png(L"../Resources/Images/Unit/Enemy/Skel/SkelArrow.bmp", L"SkelArrow");
	m_eCurState = IDLE;
}

int CSkelArrow::Update()
{
	if (m_bIsDead)
	{
		Move_Frame_No_Loop();
		m_eCurState = DEAD;
		if (m_tFrame.iStart >= m_tFrame.iEnd)
			return OBJ_DEAD;
	}
	else
	{
		CBullet::Update();
		if (m_bNoMove)
			return 0;
		m_tInfo.fX += m_fSpeed * cosf(m_fAngle * PI / 180.f);
		m_tInfo.fY -= m_fSpeed * sinf(m_fAngle * PI / 180.f);
	}
	return 0;
}

void CSkelArrow::Late_Update()
{
	Motion_Change();
}

void CSkelArrow::Render(HDC hDC)
{
	CBullet::Render(hDC);
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

void CSkelArrow::Release()
{
}

void CSkelArrow::Motion_Change()
{
	if (m_ePreState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_iFrameWidth = 39;
			m_iFrameHeight = 15;
			m_tInfo.fCX = m_iFrameWidth;
			m_tInfo.fCY = m_iFrameHeight;
			m_tFrame.iStart = 0;
			m_tFrame.iEnd = 0;
			m_tFrame.iMotion = 0;
			m_tFrame.dwSpeed = 100.f;
			m_wsFrameKey = L"SkelArrow";
			m_tFrame.dwTime = GetTickCount();
			break;
		case DEAD:
			break;
		default:
			break;
		}

		m_ePreState = m_eCurState;
	}
}
