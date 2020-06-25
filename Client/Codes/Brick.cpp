#include "stdafx.h"
#include "..\Headers\Brick.h"
#include "KeyMgr.h"
#include "GameManager.h"

USING(Client)

CBrick::CBrick(PDIRECT3DDEVICE9 pGraphic_Device)
	:CGameObject(pGraphic_Device)
{
}

CBrick::CBrick(const CBrick & rhs)
	: CGameObject(rhs)
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

	m_pTransform->SetUp_Position(_float3(m_tDesc.tBaseDesc.vPos.x, m_tDesc.tBaseDesc.vPos.y + 10.f, m_tDesc.tBaseDesc.vPos.z));

	m_pTransform->SetUp_Scale(m_tDesc.tBaseDesc.vSize);

	CKeyMgr::Get_Instance()->RegisterObserver(m_tDesc.eSceneID, this);
	return S_OK;
}

_int CBrick::Update_GameObject(_double TimeDelta)
{
	if(m_bIsPick == true)
		CGameManager::Get_Instance()->Set_PickObject(true);

	MoveToMouseDrag();

	if (0.0 < m_tDesc.m_dStartFall)
		m_tDesc.m_dStartFall -= TimeDelta;

	if (false == m_bIsDoneIntro && m_tDesc.m_dStartFall <= 0.0)
	{
		m_pTransform->SetUp_Position(_float3(m_tDesc.tBaseDesc.vPos.x, m_pTransform->Get_State(CTransform::STATE_POSITION).y - 0.3f, m_tDesc.tBaseDesc.vPos.z));

		if (m_pTransform->Get_State(CTransform::STATE_POSITION).y <= m_tDesc.tBaseDesc.vPos.y)
		{
			m_pTransform->SetUp_Position(_float3(m_tDesc.tBaseDesc.vPos.x, m_tDesc.tBaseDesc.vPos.y, m_tDesc.tBaseDesc.vPos.z));
			m_bIsDoneIntro = true;
		}
	}

	if (nullptr == m_pBoxCollider	||
		nullptr == m_pTransform)
		return E_FAIL;

	m_pBoxCollider->Update_Collider(m_pTransform->Get_WorldMatrix());

	if(true == m_bIsDoneIntro)
		MoveLimitXY();


	return _int();
}

_int CBrick::Late_Update_GameObject(_double TimeDelta)
{
	if (nullptr == m_pRenderer) return -1;
	m_pRenderer->Add_RenderGroup(CRenderer::RENDER_NONALPHA, this);

	CManagement* pManagement = CManagement::Get_Instance();
	if (nullptr == pManagement) return -1;
	pManagement->Add_CollisionGroup(CCollisionMgr::COL_BOX, this);
	return 0;
}

