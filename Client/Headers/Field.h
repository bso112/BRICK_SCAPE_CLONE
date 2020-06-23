#pragma once
#include "GameObject.h"

#include "Management.h"
#include "Client_Defines.h"

BEGIN(Client)
class CWall;
class CField : public CGameObject
{
protected:
	explicit CField(PDIRECT3DDEVICE9 pGraphic_Device);
	explicit CField(const CField& rhs);
	virtual ~CField() = default;


public:
	virtual HRESULT Ready_GameObject_Prototype();
	virtual HRESULT Ready_GameObject(void* pArg);
	virtual _int Update_GameObject(_double TimeDelta);
	virtual _int Late_Update_GameObject(_double TimeDelta);
	virtual HRESULT Render_GameObject();

public:
	CWall*	Get_Walls();

private:
	CTransform*	m_pTransform = nullptr;
	CVIBuffer*	m_pVIBuffer = nullptr;
	CTexture*	m_pTexture = nullptr;
	CRenderer*	m_pRenderer = nullptr;

private:
	CWall*	m_Walls[6];

public:
	static CField* Create(PDIRECT3DDEVICE9 pGraphic_Device);
	virtual CField* Clone_GameObject(void* pArg);
	virtual void Free();


};
END
