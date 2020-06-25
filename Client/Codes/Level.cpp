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


	brickDesc.tBaseDesc.vPos = _float3(0.f, 1.f, 0.f);
	brickDesc.tBaseDesc.vSize = _float3(1.f, 1.f, 2.f);
	brickDesc.m_dStartFall = 0.5;
	brickDesc.eSceneID = SCENE_STAGE;
	brickDesc.eTextureSceneID = SCENE_STATIC;
	brickDesc.iTextureID = 3;
	brickDesc.pTextureTag = L"Component_Texture_Brick";
	brickDesc.m_vAxis = _float3(0.f, 0.f, 1.f);
	brickDesc.bPlayer = true;
	m_Bricks.emplace_back((CBrick*)pEngineMgr->Add_Object_ToLayer(SCENE_STATIC, L"GameObject_Brick", SCENE_STAGE, L"GameObject", &brickDesc));
	Safe_AddRef(m_Bricks.back());

	brickDesc.tBaseDesc.vPos = _float3(0.f, 1.f, -1.5f);
	brickDesc.tBaseDesc.vSize = _float3(1.f, 2.f, 1.f);
	brickDesc.m_dStartFall = 0.2;
	brickDesc.eSceneID = SCENE_STAGE;
	brickDesc.eTextureSceneID = SCENE_STATIC;
	brickDesc.iTextureID = 0;
	brickDesc.pTextureTag = L"Component_Texture_Brick";
	brickDesc.m_vAxis = _float3(0.f, 1.f, 0.f);
	m_Bricks.emplace_back((CBrick*)pEngineMgr->Add_Object_ToLayer(SCENE_STATIC, L"GameObject_Brick", SCENE_STAGE, L"GameObject", &brickDesc));
	Safe_AddRef(m_Bricks.back());

	brickDesc.tBaseDesc.vPos = _float3(-1.f, -1.f, 0.f);
	brickDesc.tBaseDesc.vSize = _float3(1.f, 1.f, 2.f);
	brickDesc.m_dStartFall = 0.4;
	brickDesc.eSceneID = SCENE_STAGE;
	brickDesc.eTextureSceneID = SCENE_STATIC;
	brickDesc.iTextureID = 0;
	brickDesc.pTextureTag = L"Component_Texture_Brick";
	brickDesc.m_vAxis = _float3(0.f, 0.f, 1.f);
	m_Bricks.emplace_back((CBrick*)pEngineMgr->Add_Object_ToLayer(SCENE_STATIC, L"GameObject_Brick", SCENE_STAGE, L"GameObject", &brickDesc));
	Safe_AddRef(m_Bricks.back());

	brickDesc.tBaseDesc.vPos = _float3(1.f, -1.f, 1.f);
	brickDesc.tBaseDesc.vSize = _float3(1.f, 1.f, 2.f);
	brickDesc.m_dStartFall = 0.5;
	brickDesc.eSceneID = SCENE_STAGE;
	brickDesc.eTextureSceneID = SCENE_STATIC;
	brickDesc.iTextureID = 0;
	brickDesc.pTextureTag = L"Component_Texture_Brick";
	brickDesc.m_vAxis = _float3(0.f, 0.f, 1.f);
	m_Bricks.emplace_back((CBrick*)pEngineMgr->Add_Object_ToLayer(SCENE_STATIC, L"GameObject_Brick", SCENE_STAGE, L"GameObject", &brickDesc));
	Safe_AddRef(m_Bricks.back());

	return S_OK;
}

