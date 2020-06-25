#include "stdafx.h"
#include "..\Headers\Camera_Free.h"
#include "GameManager.h"

CCamera_Free::CCamera_Free(PDIRECT3DDEVICE9 pGraphic_Device)
	: CCamera(pGraphic_Device)
{
}

CCamera_Free::CCamera_Free(const CCamera_Free & rhs)
	: CCamera(rhs)
{

}

HRESULT CCamera_Free::Ready_GameObject_Prototype()
{
	return S_OK;
}

HRESULT CCamera_Free::Ready_GameObject(void * pArg)
{
	if (CCamera::Ready_GameObject(pArg))
		return E_FAIL;

	m_vDirVec = m_StateDesc.vEye - m_StateDesc.vAt;
	D3DXVec3Normalize(&m_vDirVec, &m_vDirVec);
	m_pTransformCom->SetUp_Position(_float3(0.f, 0.f, 0.f) + (m_vDirVec * fCameraZommDist));

	return S_OK;
}

_int CCamera_Free::Update_GameObject(_double TimeDelta)
{
	POINT		ptMouse;

	if (GetKeyState('Q') & 0x8000 && 15.f >= fCameraZommDist)
		fCameraZommDist += 0.3f;
	else if (GetKeyState('E') & 0x8000 && 5.f <= fCameraZommDist)
		fCameraZommDist -= 0.3f;

	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);
	CurMousePos = _float3((_float)ptMouse.x, (_float)ptMouse.y, 0.f);

	if (OldMousePos != CurMousePos)
	{
		fDir = CurMousePos - OldMousePos;

		OldMousePos = CurMousePos;
	}

	if (!(CGameManager::Get_Instance()->Get_IsGameStart()) || CGameManager::Get_Instance()->Get_IsPickObject())
		return CCamera::Update_GameObject(TimeDelta);


	_float3		vRight, vUp, vLook;

	vLook = m_vDirVec;
	D3DXVec3Normalize(&vLook, &vLook);
	D3DXVec3Cross(&vRight, &_float3(0.f, 1.f, 0.f), &vLook);
	D3DXVec3Cross(&vUp, &vLook, &vRight);
	D3DXVec3Normalize(&vRight, &vRight);
	D3DXVec3Normalize(&vUp, &vUp);

	if ((GetKeyState(VK_LBUTTON) & 0x8000))
	{
		_matrix		RotationMatrixY;
		D3DXMatrixRotationAxis(&RotationMatrixY, &vUp, D3DXToRadian(fDir.x / 3));

		_matrix		RotationMatrixX;
		D3DXMatrixRotationAxis(&RotationMatrixX, &vRight, D3DXToRadian(fDir.y / 3));

		D3DXVec3TransformNormal(&vRight, &vRight, &RotationMatrixY);
		D3DXVec3TransformNormal(&vUp, &vUp, &RotationMatrixY);
		D3DXVec3TransformNormal(&vLook, &vLook, &RotationMatrixY);

		if (0.95f >= vLook.y && -0.95f <= vLook.y)
		{
			D3DXVec3TransformNormal(&vRight, &vRight, &RotationMatrixX);
			D3DXVec3TransformNormal(&vUp, &vUp, &RotationMatrixX);
			D3DXVec3TransformNormal(&vLook, &vLook, &RotationMatrixX);
		}
		else
		{
			if (0.95f <= vLook.y)
			{
				if (0 < fDir.y)
				{
					D3DXVec3TransformNormal(&vRight, &vRight, &RotationMatrixX);
					D3DXVec3TransformNormal(&vUp, &vUp, &RotationMatrixX);
					D3DXVec3TransformNormal(&vLook, &vLook, &RotationMatrixX);
				}
			}
			else
			{
				if (0 > fDir.y)
				{
					D3DXVec3TransformNormal(&vRight, &vRight, &RotationMatrixX);
					D3DXVec3TransformNormal(&vUp, &vUp, &RotationMatrixX);
					D3DXVec3TransformNormal(&vLook, &vLook, &RotationMatrixX);
				}
			}
		}
	}

	D3DXVec3Normalize(&vLook, &vLook);

	m_pTransformCom->SetUp_Position(_float3(0.f, 0.f, 0.f) + (vLook * fCameraZommDist));

	_float3		Right, Up, Look;

	Look = _float3(0.f, 0.f, 0.f) - m_pTransformCom->Get_State(CTransform::STATE_POSITION);
	D3DXVec3Normalize(&Look, &Look);
	m_pTransformCom->Set_State(CTransform::STATE_LOOK, Look);

	D3DXVec3Cross(&Right, &_float3(0.f, 1.f, 0.f), &Look);
	D3DXVec3Normalize(&Right, &Right);
	m_pTransformCom->Set_State(CTransform::STATE_RIGHT, Right);

	D3DXVec3Cross(&Up, &Look, &Right);
	D3DXVec3Normalize(&Up, &Up);
	m_pTransformCom->Set_State(CTransform::STATE_UP, Up);

	m_vDirVec = vLook;
	fDir = _float3(0.f, 0.f, 0.f);

	return CCamera::Update_GameObject(TimeDelta);
}

_int CCamera_Free::Late_Update_GameObject(_double TimeDelta)
{
	return CCamera::Late_Update_GameObject(TimeDelta);
}

HRESULT CCamera_Free::Render_GameObject()
{
	return S_OK;
}

CCamera_Free * CCamera_Free::Create(PDIRECT3DDEVICE9 pGraphic_Device)
{
	CCamera_Free*	pInstance = new CCamera_Free(pGraphic_Device);

	if (FAILED(pInstance->Ready_GameObject_Prototype()))
	{
		MSG_BOX("Failed To Creating CLoading");
		Safe_Release(pInstance);
	}
	return pInstance;
}

CGameObject * CCamera_Free::Clone_GameObject(void * pArg)
{
	CCamera_Free*	pInstance = new CCamera_Free(*this);

	if (FAILED(pInstance->Ready_GameObject(pArg)))
	{
		MSG_BOX("Failed To Creating CLoading");
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CCamera_Free::Free()
{
	CCamera::Free();
}
