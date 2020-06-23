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