HRESULT CLevel::Ready_Level_Two()
{
	CManagement* pEngineMgr = CManagement::Get_Instance();
	if (nullptr == pEngineMgr) return E_FAIL;

	CBrick::STATEDESC brickDesc;
	brickDesc.tBaseDesc.vPos = _float3(1.f, 1.f, 1.f);
	brickDesc.tBaseDesc.vSize = _float3(1.f, 1.f, 2.f);
	brickDesc.m_dStartFall = 0.5;
	brickDesc.eSceneID = SCENE_STAGE2;
	brickDesc.eTextureSceneID = SCENE_STATIC;
	brickDesc.iTextureID = 3;
	brickDesc.pTextureTag = L"Component_Texture_Brick";
	brickDesc.m_vAxis = _float3(0.f, 0.f, 1.f);
	brickDesc.bPlayer = true;
	m_Bricks.emplace_back((CBrick*)pEngineMgr->Add_Object_ToLayer(SCENE_STATIC, L"GameObject_Brick", SCENE_STAGE2, L"GameObject", &brickDesc));
	Safe_AddRef(m_Bricks.back());


	brickDesc.tBaseDesc.vPos = _float3(1.f, 1.f, -0.55f);
	brickDesc.tBaseDesc.vSize = _float3(1.f, 2.f, 1.f);
	brickDesc.m_dStartFall = 0.2;
	brickDesc.eSceneID = SCENE_STAGE2;
	brickDesc.eTextureSceneID = SCENE_STATIC;
	brickDesc.iTextureID = 0;
	brickDesc.pTextureTag = L"Component_Texture_Brick";
	brickDesc.m_vAxis = _float3(0.f, 1.f, 0.f);
	brickDesc.bPlayer = false;
	m_Bricks.emplace_back((CBrick*)pEngineMgr->Add_Object_ToLayer(SCENE_STATIC, L"GameObject_Brick", SCENE_STAGE2, L"GameObject", &brickDesc));
	Safe_AddRef(m_Bricks.back());



	brickDesc.tBaseDesc.vPos = _float3(1.f, 1.f, -1.6f);
	brickDesc.tBaseDesc.vSize = _float3(2.f, 1.f, 1.f);
	brickDesc.m_dStartFall = 0.6;
	brickDesc.eSceneID = SCENE_STAGE2;
	brickDesc.eTextureSceneID = SCENE_STATIC;
	brickDesc.iTextureID = 0;
	brickDesc.pTextureTag = L"Component_Texture_Brick";
	brickDesc.m_vAxis = _float3(1.f, 0.f, 0.f);
	brickDesc.bPlayer = false;
	m_Bricks.emplace_back((CBrick*)pEngineMgr->Add_Object_ToLayer(SCENE_STATIC, L"GameObject_Brick", SCENE_STAGE2, L"GameObject", &brickDesc));
	Safe_AddRef(m_Bricks.back());


	brickDesc.tBaseDesc.vPos = _float3(1.f, 1.f, -2.65f);
	brickDesc.tBaseDesc.vSize = _float3(1.f, 2.f, 1.f);
	brickDesc.m_dStartFall = 0.4;
	brickDesc.eSceneID = SCENE_STAGE2;
	brickDesc.eTextureSceneID = SCENE_STATIC;
	brickDesc.iTextureID = 0;
	brickDesc.pTextureTag = L"Component_Texture_Brick";
	brickDesc.m_vAxis = _float3(0.f, 1.f, 0.f);
	brickDesc.bPlayer = false;
	m_Bricks.emplace_back((CBrick*)pEngineMgr->Add_Object_ToLayer(SCENE_STATIC, L"GameObject_Brick", SCENE_STAGE2, L"GameObject", &brickDesc));
	Safe_AddRef(m_Bricks.back());



	brickDesc.tBaseDesc.vPos = _float3(1.f, -0.55f, -2.65f);
	brickDesc.tBaseDesc.vSize = _float3(2.f, 1.f, 1.f);
	brickDesc.m_dStartFall = 0.2;
	brickDesc.eSceneID = SCENE_STAGE2;
	brickDesc.eTextureSceneID = SCENE_STATIC;
	brickDesc.iTextureID = 0;
	brickDesc.pTextureTag = L"Component_Texture_Brick";
	brickDesc.m_vAxis = _float3(1.f, 0.f, 0.f);
	brickDesc.bPlayer = false;
	m_Bricks.emplace_back((CBrick*)pEngineMgr->Add_Object_ToLayer(SCENE_STATIC, L"GameObject_Brick", SCENE_STAGE2, L"GameObject", &brickDesc));
	Safe_AddRef(m_Bricks.back());



	brickDesc.tBaseDesc.vPos = _float3(-1.f, -2.f, 1.f);
	brickDesc.tBaseDesc.vSize = _float3(3.f, 1.f, 1.f);
	brickDesc.m_dStartFall = 0.3;
	brickDesc.eSceneID = SCENE_STAGE2;
	brickDesc.eTextureSceneID = SCENE_STATIC;
	brickDesc.iTextureID = 0;
	brickDesc.pTextureTag = L"Component_Texture_Brick";
	brickDesc.m_vAxis = _float3(1.f, 0.f, 0.f);
	brickDesc.bPlayer = false;
	m_Bricks.emplace_back((CBrick*)pEngineMgr->Add_Object_ToLayer(SCENE_STATIC, L"GameObject_Brick", SCENE_STAGE2, L"GameObject", &brickDesc));
	Safe_AddRef(m_Bricks.back());

	return S_OK;
}

