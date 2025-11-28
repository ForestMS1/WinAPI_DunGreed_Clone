#pragma once
#include "Define.h"
#include "CObj.h"
class CUI : public CObj
{
public:
	CUI();
	virtual ~CUI();
public:
	// CObj을(를) 통해 상속됨
	void Initialize() override;
	int Update() override;
	void Late_Update() override;
	void Render(HDC hDC) override;
	void Release() override;

public:
	bool IsOpen() const { return m_bIsOpen; }
	void Open() { m_bIsOpen = true; }
	void Close() { m_bIsOpen = false; }
	void SetParentUI(CUI* pParentUI) { m_pParentUI = pParentUI; }
	CUI* GetParentUI() const { return m_pParentUI; }
	void AddChildUI(CUI* pChildUI) 
	{
		if (pChildUI) 
		{
			m_vecChildUI.push_back(pChildUI);
			pChildUI->SetParentUI(this);
		}
	}


protected:
	// 애니메이션
	FRAME		m_tFrame;
	wstring		m_wsFrameKey;
	bool		m_bIsFlipped; // 좌 우 반전


	// UI 활성화 여부
	bool m_bIsOpen;

	// 부모, 자식 UI
	CUI*		m_pParentUI;
	vector<CUI*>	m_vecChildUI;
};

