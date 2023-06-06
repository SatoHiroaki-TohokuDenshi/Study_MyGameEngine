#include <DirectXTex.h>
#include "Texture.h"
#include "Direct3D.h"

#pragma comment(lib, "DirectXTex.lib")

Texture::Texture() :
	pSampler_(nullptr), pSRV_(nullptr)
{
	Release();
}

Texture::~Texture() {

}

//画像の読み込み
HRESULT Texture::Load(std::string fileName) {
	HRESULT hr = S_OK;

	wchar_t wtext[FILENAME_MAX];
	size_t ret;
	mbstowcs_s(&ret, wtext, fileName.c_str(), fileName.length());

	using namespace DirectX;
	TexMetadata metadata;		//画像のデータを扱う構造体
	ScratchImage image;			//画像そのものを扱うクラス（画像の本体）
	hr = LoadFromWICFile(wtext, WIC_FLAGS::WIC_FLAGS_NONE, &metadata, image);
	//エラー処理
	if (FAILED(hr)) {
		MessageBox(nullptr, "画像の読み込みに失敗しました", "エラー", MB_OK);
		return hr;
	}

	//サンプラーの作成
	D3D11_SAMPLER_DESC  SamDesc;
	ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));
	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	hr = Direct3D::pDevice->CreateSamplerState(&SamDesc, &pSampler_);
	//エラー処理
	if (FAILED(hr)) {
		MessageBox(nullptr, "サンプラーの作成に失敗しました", "エラー", MB_OK);
		return hr;
	}

	//シェーダーリソースビューの作成
	D3D11_SHADER_RESOURCE_VIEW_DESC srv = {};
	srv.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	srv.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srv.Texture2D.MipLevels = 1;
	hr = CreateShaderResourceView(Direct3D::pDevice, image.GetImages(), image.GetImageCount(),metadata, &pSRV_);
	//エラー処理
	if (FAILED(hr)) {
		MessageBox(nullptr, "シェーダーリソースビューの作成に失敗しました", "エラー", MB_OK);
		return hr;
	}

	return S_OK;
}

//解放
void Texture::Release() {
	SAFE_RELEASE(pSRV_);
	SAFE_RELEASE(pSampler_);
}