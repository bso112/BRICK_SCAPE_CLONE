#include "stdafx.h"
#include "..\Headers\Level.h"

#include "Management.h"
#include "Brick.h"

CLevel::CLevel()
{
}

HRESULT CLevel::Ready_Level(_uint Level)
{
	switch (Level)
	{
	case 0:
		return Ready_Level_One();
	case 1:
		return Ready_Level_Two();
	case 2:
		return Ready_Level_Tree();
	case 3:
		return Ready_Level_Four();
	}

	return S_OK;
}

CBrick * CLevel::PickBrick(POINT pt)
{
	return nullptr;
}

HRESULT CLevel::Ready_Level_One()
{
	CManagement* pEngineMgr = CManagement::Get_Instance();
	if (nullptr == pEngineMgr) return E_FAIL;

	CBrick::STATEDESC brickDesc;
	brickDesc.tBaseDesc.vPos = _float3(0.f, 0.f, 0.f);
	brickDesc.tBaseDesc.vSize = _float3(1.f, 3.f, 1.f);
	if (FAILED(pEngineMgr->Add_Object_ToLayer(SCENE_STATIC, L"GameObject_Brick", SCENE_STAGE, L"GameObject", &brickDesc)))
		return E_FAIL;

	brickDesc.tBaseDesc.vPos = _float3(1.f, 0.f, 0.f);
	brickDesc.tBaseDesc.vSize = _float3(1.f, 1.f, 3.f);
	if (FAILED(pEngineMgr->Add_Object_ToLayer(SCENE_STATIC, L"GameObject_Brick", SCENE_STAGE, L"GameObject", &brickDesc)))
		return E_FAIL;


	return S_OK;
}

HRESULT CLevel::Ready_Level_Two()
{
	return S_OK;
}

HRESULT CLevel::Ready_Level_Tree()
{
	return S_OK;
}

HRESULT CLevel::Ready_Level_Four()
{
	return S_OK;
}

CLevel * CLevel::Create(_uint Level)
{
	CLevel* pInstance = new CLevel;
	if (FAILED(pInstance->Ready_Level(Level)))
	{
		MSG_BOX("Failed To Create Level");
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CLevel::Free()
{
}
