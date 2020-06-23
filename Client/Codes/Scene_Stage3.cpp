#include "stdafx.h"
#include "..\Headers\Scene_Stage3.h"

CScene_Stage3::CScene_Stage3(PDIRECT3DDEVICE9 pGraphic_Device)
	: CScene(pGraphic_Device)
{

}

HRESULT CScene_Stage3::Ready_Scene()
{
	
	return S_OK;
}

_int CScene_Stage3::Update_Scene(_double TimeDelta)
{
	return _int();
}

HRESULT CScene_Stage3::Render_Scene()
{
	return S_OK;
}

CScene_Stage3 * CScene_Stage3::Create(PDIRECT3DDEVICE9 pGraphic_Device)
{
	CScene_Stage3*	pInstance = new CScene_Stage3(pGraphic_Device);

	if (FAILED(pInstance->Ready_Scene()))
	{
		MSG_BOX("Failed To Create CScene_Stage3");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CScene_Stage3::Free()
{


	CScene::Free();
}
