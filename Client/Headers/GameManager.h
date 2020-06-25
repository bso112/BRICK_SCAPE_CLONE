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
	void	Set_IsGoal(_bool Goal) { m_bGoal = Goal; }
	void	Set_IsGameStart(_bool IsStart) { m_bGameStart = IsStart; }
	void	Set_PickObject(_bool bPickObject) { m_bPickObject = bPickObject; }
public:
	_bool	Get_IsGoal() { return m_bGoal; }
	_bool	Get_IsGameStart() { return m_bGameStart; }
	_bool	Get_IsPickObject() { return m_bPickObject; }

	CBrick* PickBrick(POINT pt);
	HRESULT OnGameStart();
	HRESULT OnGameEnd();
private:
	CLevel*		m_pCurrentLevel = nullptr;
	_bool		m_bGameStart = false;
	_bool		m_bGoal = false;

	_bool		m_bPickObject = false;
public:
	virtual void Free() override;
};

END