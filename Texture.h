#pragma once
#include <d3d11.h>
#include <string>
#include <wrl.h>

using namespace Microsoft::WRL;
using std::string;

class Texture {
	ID3D11SamplerState* pSampler_;
	ID3D11ShaderResourceView* pSRV_;
public:
	Texture();
	~Texture();
	//画像の読み込み
	HRESULT Load(string fileName);
	//解放
	void Release();
	//サンプラーのゲッター
	ID3D11SamplerState* GetSampler() { return pSampler_; };
	//シェーダーリソースビューのゲッター
	ID3D11ShaderResourceView* GetSRV() { return pSRV_; };
};