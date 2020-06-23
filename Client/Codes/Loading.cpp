#include "stdafx.h"
#include "..\Headers\Loading.h"
#include "GameManager.h"

USING(Client)

CLoading::CLoading(PDIRECT3DDEVICE9 pGraphic_Device)
	: m_pGraphic_Device(pGraphic_Device)
{
	Safe_AddRef(m_pGraphic_Device);
}

_uint APIENTRY Thread_Main(void* pArg)
{
	CLoading*		pLoading = (CLoading*)pArg;

	HRESULT	hr = 0;

	EnterCriticalSection(pLoading->Get_CriticalSection());

	switch (pLoading->Get_SceneID())
	{
	case SCENE_STAGE:
		hr = pLoading->Loading_ForStageOne();
		break;

	/*case SCENE_STAGE2:
		break;*/
	}

	LeaveCriticalSection(pLoading->Get_CriticalSection());

	if (FAILED(hr))
		return -1;

	return 0;
}

HRESULT CLoading::Ready_Loading(SCENEID eSceneID)
{
	m_eSceneID = eSceneID;

	InitializeCriticalSection(&m_CriticalSection);

	m_hThread = (HANDLE)_beginthreadex(nullptr, 0, Thread_Main, this, 0, nullptr);
	if (0 == m_hThread)
		return E_FAIL;

	return S_OK;
}

HRESULT CLoading::Loading_ForStageOne()
{
#pragma region GAMEOBJECT_PROTOTYPE

#pragma endregion


#pragma region MODULE_PROTOTYPE

#pragma endregion

	CGameManager::Get_Instance()->Set_CurrentLevel(0);

	m_isFinished = true;

	return S_OK;
}

CLoading * CLoading::Create(PDIRECT3DDEVICE9 pGraphic_Device, SCENEID eSceneID)
{
	CLoading*	pInstance = new CLoading(pGraphic_Device);

	if (FAILED(pInstance->Ready_Loading(eSceneID)))
	{
		MSG_BOX("Failed To Creating CLoading");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CLoading::Free()
{
	WaitForSingleObject(m_hThread, INFINITE);

	DeleteCriticalSection(&m_CriticalSection);

	CloseHandle(m_hThread);

	Safe_Release(m_pGraphic_Device);
}
