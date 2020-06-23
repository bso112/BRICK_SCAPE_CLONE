#pragma once
#include "GameObject.h"

#include "Management.h"
#include "Client_Defines.h"

BEGIN(Client)

class CBrick : public CGameObject
{
public:
	typedef struct tagStatedesc
	{
		BASEDESC tBaseDesc;
		_bool	 bPlayer;

	}STATEDESC;
protected:
	explicit CBrick(PDIRECT3DDEVICE9 pGraphic_Device);
	explicit CBrick(const CBrick& rhs);
	virtual ~CBrick() = default;


public:
	virtual HRESULT Ready_GameObject_Prototype();
	virtual HRESULT Ready_GameObject(void* pArg);
	virtual _int Update_GameObject(_double TimeDelta);
	virtual _int Late_Update_GameObject(_double TimeDelta);
	virtual HRESULT Render_GameObject();

private:
	CTransform*	m_pTransform = nullptr;
	CVIBuffer*	m_pVIBuffer = nullptr;
	CTexture*	m_pTexture = nullptr;
	CRenderer*	m_pRenderer = nullptr;
	CShader*	m_pShader = nullptr;
private:
	STATEDESC	m_tDesc;
	_bool		m_bIsDoneIntro = false;
public:
	static CBrick* Create(PDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone_GameObject(void* pArg);
	virtual void Free();
};
END
