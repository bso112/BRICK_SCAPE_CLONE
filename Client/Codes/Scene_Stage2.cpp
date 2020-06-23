#include "stdafx.h"
#include "..\Headers\Scene_Stage2.h"

CScene_Stage2::CScene_Stage2(PDIRECT3DDEVICE9 pGraphic_Device)
	: CScene(pGraphic_Device)
{

}

HRESULT CScene_Stage2::Ready_Scene()
{
	
	return S_OK;
}

_int CScene_Stage2::Update_Scene(_double TimeDelta)
{
	return _int();
}

HRESULT CScene_Stage2::Render_Scene()
{
	return S_OK;
}

CScene_Stage2 * CScene_Stage2::Create(PDIRECT3DDEVICE9 pGraphic_Device)
{
	CScene_Stage2*	pInstance = new CScene_Stage2(pGraphic_Device);

	if (FAILED(pInstance->Ready_Scene()))
	{
		MSG_BOX("Failed To Create CScene_Stage2");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CScene_Stage2::Free()
{


	CScene::Free();
}
