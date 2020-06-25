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
		BASEDESC		tBaseDesc;
		SCENEID			eSceneID = SCENE_END;
		const _tchar*	pTextureTag = nullptr;
		SCENEID			eTextureSceneID = SCENE_END;
		_uint			iTextureID = 0;
		_bool			bPlayer;
		_double			m_dStartFall;

		_float3			m_vAxis;
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
public:
	virtual HRESULT	OnKeyDown(_int KeyCode);
	virtual HRESULT	OnKeyUp(_int KeyCode);

public:
	_bool	IsPlayer() { return m_tDesc.bPlayer; }

public:
	virtual void OnCollisionEnter(CGameObject* _pOther);
	virtual void OnCollisionStay(CGameObject* _pOther);
private:
	CTransform*		m_pTransform = nullptr;
	CVIBuffer*		m_pVIBuffer = nullptr;
	CTexture*		m_pTexture = nullptr;
	CRenderer*		m_pRenderer = nullptr;
	CShader*		m_pShader = nullptr;
	CCollider_Box*	m_pBoxCollider = nullptr;
private:
	STATEDESC	m_tDesc;
	_bool		m_bIsDoneIntro = false;

private:
	_float3 CurMousePos;
	_float3 OldMousePos;
	_float3	fDir;

	_bool OldSetOnece = false;

private:
	_bool	m_bIsPick = false;
private:
	HRESULT	MoveToMouseDrag();
	HRESULT	MoveLimitXY();
	static _float ZBuffer;
public:
	static CBrick* Create(PDIRECT3DDEVICE9 pGraphic_Device);
	virtual CGameObject* Clone_GameObject(void* pArg);
	virtual void Free();
};
END
