#pragma once
#include "Define.h"
#include "CObj.h"


class CCamera
{
	SINGLE(CCamera)

private:
	Vec2		m_vLookAt; // 카메라가 보고있는 중심 좌표
	Vec2		m_vCurLookAt; // 이전위치와 현재위치 보정 위치
	Vec2		m_vPrevLookAt; // 카메라가 보는 이전프레임 위치
	CObj*		m_pTarget; // 카메라 타겟 오브젝트
	Vec2		m_vDiff; // 해상도 중심위치와, 카메라 LookAt 간의 차이값

	float		m_fTime; // 타겟을 따라가는데 걸리는 시간
	float		m_fSpeed; // 타겟을 따라가는 속도
	float		m_fAccTime; // 누적 시간


public:
	void SetLookAt(Vec2 _vLook) 
	{ 
		m_vLookAt = _vLook; 
		float fMoveDist = (m_vLookAt - m_vPrevLookAt).Length();
		m_fSpeed = fMoveDist / m_fTime;
		m_fAccTime = 0.f;
	}
	void SetTarget(CObj* _pTarget) { m_pTarget = _pTarget; }
	Vec2 GetLookAt() const { return m_vCurLookAt; }
	Vec2 GetRenderPos(Vec2 _vObjPos) { return _vObjPos - m_vDiff; }
	Vec2 GetRealPos(Vec2 _vRenderPos) { return _vRenderPos + m_vDiff; }
	RECT GetRenderRect(INFO tInfo)
	{
		Vec2 rp = GetRenderPos(Vec2(tInfo.fX, tInfo.fY));
		RECT rRect;
		rRect.left = rp.fX - tInfo.fCX / 2;
		rRect.top = rp.fY - tInfo.fCY / 2;
		rRect.right = rp.fX + tInfo.fCY / 2;
		rRect.bottom = rp.fY + tInfo.fCY / 2;
		return rRect;
	}
	float Get_ScrollX() const { return m_vDiff.fX; }
	float Get_ScrollY() const { return m_vDiff.fY; }
	void Set_ScrollX(float fX) { m_vLookAt.fX += fX; }
	void Set_ScrollY(float fY) { m_vLookAt.fY += fY; }

	Vec2 GetDiff() const { return m_vDiff; }


public:
	void Update();
	void Initialize();
private:
	void CalDiff();
};

