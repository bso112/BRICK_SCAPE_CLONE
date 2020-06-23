#include "stdafx.h"
#include "..\Headers\Scene_Stage4.h"

CScene_Stage4::CScene_Stage4(PDIRECT3DDEVICE9 pGraphic_Device)
	: CScene(pGraphic_Device)
{

}

HRESULT CScene_Stage4::Ready_Scene()
{
	
	return S_OK;
}

_int CScene_Stage4::Update_Scene(_double TimeDelta)
{
	return _int();
}

HRESULT CScene_Stage4::Render_Scene()
{
	return S_OK;
}

CScene_Stage4 * CScene_Stage4::Create(PDIRECT3DDEVICE9 pGraphic_Device)
{
	CScene_Stage4*	pInstance = new CScene_Stage4(pGraphic_Device);

	if (FAILED(pInstance->Ready_Scene()))
	{
		MSG_BOX("Failed To Create CScene_Stage4");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CScene_Stage4::Free()
{


	CScene::Free();
}
