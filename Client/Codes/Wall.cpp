#include "stdafx.h"
#include "..\Headers\Wall.h"

USING(Client)

CWall::CWall(PDIRECT3DDEVICE9 pGraphic_Device)
	:CGameObject(pGraphic_Device)
{
}

CWall::CWall(const CWall & rhs)
	: CGameObject(rhs)
{
}

HRESULT CWall::Ready_GameObject_Prototype()
{
	return S_OK;
}

HRESULT CWall::Ready_GameObject(void * pArg)
{
	if (nullptr != pArg)
		memcpy(&m_tDesc, pArg, sizeof(STATEDESC));

	CTransform::STATEDESC tTransformDesc;
	tTransformDesc.RotatePerSec = D3DXToRadian(90.f);
	tTransformDesc.SpeedPerSec = 5.0;
	if (FAILED(Add_Component(SCENE_STATIC, L"Component_Transform", L"Com_Transform", (CComponent**)&m_pTransform, &tTransformDesc)))
		return E_FAIL;

	//if (FAILED(Add_Component(m_tDesc.m_iTextureSceneID, m_tDesc.m_pTextureTag, L"Texture", (CComponent**)&m_pTexture)))
	//return E_FAIL;
	//

	if (FAILED(Add_Component(SCENE_STATIC, L"Component_Shader_Rect", L"Com_Shader_Rect", (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(Add_Component(SCENE_STATIC, L"Component_VIBuffer_Rect", L"Com_VIBuffer_Rect", (CComponent**)&m_pVIBuffer)))
		return E_FAIL;

	if (FAILED(Add_Component(SCENE_STATIC, L"Component_Renderer", L"Com_Renderer", (CComponent**)&m_pRenderer)))
		return E_FAIL;

	m_pTransform->SetUp_Position(m_tDesc.tBaseDesc.vPos);

	m_pTransform->SetUp_Scale(m_tDesc.tBaseDesc.vSize);
	return S_OK;
}

_int CWall::Update_GameObject(_double TimeDelta)
{
	return _int();
}

_int CWall::Late_Update_GameObject(_double TimeDelta)
{
	return _int();
}

HRESULT CWall::Render_GameObject()
{

	return S_OK;
}

CWall * CWall::Create(PDIRECT3DDEVICE9 pGraphic_Device)
{
	CWall*	pInstance = new CWall(pGraphic_Device);

	if (FAILED(pInstance->Ready_GameObject_Prototype()))
	{
		MSG_BOX("Failed To Create CField");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject* CWall::Clone_GameObject(void * pArg)
{
	CWall*	pInstance = new CWall(*this);

	if (FAILED(pInstance->Ready_GameObject(pArg)))
	{
		MSG_BOX("Failed To Create CField");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CWall::Free()
{
	CGameObject::Free();
}
