#include "pch.h"
#include "CCosSword.h"
#include "CPlayer.h"
#include "CCosSwordBullet.h"
#include "CSkilUI.h"
CCosSword::CCosSword() : m_bIsGot(false), isAttack(false)
{
	m_pSwingFX = new CCosSwingFX;
}

CCosSword::CCosSword(float fX, float fY) :m_bIsGot(false), isAttack(false)
{
	m_tInfo.fX = fX;
	m_tInfo.fY = fY;
	m_pSwingFX = new CCosSwingFX;
}

CCosSword::~CCosSword()
{
	Release();
}

void CCosSword::Initialize()
{
	__super::Initialize();
	if (m_pSwingFX == nullptr)
	{
		m_pSwingFX = new CCosSwingFX;
	}
	m_pSwingFX->Initialize();
	if (GET(CPlayerMgr)->GetPlayer() != nullptr && !m_bIsDrop)
	{
		m_fOffsetX = GET(CPlayerMgr)->GetPlayer()->Get_Info()->fCX * 0.5f;
		m_fOffsetY = GET(CPlayerMgr)->GetPlayer()->Get_Info()->fCY * 0.5f;

		m_tInfo.fX = GET(CPlayerMgr)->GetPlayer()->Get_Info()->fX + m_fOffsetX;
		m_tInfo.fY = GET(CPlayerMgr)->GetPlayer()->Get_Info()->fY - m_fOffsetY;
	}

	m_iFrameWidth = 27;
	m_iFrameHeight = 81;
	m_tInfo.fCX = m_iFrameWidth;
	m_tInfo.fCY = m_iFrameHeight;

	//플레이어 감지 범위
	m_fDetectfCX = m_tInfo.fCX * 0.5f;
	m_fDetectfCY = m_tInfo.fCY * 0.5f;

	m_tFrame.iStart = 0;
	m_tFrame.iMotion = 0;
	m_tFrame.iEnd = 11;
	m_tFrame.dwSpeed = 100;
	m_tFrame.dwTime = GetTickCount();

	__super::Update_Rect();

	GET(CResourceMgr)->Insert_Png(L"../Resources/Images/Item/Weapon/CosmosSword.png", L"CosmosSword");
	GET(CResourceMgr)->Insert_Bmp(L"../Resources/Images/Item/Weapon/CosmosSwordNoAnim.bmp", L"CosmosSwordNoAnim");

	m_fDamage = 15.f;
	m_iMaxAttackCount = 10;
	m_iCurAttackCount = 0;
	m_wsFrameKey = L"CosmosSwordNoAnim";

	m_tAttackInfo.fCX = 60.f;
	m_tAttackInfo.fCY = 90.f;

	ZeroMemory(&m_tAttackRect, sizeof(RECT));
	m_SoundIndex = SOUND_PLAYER_ATTACK1;
	m_dwSoundTick = GetTickCount();

	m_fShopPrice = 3000;
	m_wsName = L"코스모스 소드";

	m_dwShootDelay = GetTickCount();

	//GET(CUIMgr)->Insert_UI(L"CosSkillUI", new CSkilUI);
}

int CCosSword::Update()
{
	//바닥에 떨어진 거
	if (m_bIsGot)
	{
		GET(CSoundMgr)->PlaySoundW(L"Get_Item.wav", SOUND_EFFECT, 1.f);
		return OBJ_DEAD;
	}


	//템칸이나 착용 중 일때
	if (m_bIsDrop == false)
	{
		CWeapon::Update();
		if (m_pSwingFX != nullptr)
		{
			m_pSwingFX->Update();
		}

		if (GET(CKeyMgr)->Key_Down('X'))
		{
			if (m_dwShootDelay + 100 < GetTickCount())
			{
				GET(CObjMgr)->AddObject(OBJ_PLAYER_BULLET,
					CAbstractFactory<CCosSwordBullet>::CreateBullet(m_tInfo.fX, m_tInfo.fY, m_fAngle * 180 / PI));
				m_dwShootDelay = GetTickCount();
				//GET(CSoundMgr)->PlaySound(L"GatlingShot.wav", SOUND_PLAYER_ATTACK1, 0.3f);

				GET(CSoundMgr)->PlaySoundW(L"CosmicDash.wav", (CHANNELID)(m_iCurAttackCount % 6 + 3), 0.3f);
				m_dwSoundTick = GetTickCount();
			}
		}
	}
	//GET(CUIMgr)->Find_UI(L"CosSkillUI")->Open();

	//CWeapon::Update();
	CItem::Update();

	__super::Update_Rect();
	//Move_Frame();

	return 0;
}

