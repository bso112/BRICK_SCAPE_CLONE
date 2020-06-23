#include "stdafx.h"
#include "..\Headers\Brick.h"

USING(Client)

CBrick::CBrick(PDIRECT3DDEVICE9 pGraphic_Device)
	:CGameObject(pGraphic_Device)
{
}

CBrick::CBrick(const CBrick & rhs)
	:CGameObject(rhs)
{
}

HRESULT CBrick::Ready_GameObject_Prototype()
{
	return S_OK;
}

HRESULT CBrick::Ready_GameObject(void * pArg)
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

	if (FAILED(Add_Component(SCENE_STATIC, L"Component_VIBuffer_Cube", L"Com_VIBuffer_Cube", (CComponent**)&m_pVIBuffer)))
		return E_FAIL;

	if (FAILED(Add_Component(SCENE_STATIC, L"Component_Renderer", L"Com_Renderer", (CComponent**)&m_pRenderer)))
		return E_FAIL;

	m_pTransform->SetUp_Position(_float3(m_tDesc.tBaseDesc.vPos.x, m_tDesc.tBaseDesc.vPos.y + 10.f, m_tDesc.tBaseDesc.vPos.z));

	m_pTransform->SetUp_Scale(m_tDesc.tBaseDesc.vSize);

	return S_OK;
}

_int CBrick::Update_GameObject(_double TimeDelta)
{
	if (false == m_bIsDoneIntro)
	{
		m_pTransform->SetUp_Position(_float3(m_tDesc.tBaseDesc.vPos.x, m_pTransform->Get_State(CTransform::STATE_POSITION).y - 0.3f, m_tDesc.tBaseDesc.vPos.z));
		
		if (m_pTransform->Get_State(CTransform::STATE_POSITION).y <= m_tDesc.tBaseDesc.vPos.y)
			m_bIsDoneIntro = true;
	}


	return _int();
}

_int CBrick::Late_Update_GameObject(_double TimeDelta)
{
	if (nullptr == m_pRenderer) return -1;
	m_pRenderer->Add_RenderGroup(CRenderer::RENDER_NONALPHA, this);
	return 0;
}

HRESULT CBrick::Render_GameObject()
{
	
	_matrix			matView, matProj;

	CManagement* pEnginMgr = CManagement::Get_Instance();
	if (nullptr == pEnginMgr) return E_FAIL;
	matView = pEnginMgr->Get_Transform(D3DTS_VIEW);
	matProj = pEnginMgr->Get_Transform(D3DTS_PROJECTION);

	//if (FAILED(m_pTexture->Set_TextureOnShader(m_pShader, "g_BaseTexture", m_tDesc.m_iTextureID)))
	//	return E_FAIL;

	if (FAILED(m_pShader->Set_Value("g_matWorld", &m_pTransform->Get_WorldMatrix(), sizeof(_matrix))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_Value("g_matView", &matView, sizeof(_matrix))))
		return E_FAIL;
	if (FAILED(m_pShader->Set_Value("g_matProj", &matProj, sizeof(_matrix))))
		return E_FAIL;

	if (FAILED(m_pShader->Begin_Shader()))
		return E_FAIL;

	if (FAILED(m_pShader->Begin_Pass(0)))
		return E_FAIL;

	if (FAILED(m_pVIBuffer->Render_VIBuffer()))
		return E_FAIL;

	if (FAILED(m_pShader->End_Pass()))
		return E_FAIL;
	if (FAILED(m_pShader->End_Shader()))
		return E_FAIL;
	return S_OK;


}

CBrick * CBrick::Create(PDIRECT3DDEVICE9 pGraphic_Device)
{
	CBrick*	pInstance = new CBrick(pGraphic_Device);

	if (FAILED(pInstance->Ready_GameObject_Prototype()))
	{
		MSG_BOX("Failed To Create CBrick");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CBrick::Clone_GameObject(void * pArg)
{
	CBrick*	pInstance = new CBrick(*this);

	if (FAILED(pInstance->Ready_GameObject(pArg)))
	{
		MSG_BOX("Failed To Create CBrick");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CBrick::Free()
{
	Safe_Release(m_pRenderer);
	Safe_Release(m_pShader);
	Safe_Release(m_pTexture);
	Safe_Release(m_pTransform);
	Safe_Release(m_pVIBuffer);
	CGameObject::Free();
}