HRESULT CBrick::Render_GameObject()
{

	_matrix			matView, matProj;

	CManagement* pEnginMgr = CManagement::Get_Instance();
	if (nullptr == pEnginMgr) return E_FAIL;
	matView = pEnginMgr->Get_Transform(D3DTS_VIEW);
	matProj = pEnginMgr->Get_Transform(D3DTS_PROJECTION);

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

HRESULT CBrick::OnKeyDown(_int KeyCode)
{
	if (VK_LBUTTON == KeyCode)
	{
		if (m_pVIBuffer->Pick_Polygon(g_hWnd, m_pTransform->Get_WorldMatrix(), &_float3()))
			m_bIsPick = true;
		else
			m_bIsPick = false;
	}

	return S_OK;
}

HRESULT CBrick::OnKeyUp(_int KeyCode)
{
	if (VK_LBUTTON == KeyCode)
	{
		m_bIsPick = false;
	}

	return S_OK;
}

void CBrick::OnCollisionEnter(CGameObject * _pOther)
{
}

void CBrick::OnCollisionStay(CGameObject * _pOther)
{
	if (false == m_bIsPick)
		return;
	CTransform* TargetTransform = (CTransform*)_pOther->Find_Component(L"Com_Transform");

	if (m_tDesc.m_vAxis == _float3(1.f, 0.f, 0.f))
	{
		if (m_pTransform->Get_State(CTransform::STATE_POSITION).x < TargetTransform->Get_State(CTransform::STATE_POSITION).x)
			m_pTransform->SetUp_Position(_float3(m_pTransform->Get_State(CTransform::STATE_POSITION).x - m_pBoxCollider->Get_CollDistance().x, m_pTransform->Get_State(CTransform::STATE_POSITION).y, m_pTransform->Get_State(CTransform::STATE_POSITION).z));
		else if (m_pTransform->Get_State(CTransform::STATE_POSITION).x > TargetTransform->Get_State(CTransform::STATE_POSITION).x)
			m_pTransform->SetUp_Position(_float3(m_pTransform->Get_State(CTransform::STATE_POSITION).x + m_pBoxCollider->Get_CollDistance().x, m_pTransform->Get_State(CTransform::STATE_POSITION).y, m_pTransform->Get_State(CTransform::STATE_POSITION).z));
	}
	else if (m_tDesc.m_vAxis == _float3(0.f, 1.f, 0.f))
	{
		if (m_pTransform->Get_State(CTransform::STATE_POSITION).y < TargetTransform->Get_State(CTransform::STATE_POSITION).y)
			m_pTransform->SetUp_Position(_float3(m_pTransform->Get_State(CTransform::STATE_POSITION).x, m_pTransform->Get_State(CTransform::STATE_POSITION).y - m_pBoxCollider->Get_CollDistance().y, m_pTransform->Get_State(CTransform::STATE_POSITION).z));
		else if (m_pTransform->Get_State(CTransform::STATE_POSITION).y > TargetTransform->Get_State(CTransform::STATE_POSITION).y)
			m_pTransform->SetUp_Position(_float3(m_pTransform->Get_State(CTransform::STATE_POSITION).x, m_pTransform->Get_State(CTransform::STATE_POSITION).y + m_pBoxCollider->Get_CollDistance().y, m_pTransform->Get_State(CTransform::STATE_POSITION).z));

	}
	else if (m_tDesc.m_vAxis == _float3(0.f, 0.f, 1.f))
	{
		if (m_pTransform->Get_State(CTransform::STATE_POSITION).z < TargetTransform->Get_State(CTransform::STATE_POSITION).z)
			m_pTransform->SetUp_Position(_float3(m_pTransform->Get_State(CTransform::STATE_POSITION).x, m_pTransform->Get_State(CTransform::STATE_POSITION).y, m_pTransform->Get_State(CTransform::STATE_POSITION).z - m_pBoxCollider->Get_CollDistance().z));
		else if (m_pTransform->Get_State(CTransform::STATE_POSITION).z > TargetTransform->Get_State(CTransform::STATE_POSITION).z)
			m_pTransform->SetUp_Position(_float3(m_pTransform->Get_State(CTransform::STATE_POSITION).x, m_pTransform->Get_State(CTransform::STATE_POSITION).y, m_pTransform->Get_State(CTransform::STATE_POSITION).z + m_pBoxCollider->Get_CollDistance().z));
	}

}

HRESULT CBrick::MoveToMouseDrag()
{
	POINT		ptMouse;

	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	D3DVIEWPORT9		ViewPort;
	m_pGraphic_Device->GetViewport(&ViewPort);

	_float3		vMousePos = _float3((_float)ptMouse.x, (_float)ptMouse.y, 0.0f);

	// 2차원 투영 스페이스로 변환한다.(0, 0, g_iWinCX, g_iWinCY -> -1, 1, 1, -1)
	vMousePos.x = vMousePos.x / (ViewPort.Width * 0.5f) - 1.f;
	vMousePos.y = vMousePos.y / -(ViewPort.Height * 0.5f) + 1.f;
	vMousePos.z = 0.f;

	// 투영스페이스 -> 뷰스페이스 (투영행렬의 역행렬 곱하기)
	CManagement* pManagement = CManagement::Get_Instance();
	if (nullptr == pManagement)
		return false;
	Safe_AddRef(pManagement);

	_matrix InverseProjetion = pManagement->Get_Transform(D3DTS_PROJECTION);
	D3DXMatrixInverse(&InverseProjetion, nullptr, &InverseProjetion);

	D3DXVec3TransformCoord(&vMousePos, &vMousePos, &InverseProjetion);

	// 뷰 스페이스에서의 마우스의 시작점, 레이를 구한다
	_float3		vMousePivot = _float3(0.f, 0.f, 0.f);
	_float3		vMouseRay = _float3(vMousePos.x, vMousePos.y, vMousePos.z) - vMousePivot;

	// 뷰스페이스 -> 월드스페이스 (뷰행렬의 역행렬을 구한다)
	_matrix ViewMatrix = pManagement->Get_Transform(D3DTS_VIEW);
	D3DXMatrixInverse(&ViewMatrix, nullptr, &ViewMatrix);

	// 구한 뷰 공간의 역행렬을 마우스의 좌표에 곱한다. ( 마우스 좌표의 월드행렬화 )
	D3DXVec3TransformCoord(&vMousePivot, &vMousePivot, &ViewMatrix);
	D3DXVec3TransformNormal(&vMouseRay, &vMouseRay, &ViewMatrix);

	D3DXVec3Normalize(&vMouseRay, & vMouseRay);

	/*if (m_tDesc.m_vAxis == _float3(1.f, 0.f, 0.f))
	{
		m_pTransform->SetUp_Position(vMousePivot + (vMouseRay * 10.f));
	}
	else if (m_tDesc.m_vAxis == _float3(0.f, 1.f, 0.f))
	{
		m_pTransform->SetUp_Position(vMousePivot + (vMouseRay * 10.f));
	}
	else if (m_tDesc.m_vAxis == _float3(0.f, 0.f, 1.f))
	{
		m_pTransform->SetUp_Position(vMousePivot + (vMouseRay * 10.f));
	}*/

	_float X = (vMousePivot + (vMouseRay * 10.f )).x;
	_float Y = (vMousePivot + (vMouseRay * 10.f )).y;
	_float Z = (vMousePivot + (vMouseRay * 10.f )).z;

	CurMousePos = _float3(X, Y, Z);
	if (false == OldSetOnece)
	{
		OldMousePos = CurMousePos;
		OldSetOnece = true;
	}
	fDir = _float3(0.f, 0.f, 0.f);
	if (OldMousePos != CurMousePos)
	{
		fDir = CurMousePos - OldMousePos;

		OldMousePos = CurMousePos;
	}
	if (m_bIsPick)
	{
		if (m_tDesc.m_vAxis == _float3(1.f, 0.f, 0.f))
			m_pTransform->SetUp_Position(_float3(m_pTransform->Get_State(CTransform::STATE_POSITION).x + fDir.x, m_pTransform->Get_State(CTransform::STATE_POSITION).y, m_pTransform->Get_State(CTransform::STATE_POSITION).z));
		else if (m_tDesc.m_vAxis == _float3(0.f, 1.f, 0.f))
			m_pTransform->SetUp_Position(_float3(m_pTransform->Get_State(CTransform::STATE_POSITION).x, m_pTransform->Get_State(CTransform::STATE_POSITION).y + fDir.y, m_pTransform->Get_State(CTransform::STATE_POSITION).z));
		else if (m_tDesc.m_vAxis == _float3(0.f, 0.f, 1.f))
			m_pTransform->SetUp_Position(_float3(m_pTransform->Get_State(CTransform::STATE_POSITION).x, m_pTransform->Get_State(CTransform::STATE_POSITION).y, m_pTransform->Get_State(CTransform::STATE_POSITION).z + fDir.z));
	}


	Safe_Release(pManagement);

	return S_OK;
}

HRESULT CBrick::MoveLimitXY()
{
	CManagement* pManagement = CManagement::Get_Instance();
	if (nullptr == pManagement) return -1;

	CTransform* pTargetTransform = (CTransform*)(pManagement->Get_ObjectPointer(SCENE_STAGE, L"Layer_Field")->Find_Component(L"Com_Transform"));
	_float3	MyPos = m_pTransform->Get_State(CTransform::STATE_POSITION);

	_float FieldCX = pTargetTransform->Get_State(CTransform::STATE_RIGHT).x / 2.f;
	_float FieldCY = pTargetTransform->Get_State(CTransform::STATE_UP).y / 2.f;
	
	_float MyTopY = m_pTransform->Get_State(CTransform::STATE_POSITION).y + (m_pTransform->Get_State(CTransform::STATE_UP).y / 2);
	_float MyBottomY = m_pTransform->Get_State(CTransform::STATE_POSITION).y - (m_pTransform->Get_State(CTransform::STATE_UP).y / 2);

	_float MyRightX = m_pTransform->Get_State(CTransform::STATE_POSITION).x + (m_pTransform->Get_State(CTransform::STATE_RIGHT).x / 2);
	_float MyLeftX = m_pTransform->Get_State(CTransform::STATE_POSITION).x - (m_pTransform->Get_State(CTransform::STATE_RIGHT).x / 2);

	if (_float3(0.f, FieldCY, 0.f).y < MyTopY)
		m_pTransform->SetUp_Position(_float3(MyPos.x, MyPos.y - (MyTopY - FieldCY), MyPos.z));

	if (_float3(0.f, -FieldCY, 0.f).y > MyBottomY)
		m_pTransform->SetUp_Position(_float3(MyPos.x, MyPos.y + -(MyBottomY + FieldCY), MyPos.z));

	if (_float3(FieldCX, 0.f, 0.f).x < MyRightX)
		m_pTransform->SetUp_Position(_float3(MyPos.x - (MyRightX - FieldCX), MyPos.y, MyPos.z));

	if (_float3(-FieldCX, 0.f, 0.f).x > MyLeftX)
		m_pTransform->SetUp_Position(_float3(MyPos.x + -(MyLeftX + FieldCX), MyPos.y, MyPos.z));


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
	CKeyMgr::Get_Instance()->UnRegisterObserver(m_tDesc.eSceneID, this);
	Safe_Release(m_pRenderer);
	Safe_Release(m_pShader);
	Safe_Release(m_pTexture);
	Safe_Release(m_pTransform);
	Safe_Release(m_pVIBuffer);
	Safe_Release(m_pBoxCollider);
	CGameObject::Free();
}