HRESULT CLevel::Ready_Level_Tree()
{
	CManagement* pEngineMgr = CManagement::Get_Instance();
	if (nullptr == pEngineMgr) return E_FAIL;

	CBrick::STATEDESC brickDesc;
	brickDesc.tBaseDesc.vPos = _float3(0.f, 0.f, -2.5f);
	brickDesc.tBaseDesc.vSize = _float3(1.f, 6.f, 1.f);
	brickDesc.m_dStartFall = 0.2;
	brickDesc.eSceneID = SCENE_STAGE3;
	brickDesc.eTextureSceneID = SCENE_STATIC;
	brickDesc.iTextureID = 0;
	brickDesc.pTextureTag = L"Component_Texture_Brick";
	brickDesc.m_vAxis = _float3(0.f, 1.f, 0.f);
	m_Bricks.emplace_back((CBrick*)pEngineMgr->Add_Object_ToLayer(SCENE_STATIC, L"GameObject_Brick", SCENE_STAGE3, L"GameObject", &brickDesc));
	Safe_AddRef(m_Bricks.back());

	brickDesc.tBaseDesc.vPos = _float3(1.f, 1.f, 0.f);
	brickDesc.tBaseDesc.vSize = _float3(1.f, 1.f, 2.f);
	brickDesc.m_dStartFall = 0.5;
	brickDesc.eSceneID = SCENE_STAGE3;
	brickDesc.eTextureSceneID = SCENE_STATIC;
	brickDesc.iTextureID = 3;
	brickDesc.pTextureTag = L"Component_Texture_Brick";
	brickDesc.m_vAxis = _float3(0.f, 0.f, 1.f);
	brickDesc.bPlayer = true;
	m_Bricks.emplace_back((CBrick*)pEngineMgr->Add_Object_ToLayer(SCENE_STATIC, L"GameObject_Brick", SCENE_STAGE3, L"GameObject", &brickDesc));
	Safe_AddRef(m_Bricks.back());

	return S_OK;
}

HRESULT CLevel::Ready_Level_Four()
{
	CManagement* pEngineMgr = CManagement::Get_Instance();
	if (nullptr == pEngineMgr) return E_FAIL;

	CBrick::STATEDESC brickDesc;
	brickDesc.tBaseDesc.vPos = _float3(0.f, 0.f, -2.5f);
	brickDesc.tBaseDesc.vSize = _float3(1.f, 6.f, 1.f);
	brickDesc.m_dStartFall = 0.2;
	brickDesc.eSceneID = SCENE_STAGE4;
	brickDesc.eTextureSceneID = SCENE_STATIC;
	brickDesc.iTextureID = 0;
	brickDesc.pTextureTag = L"Component_Texture_Brick";
	brickDesc.m_vAxis = _float3(0.f, 1.f, 0.f);
	m_Bricks.emplace_back((CBrick*)pEngineMgr->Add_Object_ToLayer(SCENE_STATIC, L"GameObject_Brick", SCENE_STAGE4, L"GameObject", &brickDesc));
	Safe_AddRef(m_Bricks.back());

	brickDesc.tBaseDesc.vPos = _float3(1.f, 1.f, 0.f);
	brickDesc.tBaseDesc.vSize = _float3(1.f, 1.f, 2.f);
	brickDesc.m_dStartFall = 0.5;
	brickDesc.eSceneID = SCENE_STAGE4;
	brickDesc.eTextureSceneID = SCENE_STATIC;
	brickDesc.iTextureID = 3;
	brickDesc.pTextureTag = L"Component_Texture_Brick";
	brickDesc.m_vAxis = _float3(0.f, 0.f, 1.f);
	brickDesc.bPlayer = true;
	m_Bricks.emplace_back((CBrick*)pEngineMgr->Add_Object_ToLayer(SCENE_STATIC, L"GameObject_Brick", SCENE_STAGE4, L"GameObject", &brickDesc));
	Safe_AddRef(m_Bricks.back());
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
	for (auto& Brick : m_Bricks)
		Safe_Release(Brick);

	m_Bricks.clear();
}
