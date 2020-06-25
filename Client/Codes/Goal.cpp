#include "stdafx.h"
#include "..\Headers\Goal.h"


CGoal::CGoal(PDIRECT3DDEVICE9 pGraphic_Device)
	:CGameObject(pGraphic_Device)
{
}

CGoal::CGoal(const CGoal & rhs)
	:CGameObject(rhs)
{
}

HRESULT CGoal::Ready_GameObject_Prototype()
{
	return S_OK;
}

HRESULT CGoal::Ready_GameObject(void * pArg)
{
	if (nullptr != pArg)
		memcpy(&m_tDesc, pArg, sizeof(STATEDESC));

	if (FAILED(Add_Component(SCENE_STATIC, L"Component_Transform", L"Com_Transform", (CComponent**)&m_pTransform)))
		return E_FAIL;

	if (FAILED(Add_Component(m_tDesc.eTextureSceneID, m_tDesc.pTextureTag, L"Com_Texture", (CComponent**)&m_pTexture)))
		return E_FAIL;


	if (FAILED(Add_Component(SCENE_STATIC, L"Component_Shader_Rect", L"Com_Shader_Rect", (CComponent**)&m_pShader)))
		return E_FAIL;

	if (FAILED(Add_Component(SCENE_STATIC, L"Component_VIBuffer_Cube", L"Com_VIBuffer_Cube", (CComponent**)&m_pVIBuffer)))
		return E_FAIL;

	if (FAILED(Add_Component(SCENE_STATIC, L"Component_Renderer", L"Com_Renderer", (CComponent**)&m_pRenderer)))
		return E_FAIL;

	if (FAILED(Add_Component(SCENE_STATIC, L"Component_BoxCollider", L"Com_Collider", (CComponent**)&m_pBoxCollider)))
		return E_FAIL;

	m_pTransform->SetUp_Position(m_tDesc.tBaseDesc.vPos);
	m_pTransform->SetUp_Scale(m_tDesc.tBaseDesc.vSize);


	return S_OK;
}

_int CGoal::Update_GameObject(_double TimeDelta)
{
	if (nullptr == m_pBoxCollider ||
		nullptr == m_pTransform)
		return E_FAIL;

	m_pBoxCollider->Update_Collider(m_pTransform->Get_WorldMatrix());
	return _int();
}

_int CGoal::Late_Update_GameObject(_double TimeDelta)
{
	if (nullptr == m_pRenderer) return -1;
	m_pRenderer->Add_RenderGroup(CRenderer::RENDER_ALPHABLEND, this);
	CManagement* pManagement = CManagement::Get_Instance();
	if (nullptr == pManagement) return -1;
	pManagement->Add_CollisionGroup(CCollisionMgr::COL_BOX, this);
	return _int();
}

HRESULT CGoal::Render_GameObject()
{
	_matrix			matView, matProj;

	CManagement* pEnginMgr = CManagement::Get_Instance();
	if (nullptr == pEnginMgr) return E_FAIL;
	matView = pEnginMgr->Get_Transform(D3DTS_VIEW);
	matProj = pEnginMgr->Get_Transform(D3DTS_PROJECTION);

	ALPHABLEND;
	if (FAILED(m_pTexture->Set_TextureOnShader(m_pShader, "g_BaseTexture", m_tDesc.iTextureID)))
		return E_FAIL;

	if (FAILED(m_pShader->Set_Value("g_matWorld", &m_pTransform->Get_WorldMatrix(), sizeof(_matrix))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_Value("g_matView", &matView, sizeof(_matrix))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_Value("g_matProj", &matProj, sizeof(_matrix))))
		return E_FAIL;

	if (FAILED(m_pShader->Begin_Shader()))
		return E_FAIL;

	if (FAILED(m_pShader->Begin_Pass(PASS_GOAL)))
		return E_FAIL;

	if (FAILED(m_pVIBuffer->Render_VIBuffer()))
		return E_FAIL;

	if (FAILED(m_pShader->End_Pass()))
		return E_FAIL;
	if (FAILED(m_pShader->End_Shader()))
		return E_FAIL;

	ALPHABLEND_END;
	return S_OK;
}

void CGoal::OnCollisionEnter(CGameObject * _pOther)
{
	int i = 0;
}

CGoal * CGoal::Create(PDIRECT3DDEVICE9 pGraphic_Device)
{
	CGoal*	pInstance = new CGoal(pGraphic_Device);

	if (FAILED(pInstance->Ready_GameObject_Prototype()))
	{
		MSG_BOX("Failed To Create CGoal");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGoal * CGoal::Clone_GameObject(void * pArg)
{
	CGoal*	pInstance = new CGoal(*this);

	if (FAILED(pInstance->Ready_GameObject(pArg)))
	{
		MSG_BOX("Failed To Create CGoal");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CGoal::Free()
{
	Safe_Release(m_pRenderer);
	Safe_Release(m_pShader);
	Safe_Release(m_pBoxCollider);
	Safe_Release(m_pTexture);
	Safe_Release(m_pTransform);
	Safe_Release(m_pVIBuffer);
	CGameObject::Free();
}
