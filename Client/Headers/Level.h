 #pragma once
#include "Base.h"
#include "Client_Defines.h"

BEGIN(Client)

class CBrick;
class CField;
class CLevel final : public CBase
{
private:
	explicit CLevel();
	virtual ~CLevel() = default;
	
public:
	HRESULT Ready_Level(_uint Level);
	CBrick*	PickBrick(POINT pt);

private:
	vector<CBrick*>	m_Bricks;
	CField*			m_pField = nullptr;
private:
 	HRESULT Ready_Level_One();
	HRESULT Ready_Level_Two();
	HRESULT Ready_Level_Tree();
	HRESULT Ready_Level_Four();

public:
	static CLevel* Create(_uint Level);
	virtual void Free() override;
};

END