#include "stdafx.h"
#include "..\Headers\Scene_Stage.h"
#include "KeyMgr.h"

CScene_Stage::CScene_Stage(PDIRECT3DDEVICE9 pGraphic_Device)
	: CScene(pGraphic_Device)
{

}

HRESULT CScene_Stage::Ready_Scene()
{


	
	return S_OK;
}

_int CScene_Stage::Update_Scene(_double TimeDelta)
{
	CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON, SCENE_STAGE);

	CKeyMgr::Get_Instance()->Key_Update();
	return _int();

}

HRESULT CScene_Stage::Render_Scene()
{
	return S_OK;
}

CScene_Stage * CScene_Stage::Create(PDIRECT3DDEVICE9 pGraphic_Device)
{
	CScene_Stage*	pInstance = new CScene_Stage(pGraphic_Device);

	if (FAILED(pInstance->Ready_Scene()))
	{
		MSG_BOX("Failed To Create CScene_Stage");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CScene_Stage::Free()
{


	CScene::Free();
}
