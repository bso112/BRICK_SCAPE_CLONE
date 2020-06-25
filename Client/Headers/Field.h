#pragma once
#include "GameObject.h"

#include "Management.h"
#include "Client_Defines.h"

BEGIN(Client)
class CWall;
class CGoal;
class CField : public CGameObject
{
public:
	typedef struct tagStatedesc
	{
		BASEDESC	tBaseDesc;
		SCENEID		eSceneID = SCENE_END;
		_uint		iBrickNumX = 0;
		_uint		iBrickNumY = 0;
	}STATEDESC;
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
	CWall**	Get_Walls();


private:
	STATEDESC	m_tDesc;
	CWall*	m_Walls[6];
	CGoal*	m_pGoal = nullptr;
public:
	static CField* Create(PDIRECT3DDEVICE9 pGraphic_Device);
	virtual CField* Clone_GameObject(void* pArg);
	virtual void Free();


};
END
