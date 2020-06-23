#pragma once
#include "GameObject.h"

BEGIN(Engine)
class CTransform;
class CVIBuffer;
class CTexture;
class CRenderer;
END

BEGIN(Client)

class CWall : public CGameObject
{
protected:
	explicit CWall(PDIRECT3DDEVICE9 pGraphic_Device);
	explicit CWall(const CWall& rhs);
	virtual ~CWall() = default;


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

public:
	static CWall* Create(PDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone_GameObject(void* pArg);
	virtual void Free();


};
END
