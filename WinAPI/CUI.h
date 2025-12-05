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
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void Late_Update() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

public:
	bool IsOpen() const { return m_bIsOpen; }
	void Open() 
	{ 
		m_bIsOpen = true;
		for (auto& pChild : m_vecChildUI)
			pChild->Open();
	}
	void Close()
	{
		m_bIsOpen = false;
		for (auto& pChild : m_vecChildUI)
			pChild->Close();
	}
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
	void Move_Frame();


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

