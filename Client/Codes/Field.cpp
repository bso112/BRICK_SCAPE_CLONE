#include "stdafx.h"
#include "..\Headers\Field.h"

USING(Client)

CField::CField(PDIRECT3DDEVICE9 pGraphic_Device)
	:CGameObject(pGraphic_Device)
{
}

CField::CField(const CField & rhs)
	:CGameObject(rhs)
{
	
}

HRESULT CField::Ready_GameObject_Prototype()
{
	return S_OK;
}

HRESULT CField::Ready_GameObject(void * pArg)
{
	return S_OK;
}

_int CField::Update_GameObject(_double TimeDelta)
{
	return _int();
}

_int CField::Late_Update_GameObject(_double TimeDelta)
{
	return _int();
}

HRESULT CField::Render_GameObject()
{
	return S_OK;
}

CWall * CField::Get_Walls()
{
	return nullptr;
}

CField * CField::Create(PDIRECT3DDEVICE9 pGraphic_Device)
{
	CField*	pInstance = new CField(pGraphic_Device);

	if (FAILED(pInstance->Ready_GameObject_Prototype()))
	{
		MSG_BOX("Failed To Create CField");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CField * CField::Clone_GameObject(void * pArg)
{
	CField*	pInstance = new CField(*this);

	if (FAILED(pInstance->Ready_GameObject(pArg)))
	{
		MSG_BOX("Failed To Create CField");
		Safe_Release(pInstance);
	}
	return pInstance;
}




void CField::Free()
{
	CGameObject::Free();
}