void CCosSword::Late_Update()
{
	CWeapon::Late_Update();
	CItem::Late_Update();
	if (m_bIsInPlayer && m_bIsDrop)
	{
		CObj* pPlayer = GET(CPlayerMgr)->GetPlayer();
		if (CCollisionMgr::Check_Rect(pPlayer, this))
		{
			//dynamic_cast<CPlayer*>(pPlayer)->GetDropGold(m_iGold);
			//dynamic_cast<CPlayer*>(pPlayer)->RestoreHp(m_iReHp);
			//TODO: 플레이어 인벤토리에 복사생성
			m_bIsDrop = false;
			GET(CPlayerMgr)->AddItem(this); // 이 함수 내부에서 자체적으로 Clone생성
			m_bIsGot = true; //다음프레임에 삭제
		}
	}

	//if (m_dwShootDelay + 50 < GetTickCount() &&
	//	dynamic_cast<CPlayer*>(GET(CPlayerMgr)->GetPlayer())->Get_IsAttack() && m_iCurAttackCount < m_iMaxAttackCount)
	//{
	//	GET(CObjMgr)->AddObject(OBJ_PLAYER_BULLET,
	//		CAbstractFactory<CStarBullet>::CreateBullet(m_tInfo.fX, m_tInfo.fY, m_fAngle * 180 / PI));
	//	m_iCurAttackCount++;
	//	m_dwShootDelay = GetTickCount();
	//	//GET(CSoundMgr)->PlaySound(L"GatlingShot.wav", SOUND_PLAYER_ATTACK1, 0.3f);
	//
	//	GET(CSoundMgr)->PlaySoundW(L"MagicWandAttack.wav", (CHANNELID)(m_iCurAttackCount % 6 + 3), 1.f);
	//	m_dwSoundTick = GetTickCount();
	//}
	//else if (!dynamic_cast<CPlayer*>(GET(CPlayerMgr)->GetPlayer())->Get_IsAttack())
	//{
	//	m_iCurAttackCount = 0;
	//}
	if (dynamic_cast<CPlayer*>(GET(CPlayerMgr)->GetPlayer())->Get_IsAttack())
	{
		m_fAngle += 60;

		if (!dynamic_cast<CPlayer*>(GET(CPlayerMgr)->GetPlayer())->IsFlipped())
		{

			m_tAttackRect =
			{
				m_tRect.right,
				m_tRect.top,
				m_tRect.right + 60,
				m_tRect.bottom
			};

			//m_tAttackInfo.fX = m_tInfo.fX;
			//m_tAttackInfo.fY = m_tInfo.fY;


		}
		else
		{
			m_fAngle += 270;
			m_tAttackRect =
			{
				m_tRect.left - 60,
				m_tRect.top,
				m_tRect.left,
				m_tRect.bottom
			};
			//m_tAttackInfo.fX = m_tInfo.fX + m_tInfo.fCX * 2.f;
			//m_tAttackInfo.fY = m_tInfo.fY;
		}
		if (m_dwSoundTick + 80 < GetTickCount())
		{
			m_SoundIndex++;
			if (m_SoundIndex > SOUND_PLAYER_ATTACK6)
				m_SoundIndex = SOUND_PLAYER_ATTACK1;
			GET(CSoundMgr)->PlaySoundW(L"CosmicDash.wav", (CHANNELID)m_SoundIndex, 1.f);
			m_dwSoundTick = GetTickCount();
		}
		CCollisionMgr::Collision_Weapon(this, GET(CObjMgr)->GetObjLayer(OBJ_MONSTER));
	}
	else
	{
		m_iCurAttackCount = 0;
	}
	if (m_pSwingFX != nullptr)
	{
		m_pSwingFX->Late_Update();
	}
}

