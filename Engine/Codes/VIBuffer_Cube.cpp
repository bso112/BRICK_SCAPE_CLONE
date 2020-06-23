#include "..\Headers\VIBuffer_Cube.h"

CVIBuffer_Cube::CVIBuffer_Cube(LPDIRECT3DDEVICE9 pGraphic_Device)
	:CVIBuffer(pGraphic_Device)
{
}

CVIBuffer_Cube::CVIBuffer_Cube(const CVIBuffer_Cube & rhs)
	: CVIBuffer(rhs)
{
}

HRESULT CVIBuffer_Cube::Ready_Component_Prototype()
{
	//멤버변수 셋팅
	m_iStride = sizeof(VTXTEX);
	m_iNumVertices = 8;
	m_dwFVF = D3DFVF_XYZ | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE2(0);

	m_iNumPrimitive = 12;
	m_iIndexSize = sizeof(_ushort);
	m_iNumIndices = m_iNumPrimitive * 3;
	m_eIndexFormat = D3DFMT_INDEX16;

	if (FAILED(CVIBuffer::Ready_Component_Prototype()))
		return E_FAIL;

	//값 채우기

	VTXTEX* pVertices = nullptr;

	if (FAILED(m_pVBuffer->Lock(0, 0, (void**)&pVertices, 0)))
		return E_FAIL;

	pVertices[0].vPosition = m_pVerticesPos[0] = _float3(-0.5f, 0.5f, -0.5f);
	pVertices[0].vTexUV = _float2(0.f, 0.f);

	pVertices[1].vPosition = m_pVerticesPos[1] = _float3(0.5f, 0.5f, -0.5f);
	pVertices[1].vTexUV = _float2(1.f, 0.f);

	pVertices[2].vPosition = m_pVerticesPos[2] = _float3(0.5f, -0.5f, -0.5f);
	pVertices[2].vTexUV = _float2(1.f, 1.f);

	pVertices[3].vPosition = m_pVerticesPos[3] = _float3(-0.5f, -0.5f, -0.5f);
	pVertices[3].vTexUV = _float2(0.f, 1.f);

	pVertices[4].vPosition = m_pVerticesPos[0] = _float3(-0.5f, 0.5f, 0.5f);
	pVertices[4].vTexUV = _float2(0.f, 0.f);

	pVertices[5].vPosition = m_pVerticesPos[1] = _float3(0.5f, 0.5f, 0.5f);
	pVertices[5].vTexUV = _float2(1.f, 0.f);

	pVertices[6].vPosition = m_pVerticesPos[2] = _float3(0.5f, -0.5f, 0.5f);
	pVertices[6].vTexUV = _float2(1.f, 1.f);

	pVertices[7].vPosition = m_pVerticesPos[3] = _float3(-0.5f, -0.5f, 0.5f);
	pVertices[7].vTexUV = _float2(0.f, 1.f);


	if (FAILED(m_pVBuffer->Unlock()))
		return E_FAIL;

	_ushort* pIndices = nullptr;

	if (FAILED(m_pIBuffer->Lock(0, 0, (void**)&pIndices, 0)))
		return E_FAIL;

	pIndices[0] = 0;
	pIndices[1] = 1;
	pIndices[2] = 2;

	pIndices[3] = 0;
	pIndices[4] = 2;
	pIndices[5] = 3;


	pIndices[6] = 4;
	pIndices[7] = 0;
	pIndices[8] = 3;

	pIndices[9] = 4;
	pIndices[10] = 3;
	pIndices[11] = 7;


	pIndices[12] = 1;
	pIndices[13] = 5;
	pIndices[14] = 6;

	pIndices[15] = 1;
	pIndices[16] = 6;
	pIndices[17] = 2;


	pIndices[18] = 4;
	pIndices[19] = 5;
	pIndices[20] = 1;

	pIndices[21] = 4;
	pIndices[22] = 1;
	pIndices[23] = 0;


	pIndices[24] = 6;
	pIndices[25] = 7;
	pIndices[26] = 3;

	pIndices[27] = 6;
	pIndices[28] = 3;
	pIndices[29] = 2;


	pIndices[30] = 5;
	pIndices[31] = 4;
	pIndices[32] = 7;

	pIndices[33] = 5;
	pIndices[34] = 7;
	pIndices[35] = 6;

	if (FAILED(m_pIBuffer->Unlock()))
		return E_FAIL;

	return S_OK;
}

HRESULT CVIBuffer_Cube::Ready_Component(void * pArg)
{
	return S_OK;
}



CVIBuffer_Cube * CVIBuffer_Cube::Create(LPDIRECT3DDEVICE9 pGraphic_Device)
{
	CVIBuffer_Cube*	pInstance = new CVIBuffer_Cube(pGraphic_Device);

	if (FAILED(pInstance->Ready_Component_Prototype()))
	{
		MessageBox(0, L"Failed To Creating CVIBuffer_Cube", L"System Message", MB_OK);
		Safe_Release(pInstance);
	}

	return pInstance;
}

CComponent * CVIBuffer_Cube::Clone_Component(void * pArg)
{
	CVIBuffer_Cube*	pInstance = new CVIBuffer_Cube(*this);

	if (FAILED(pInstance->Ready_Component(pArg)))
	{
		MessageBox(0, L"Failed To Creating CVIBuffer_Rect", L"System Message", MB_OK);
		Safe_Release(pInstance);
	}

	return pInstance;
}

void CVIBuffer_Cube::Free()
{
	CVIBuffer::Free();
}


