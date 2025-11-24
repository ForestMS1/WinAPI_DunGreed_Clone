#pragma once
#include "CScene.h"
#include "Define.h"
class CToolScene : public CScene
{
public:
	CToolScene();
	~CToolScene();
public:
	// CScene을(를) 통해 상속됨
	void Initialize() override;
	void Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;
};

