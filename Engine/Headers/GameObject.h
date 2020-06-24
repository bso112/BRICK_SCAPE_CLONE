#pragma once

#include "Base.h"

BEGIN(Engine)

class CComponent;
class ENGINE_DLL CGameObject abstract : public CBase
{
protected:
	explicit CGameObject(PDIRECT3DDEVICE9 pGraphic_Device);
	explicit CGameObject(const CGameObject& rhs);
	virtual ~CGameObject() = default;
public:
	virtual HRESULT Ready_GameObject_Prototype();
	virtual HRESULT Ready_GameObject(void* pArg);
	virtual _int Update_GameObject(_double TimeDelta);
	virtual _int Late_Update_GameObject(_double TimeDelta);
	virtual HRESULT Render_GameObject();


public:
	bool Get_isCollided() { return m_bCollided; }
	void Set_isCollided(bool _bCollided) { m_bCollided = _bCollided; }
	//충돌한 오브젝트를 저장한다.
	void Add_Collided(CGameObject* _pColided) { m_setCollided.insert(_pColided); }
	//충돌한 오브젝트 셋의 사이즈를 가져온다.
	size_t Get_CollidedSize() { return m_setCollided.size(); }
	//충돌한 오브젝트 셋에 _pCollied가 있는지 검사한다.
	bool Contain_Collided(CGameObject* _pCollided)
	{
		return m_setCollided.find(_pCollided) != m_setCollided.end();
	}

	bool Erase_Collided(CGameObject* _pCollided)
	{
		//returns the number of elements removed
		return m_setCollided.erase(_pCollided) ? true : false;

	}
	void Set_Dead() { m_bDead = true;  }
	const bool& Get_Dead() const { return m_bDead; }

protected:
	HRESULT Add_Component(_uint iPrototypeSceneID, const _tchar* pPrototypeTag, const _tchar * pComponentTag, CComponent** ppOut, void* pArg = nullptr);
public:
	CComponent* Find_Component(const _tchar* pComponentTag);

public:
	virtual void OnCollisionEnter(CGameObject* _pOther);
	virtual void OnCollisionStay(CGameObject* _pOther);
	virtual void OnCollisionExit(CGameObject* _pOther);

protected:
	PDIRECT3DDEVICE9			m_pGraphic_Device = nullptr;
	_bool						m_bActive = true;
	_bool						m_bDead = false;

protected:	
	map<const _tchar*, CComponent*>			m_Components;
	typedef map<const _tchar*, CComponent*>	COMPONENTS;

private:
	//충돌했나
	bool	m_bCollided = false;
	//충돌한 오브젝트 셋
	set<CGameObject*> m_setCollided;

public:
	virtual CGameObject* Clone_GameObject(void* pArg) = 0;
	virtual void Free();
};

END