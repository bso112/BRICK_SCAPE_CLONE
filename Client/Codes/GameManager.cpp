#include "stdafx.h"
#include "..\Headers\GameManager.h"
#include "Level.h"

USING(Client)

IMPLEMENT_SINGLETON(CGameManager)

CGameManager::CGameManager()
{
}

HRESULT CGameManager::Set_CurrentLevel(_uint _iLevel)
{
	// ¾À·Îµù¿¡¼­ ºÒ·¯µµ ±¦ÂúÀ»Áöµµ?
	Safe_Release(m_pCurrentLevel);

	m_pCurrentLevel = CLevel::Create(_iLevel);

	return S_OK;
}

CBrick * CGameManager::PickBrick(POINT pt)
{
	return m_pCurrentLevel->PickBrick(pt);
}

HRESULT CGameManager::OnGameStart()
{

	return S_OK;
}

HRESULT CGameManager::OnGameEnd()
{
	return S_OK;
}

void CGameManager::Free()
{
	Safe_Release(m_pCurrentLevel);

}