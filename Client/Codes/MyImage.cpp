#include "stdafx.h"
#include "MyImage.h"
#include "Management.h"
#include "VIBuffer_ViewPort.h"
#include "KeyMgr.h"
#include "Clock.h"
USING(Client)

CMyImage::CMyImage(CMyImage & _rhs)
	: CGameObject(_rhs)
{

}


HRESULT CMyImage::Ready_GameObject_Prototype()
{
	return S_OK;
}

HRESULT CMyImage::Ready_GameObject(void* pArg)
{
	if (nullptr != pArg)
		memcpy(&m_tDesc, pArg, sizeof(STATEDESC));


	if (FAILED(Add_Component(SCENE_STATIC, L"Component_Transform", L"Com_Transform", (CComponent**)&m_pTransform)))
		return E_FAIL;
	if (FAILED(Add_Component(SCENE_STATIC, L"Component_VIBuffer_ViewPort", L"Com_VIBuffer_ViewPort", (CComponent**)&m_pVIBuffer)))
		return E_FAIL;
	if (FAILED(Add_Component(m_tDesc.m_iTextureSceneID, m_tDesc.m_pTextureTag, L"Texture", (CComponent**)&m_pTexture)))
		return E_FAIL;
	if (FAILED(Add_Component(SCENE_STATIC, L"Component_Shader_ViewPort", L"Shader_ViewPort", (CComponent**)&m_pShader)))
		return E_FAIL;
	if (FAILED(Add_Component(SCENE_STATIC, L"Component_Renderer", L"Com_Renderer", (CComponent**)&m_pRenderer)))
		return E_FAIL;


	m_pTransform->SetUp_Position(m_tDesc.m_tBaseDesc.vPos);
	m_pTransform->SetUp_Scale(m_tDesc.m_tBaseDesc.vSize);
	return S_OK;
}




_int CMyImage::Update_GameObject(_double _timeDelta)
{

	if (m_bDead)
		return -1;

	if (m_bExpand)
	{
		if ( nullptr == m_pTransform)
			return -1;

		_float3 vOldSize = m_pTransform->Get_Scaled();
		_float3 vSize =  _float3(vOldSize.x + _float(m_vExpandSpeed.x * _timeDelta), vOldSize.y + _float(m_vExpandSpeed.y * _timeDelta), vOldSize.z + _float(m_vExpandSpeed.z * _timeDelta));
		m_pTransform->SetUp_Scale(vSize);
		if (vSize.x >= m_vMaxExpandSize.x || vSize.y >= m_vMaxExpandSize.y || vSize.z >= m_vMaxExpandSize.z)
			m_bExpand = false;
	}


	return 0;
}


_int CMyImage::Late_Update_GameObject(_double _timeDelta)
{
	if (!m_bActive)
		return 0;

	if (nullptr == m_pRenderer)
		return -1;

	if (FAILED(m_pRenderer->Add_RenderGroup(CRenderer::RENDER_UI, this)))
		return -1;

	return 0;
}

HRESULT CMyImage::Render_GameObject()
{
	if (!m_bActive)
		return 0;

	if (nullptr == m_pVIBuffer ||
		nullptr == m_pTransform ||
		nullptr == m_pTexture)
		return E_FAIL;

	CManagement* pEngineMgr = CManagement::Get_Instance();


	if (FAILED(m_pVIBuffer->Set_Transform(m_pTransform->Get_WorldMatrix())))
		return E_FAIL;

	ALPHABLEND;

	if (FAILED(m_pTexture->Set_TextureOnShader(m_pShader, "g_BaseTexture", 0)))
		return E_FAIL;

	if (FAILED(m_pShader->Begin_Shader()))
		return E_FAIL;
	if (FAILED(m_pShader->Begin_Pass(0)))
		return E_FAIL;


	if (FAILED(m_pVIBuffer->Render()))
		return E_FAIL;


	if (FAILED(m_pShader->End_Pass()))
		return E_FAIL;

	if (FAILED(m_pShader->End_Shader()))
		return E_FAIL;


	ALPHABLEND_END;

	return S_OK;
}




void CMyImage::Expand(_float3 _vMaxSize, _float3 _fExpandSpeed)
{
	m_bExpand = true;
	m_vMaxExpandSize = _vMaxSize;
	m_vExpandSpeed = _fExpandSpeed;
}



CMyImage * CMyImage::Create(PDIRECT3DDEVICE9 _pGraphic_Device)
{
	CMyImage* pInstance = new CMyImage(_pGraphic_Device);
	if (FAILED(pInstance->Ready_GameObject_Prototype()))
	{
		MSG_BOX("Fail to create CMyImage");
		Safe_Release(pInstance);

	}
	return pInstance;
}

CGameObject * CMyImage::Clone_GameObject(void * pArg)
{
	CMyImage* pInstance = new CMyImage(*this);
	if (FAILED(pInstance->Ready_GameObject(pArg)))
	{
		MSG_BOX("Fail to clone CMyImage");
		Safe_Release(pInstance);

	}
	return pInstance;
}



void CMyImage::Free()
{

	Safe_Release(m_pShader);
	Safe_Release(m_pVIBuffer);
	Safe_Release(m_pTransform);
	Safe_Release(m_pTexture);
	Safe_Release(m_pRenderer);

	CGameObject::Free();

}


_uint CMyImage::Get_Depth()
{
	return m_tDesc.m_iDepth;
}


