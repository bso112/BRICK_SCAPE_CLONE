#pragma once
#include "Base.h"
#include "Client_Defines.h"

BEGIN(Client)

class CLevel;
class CBrick;
class CGameManager final : public CBase
{
	DECLARE_SINGLETON(CGameManager)
private:
	explicit CGameManager();
	virtual ~CGameManager() = default;
public:
	HRESULT Set_CurrentLevel(_uint _iLevel);

	CBrick* PickBrick(POINT pt);
	HRESULT OnGameStart();
	HRESULT OnGameEnd();
private:
	CLevel*		m_pCurrentLevel = nullptr;
	_bool		m_bGameStart = false;
public:
	virtual void Free() override;
};

END