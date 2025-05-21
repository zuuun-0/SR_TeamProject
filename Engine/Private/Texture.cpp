#include "Texture.h"

CTexture::CTexture(LPDIRECT3DDEVICE9 pGraphic_Device)
	: CComponent{ pGraphic_Device }
{
}

CTexture::CTexture(const CTexture& Prototype)
	: CComponent{ Prototype }
	, m_Textures { Prototype.m_Textures }
	, m_iNumTextures { Prototype.m_iNumTextures }
{
	for (auto& pTexture : m_Textures)
		Safe_AddRef(pTexture);
}

HRESULT CTexture::Initialize_Prototype(TEXTURE eType, const _tchar* pTextureFilePath, _uint iNumTextures)
{
	m_iNumTextures = iNumTextures;

	for (size_t i = 0; i < iNumTextures; i++)
	{
		IDirect3DBaseTexture9* pTexture = { nullptr };

		_tchar szTextureFilePath[MAX_PATH] = {};

		wsprintf(szTextureFilePath, pTextureFilePath, i);

		HRESULT hr = {};
		
		switch (eType)
		{
		case TEXTURE::RECT:
			hr = D3DXCreateTextureFromFile(m_pGraphic_Device, szTextureFilePath, reinterpret_cast<LPDIRECT3DTEXTURE9*>(&pTexture));
			break;
		case TEXTURE::CUBE:
			hr = D3DXCreateCubeTextureFromFile(m_pGraphic_Device, szTextureFilePath, reinterpret_cast<LPDIRECT3DCUBETEXTURE9*>(&pTexture));
			break;
		}

		if (FAILED(hr))
			return E_FAIL;

		m_Textures.push_back(pTexture);
	}

	return S_OK;
}

HRESULT CTexture::Initialize(void* pArg)
{
	return S_OK;
}

HRESULT CTexture::Bind_Texture(_uint iTextureIndex)
{
	if (iTextureIndex >= m_iNumTextures)
		return E_FAIL;

	return m_pGraphic_Device->SetTexture(0, m_Textures[iTextureIndex]);
}


CTexture* CTexture::Create(LPDIRECT3DDEVICE9 pGraphic_Device, TEXTURE eType, const _tchar* pTextureFilePath, _uint iNumTextures)
{
	CTexture* pInstance = new CTexture(pGraphic_Device);

	if (FAILED(pInstance->Initialize_Prototype(eType, pTextureFilePath, iNumTextures)))
	{
		MSG_BOX(TEXT("Failed to Created : CTexture"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

CComponent* CTexture::Clone(void* pArg)
{
	CTexture* pInstance = new CTexture(*this);

	if (FAILED(pInstance->Initialize(pArg)))
	{
		MSG_BOX(TEXT("Failed to Cloned : CTexture"));
		Safe_Release(pInstance);
	}
	return pInstance;
}

void CTexture::Free()
{
	__super::Free();

	for (auto& pTexture : m_Textures)
		Safe_Release(pTexture);

	m_Textures.clear();
}
