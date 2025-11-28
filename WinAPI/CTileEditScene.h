#pragma once
#include "CScene.h"
#include "Define.h"
#include "CUI.h"
class CTileEditScene : public CScene
{
public:
	CTileEditScene();
	~CTileEditScene();
	// CScene을(를) 통해 상속됨
	void Initialize() override;
	void Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

private:
	void Key_Input();

private:
	int m_iDrawIDX;
	int m_iDrawIDY;
	int m_iOption;

	POINT m_ptMouse;
	CUI* m_pTileSelectUI;
	CUI* m_pTileOptionSelectUI;
};