void CCosSword::Render(HDC hDC)
{
	CWeapon::Render(hDC);
	int scrollX = GET(CCamera)->Get_ScrollX();
	int scrollY = GET(CCamera)->Get_ScrollY();

	if (m_bIsDrop)//바닥에 떨어져있을 때
	{
		HDC hMemDC = GET(CResourceMgr)->Find_Bmp(L"CosmosSwordNoAnim");
		GdiTransparentBlt(
			hDC,
			m_tRect.left - scrollX,
			m_tRect.top - scrollY,
			m_tInfo.fCX,
			m_tInfo.fCY,
			hMemDC,
			0,
			0,
			m_iFrameWidth,
			m_iFrameHeight,
			RGB(255, 0, 255)
		);
	}
	else //착용했을때
	{
		// 1. 필요한 값 및 객체 준비
		Bitmap* _bmp = (Bitmap*)GET(CResourceMgr)->Find_Png(L"CosmosSword");
		if (!_bmp) return;

		// 프레임 정보
		int W = m_iFrameWidth;     // 현재 프레임의 너비
		int H = m_iFrameHeight;    // 현재 프레임의 높이
		int FrameX = m_tFrame.iStart; // 현재 프레임의 시작 인덱스 (X축)

		// 화면 DC Graphics 객체
		Graphics _gx(hDC);

		// --- [수정 1: 회전 중심을 '현재 프레임'의 중심'으로 설정] ---
		float centerX = (float)W / 2.0f; // 현재 프레임의 상대적 중심 X
		float centerY = (float)H; // 현재 프레임의 상대적 중심 Y (m_iFrameHeight / 2.0f)

		float offX = 25;
		if (GET(CPlayerMgr)->GetPlayer()->IsFlipped())
			offX = -25;
		else
			offX = 25;
		// 최종적으로 이미지가 그려질 화면상의 중심 좌표 (스크롤 및 Info 반영)
		//float targetX = GET(CPlayerMgr)->GetPlayer()->Get_Info()->fX - scrollX + offX;
		//float targetY = GET(CPlayerMgr)->GetPlayer()->Get_Info()->fY - scrollY;

		float targetX = m_tInfo.fX - scrollX;
		float targetY = m_tInfo.fY - scrollY;
		
		// 원본 이미지 시트에서 현재 프레임의 시작 위치
		int srcX = FrameX * W;
		int srcY = 0; // Y축 방향으로의 애니메이션이 없다면 0

		// 2. 현재 Graphics의 변환 상태 저장
		Matrix originalMatrix;
		_gx.GetTransform(&originalMatrix);

		// 3. 변환(Transform) 단계 적용 

		// 3-1. 최종 위치로 이동 (targetX, targetY)
		_gx.TranslateTransform(targetX, targetY);

		float offset = 0.f;
		if (dynamic_cast<CPlayer*>(GET(CPlayerMgr)->GetPlayer())->IsFlipped())
			offset = 60.f;
		else
			offset = 0.f;
		// 3-2. 각도만큼 회전 (m_fAngle은 Degree로 가정)
		// 참고: (m_fAngle + 270) * 180.f / PI 대신 -m_fAngle을 사용해 테스트해보세요.
		// GDI+의 RotateTransform은 Degree를 사용합니다. PI 변환이 필요 없습니다.
		// 회전 방향에 따라 부호를 조정하세요.
		//_gx.RotateTransform(-((m_fAngle) * 180.f / PI + 270));
		_gx.RotateTransform(-(m_fAngle + 270 + offset) * 180.f / PI);
		// 3-3. 원본 중심점 (현재 프레임의 중심)을 원점으로 이동
		_gx.TranslateTransform(-centerX, -centerY);


		// 4. 이미지 그리기 (DrawImage 오버로드 사용)
		// 현재 프레임 영역만 잘라내서, 변환된 좌표계의 중심 (targetX, targetY)에 그려지도록 합니다.
		// DrawImage(이미지, 대상X, 대상Y, 원본X, 원본Y, 원본너비, 원본높이, 단위)

		int offsetX = 15;
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
	if (m_pSwingFX != nullptr)
	{
		m_pSwingFX->Render(hDC);
	}
}

void CCosSword::Release()
{
	Safe_Delete(m_pSwingFX);
}

CItem* CCosSword::Clone()
{
	CCosSword* pCosSword = new CCosSword(*this);
	pCosSword->SetGotFree();
	pCosSword->SetDrop(false);
	pCosSword->Initialize();
	return pCosSword;
}
