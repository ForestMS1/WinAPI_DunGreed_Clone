#pragma once
#include "Define.h"
class CKeyMgr
{
	SINGLE(CKeyMgr)

public:

	void Update();

	bool Key_Down(int _iKey);
	bool Key_Pressing(int _iKey);
	bool Key_Up(int _iKey);
	void Release();

private:
	bool		m_bKeyState[VK_MAX];
};

