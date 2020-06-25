#include "stdafx.h"
#include "GameEndPanel.h"
#include "Management.h"
#include "VIBuffer_ViewPort.h"
#include "KeyMgr.h"
#include "Clock.h"
#include "MyImage.h"
#include "MyButton.h"

USING(Client)

CGameEndPanel::CGameEndPanel(CGameEndPanel & _rhs)
	: CGameObject(_rhs)
{

}


HRESULT CGameEndPanel::Ready_GameObject_Prototype()
{
	return S_OK;
}

HRESULT CGameEndPanel::Ready_GameObject(void* pArg)
{
	CManagement* pEngineMgr = CManagement::Get_Instance();
	if (nullptr == pEngineMgr) return E_FAIL;

	CMyImage::STATEDESC bannerDesc;
	bannerDesc.m_eSceneID = SCENE_STAGE;
	bannerDesc.m_tBaseDesc = BASEDESC(_float3(g_iWinSizeX * 0.5f, g_iWinSizeY * 0.5f - 100.f, 0.f), _float3((_float)g_iWinSizeX, 1.f, 1.f));
	bannerDesc.m_iTextureSceneID = SCENE_STATIC;
	bannerDesc.m_pTextureTag = L"Component_Texture_Banner";
	CMyImage* pWinBanner = nullptr;
	if (nullptr == (pWinBanner = (CMyImage*)pEngineMgr->Add_Object_ToLayer(SCENE_STATIC, L"GameObject_MyImage", SCENE_STAGE, L"Layer_WinBanner", &bannerDesc)))
		return E_FAIL;

	pWinBanner->Expand(_float3(g_iWinSizeX, 128.f, 1.f), _float3(0.f, 500.f, 0.f));


	CMyButton::STATEDESC btnDesc;
	btnDesc.m_eSceneID = SCENE_STAGE;
	btnDesc.m_tBaseDesc = BASEDESC(_float3((g_iWinSizeX >> 1) + 100.f, (g_iWinSizeY >> 1) + 100.f, 0.f), _float3(100.f, 100.f, 10.f));
	btnDesc.m_iTextureSceneID = SCENE_STATIC;
	btnDesc.m_pTextureTag = L"Component_Texture_Btn";
	btnDesc.m_iTextureID = 1;

	CGameObject* pObj;
	if (nullptr == (pObj = pEngineMgr->Add_Object_ToLayer(SCENE_STATIC, L"GameObject_MyButton", SCENE_STAGE, L"GameObject", &btnDesc)))
		return E_FAIL;

	return S_OK;
}




_int CGameEndPanel::Update_GameObject(_double _timeDelta)
{
	if (m_bDead)
		return -1;


	return 0;
}


_int CGameEndPanel::Late_Update_GameObject(_double _timeDelta)
{
	
	return 0;
}

HRESULT CGameEndPanel::Render_GameObject()
{
	
	return S_OK;
}



CGameEndPanel * CGameEndPanel::Create(PDIRECT3DDEVICE9 _pGraphic_Device)
{
	CGameEndPanel* pInstance = new CGameEndPanel(_pGraphic_Device);
	if (FAILED(pInstance->Ready_GameObject_Prototype()))
	{
		MSG_BOX("Fail to create CGameEndPanel");
		Safe_Release(pInstance);

	}
	return pInstance;
}

CGameObject * CGameEndPanel::Clone_GameObject(void * pArg)
{
	CGameEndPanel* pInstance = new CGameEndPanel(*this);
	if (FAILED(pInstance->Ready_GameObject(pArg)))
	{
		MSG_BOX("Fail to clone CGameEndPanel");
		Safe_Release(pInstance);

	}
	return pInstance;
}



void CGameEndPanel::Free()
{
	CGameObject::Free();

}


_uint CGameEndPanel::Get_Depth()
{
	return m_tDesc.m_iDepth;
}


