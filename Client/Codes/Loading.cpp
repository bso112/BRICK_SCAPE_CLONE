#include "stdafx.h"
#include "..\Headers\Loading.h"
#include "GameManager.h"
#include "Brick.h"
#include "MyButton.h"
#include "Field.h"
#include "BackGround.h"
#include "MyImage.h"

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
	case SCENE_STAGE2:
		hr = pLoading->Loading_ForStageTwo();
		break;
	case SCENE_STAGE3:
		hr = pLoading->Loading_ForStageTree();
		break;
	case SCENE_STAGE4:
		hr = pLoading->Loading_ForStageFour();
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
	CManagement* pEngineMgr = CManagement::Get_Instance();
	if (nullptr == pEngineMgr) return E_FAIL;

#pragma region MODULE


#pragma endregion

#pragma region GAMEOBJECT

	CMyButton::STATEDESC btnDesc;
	btnDesc.m_eSceneID = SCENE_STAGE;
	btnDesc.m_tBaseDesc = BASEDESC(_float3(g_iWinSizeX >>1 ,(g_iWinSizeY >> 1) + 100.f, 0.f), _float3(100.f, 100.f, 10.f));
	btnDesc.m_iTextureSceneID = SCENE_STATIC;
	btnDesc.m_pTextureTag = L"Component_Texture_Btn";

	if (FAILED( pEngineMgr->Add_Object_ToLayer(SCENE_STATIC, L"GameObject_MyButton", SCENE_STAGE, L"GameObject", &btnDesc)))
		return E_FAIL;

	CField::STATEDESC fieldDesc;
	fieldDesc.iBrickNumX = 6;
	fieldDesc.iBrickNumY = 6;
	fieldDesc.iBrickNumZ = 6;
	fieldDesc.eSceneID = SCENE_STAGE;
	fieldDesc.eWhereGoal = CField::WALL_FRONT;
	fieldDesc.iGoalX = 1;
	fieldDesc.iGoalY = 1;
	if (FAILED(pEngineMgr->Add_Object_ToLayer(SCENE_STATIC, L"GameObject_Field", SCENE_STAGE, L"Layer_Field", &fieldDesc)))
		return E_FAIL;

	CBackGround::STATEDESC tBackgroundDesc;
	tBackgroundDesc.eTextureSceneID = SCENE_STATIC;
	tBackgroundDesc.pTextureTag = L"Component_Texture_Background";
	tBackgroundDesc.iTextureID = 2;
	tBackgroundDesc.tBaseDesc = BASEDESC(_float3(g_iWinSizeX * 0.5f, g_iWinSizeY * 0.5f, 0.f), _float3((_float)g_iWinSizeX, (_float)g_iWinSizeY, 1.f));

	if (FAILED(pEngineMgr->Add_Object_ToLayer(SCENE_STATIC, L"GameObject_Background", SCENE_STAGE, L"Layer_Background", &tBackgroundDesc)))
		return E_FAIL;



	

#pragma endregion


	CGameManager::Get_Instance()->Set_CurrentLevel(0);

	m_isFinished = true;

	return S_OK;
}

HRESULT CLoading::Loading_ForStageTwo()
{
#pragma region GAMEOBJECT_PROTOTYPE
	CManagement* pEngineMgr = CManagement::Get_Instance();
	if (nullptr == pEngineMgr) return E_FAIL;
	CGameManager*	pGameManager = CGameManager::Get_Instance();
	if (nullptr == pGameManager) return E_FAIL;

#pragma endregion


#pragma region MODULE_PROTOTYPE

#pragma endregion

	pGameManager->Set_CurrentLevel(1);

	m_isFinished = true;

	return S_OK;
}

HRESULT CLoading::Loading_ForStageTree()
{
#pragma region GAMEOBJECT_PROTOTYPE
	CManagement* pEngineMgr = CManagement::Get_Instance();
	if (nullptr == pEngineMgr) return E_FAIL;
	CGameManager*	pGameManager = CGameManager::Get_Instance();
	if (nullptr == pGameManager) return E_FAIL;

#pragma endregion


#pragma region MODULE_PROTOTYPE

#pragma endregion

	pGameManager->Set_CurrentLevel(2);

	m_isFinished = true;

	return S_OK;
}

HRESULT CLoading::Loading_ForStageFour()
{
#pragma region GAMEOBJECT_PROTOTYPE
	CManagement* pEngineMgr = CManagement::Get_Instance();
	if (nullptr == pEngineMgr) return E_FAIL;
	CGameManager*	pGameManager = CGameManager::Get_Instance();
	if (nullptr == pGameManager) return E_FAIL;

#pragma endregion


#pragma region MODULE_PROTOTYPE

#pragma endregion

	pGameManager->Set_CurrentLevel(3);

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
