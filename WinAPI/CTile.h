#pragma once
#include "CObj.h"
class CTile : public CObj
{
public:
	CTile();
	~CTile();
	// CObj을(를) 통해 상속됨
	void Initialize()					override;
	int Update()						override;
	void Late_Update()					override;
	void Render(HDC hDC)				override;
	void Release()						override;

public:
	void Set_DrawID(int iDrawIDX, int iDrawIDY)			{ m_tTileInfo.iDrawIDX = iDrawIDX; m_tTileInfo.iDrawIDY = iDrawIDY; }
	void Set_Option(int iOptionID)						{ m_iOption = iOptionID; }
	TILEINFO Get_DrawID()	const						{ return m_tTileInfo; }
	int	Get_Option()	const							{ return m_iOption; }
private:
	//int m_iDrawIDX;
	//int m_iDrawIDY;
	TILEINFO m_tTileInfo;
	int m_iOption;
};

